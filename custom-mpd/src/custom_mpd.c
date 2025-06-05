#include "../include/arg_parser.h"

#include "../include/socks.h"
#include "../include/mpd_receiver.h"
#include "../include/mpd_essentials_receiver.h"

#include "../include/keyval.h"
#include "../include/mpd_to_kv.h"

#include "../include/titlefilename_kv.h"
#include "../include/fmtted_time_kvs.h"

#include "../include/str_wrapper.h"
#include "../include/wbformatter.h"

#include <signal.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SHARED_STRBUF_SIZE 2048
#define WBPROP_BUF_SIZE 1024
#define KEYVAL_ARR_SIZE 64

#define MPD_IDLE "idle player\n"

#define POLL_RES_TIMEOUT 0
#define POLL_RES_ERR -1

struct Ctx{
    struct Opts         opts;
    int                 sockfd;
    char                shared_strbuf[SHARED_STRBUF_SIZE];
    struct KeyValPtr    kvptr_arr[KEYVAL_ARR_SIZE];
    size_t              kvptrs_len;
};
struct Ctx *cleanup_ctx;
void cleanup_close(int sig)
{
    if(cleanup_ctx->sockfd > 0) {
        close(cleanup_ctx->sockfd);
        cleanup_ctx->sockfd = -1;
        printf("closed socket\n");
    }
    exit(sig);
}

char *get_class(struct KeyValPtr *kvptrs, size_t len)
{
    char *state = kv_val_of("state", kvptrs, len);
    return state != NULL ? state : "";
}

#include "../include/utf8util.h" /* feels out of place */
void animate_buf(char *anim, char *src, size_t max_bytes, size_t max_len, unsigned long step, unsigned long start_delay)
{
    size_t utf8len = utf8_strlen(src);
    size_t offset;

    if(utf8len <= max_len){
        strcpy(anim, src);
        return;
    }

    step %= utf8len + start_delay;
    if(step <= start_delay){
        offset = 0;
    }else{
        offset = step - start_delay;
    }
    wrapcpy_utf8str(anim, src, max_len, max_bytes, offset);
}

int main(int argc, char *argv[])
{
    struct Ctx          ctx;
    struct pollfd       pfd;
    int                 pol_res;
    char                text_buf[WBPROP_BUF_SIZE];
    char                text_buf_anim[WBPROP_BUF_SIZE];
    char                tooltip_buf[WBPROP_BUF_SIZE];
    char               *cls_ptr;
    unsigned long       poll_ittr_count;
    unsigned long       elapsed_offset_s;
    struct _fmtted_time fmtted_time;

    cleanup_ctx = &ctx;
    signal(SIGINT, cleanup_close);
    signal(SIGTERM, cleanup_close);

    ctx.opts = parse_opts(argc, argv);

    ctx.sockfd = create_connect_sun(ctx.opts.mpd_sun_path);
    if(ctx.sockfd == -1){
        exit(EXIT_FAILURE);
    }

    if(!recv_mpd_greet(ctx.sockfd, ctx.shared_strbuf, sizeof(ctx.shared_strbuf))){
        perror("Did not receive MPD's greet message");
    }
    print_waybarf("MPD Connected", "", "");

    memset(&pfd, 0, sizeof(pfd));
    pfd.fd = ctx.sockfd;
    pfd.events = POLLIN | POLLHUP;

    while(1)
    {
        recv_mpd_essentials(ctx.sockfd, ctx.shared_strbuf, sizeof(ctx.shared_strbuf));
        ctx.kvptrs_len = parse_to_kv(ctx.kvptr_arr, KEYVAL_ARR_SIZE, ctx.shared_strbuf); 

        ctx.kvptrs_len = titlefilename_kv_add(ctx.kvptr_arr, KEYVAL_ARR_SIZE, ctx.kvptrs_len);
        ctx.kvptrs_len = fmtted_time_kvs_add(&fmtted_time, ctx.kvptr_arr, KEYVAL_ARR_SIZE, ctx.kvptrs_len);

        kv_insert_sort_desc(ctx.kvptr_arr, ctx.kvptrs_len);

        poll_ittr_count = 0;
        elapsed_offset_s = 0;
        write(ctx.sockfd, MPD_IDLE, sizeof(MPD_IDLE)-1);
        pol_res = POLL_RES_TIMEOUT;
        while(pol_res == POLL_RES_TIMEOUT)
        {
            cls_ptr = get_class(ctx.kvptr_arr, ctx.kvptrs_len);
            populate_format(text_buf, sizeof(text_buf), ctx.kvptr_arr, ctx.kvptrs_len, ctx.opts.textf);
            populate_format(tooltip_buf, sizeof(tooltip_buf), ctx.kvptr_arr, ctx.kvptrs_len, ctx.opts.tooltipf);

            animate_buf(text_buf_anim, text_buf, sizeof(text_buf_anim), ctx.opts.max_text_len, poll_ittr_count, ctx.opts.scroll_delay_ticks);

            print_waybarf(text_buf_anim, tooltip_buf, cls_ptr);

            pol_res = poll(&pfd, 1, ctx.opts.update_rate_ms);
            if(pol_res == POLL_RES_ERR){
                perror("Err idling for mpd.\n");
                return EXIT_FAILURE;
            }
            poll_ittr_count++;

            elapsed_offset_s = (strcmp(cls_ptr, "pause") == 0) ?  elapsed_offset_s : ( poll_ittr_count * ctx.opts.update_rate_ms/1000 );
            fmtted_time_update(&fmtted_time, ctx.kvptr_arr, ctx.kvptrs_len, elapsed_offset_s);
        }
        recv_mpd(ctx.sockfd, ctx.shared_strbuf, sizeof(ctx.shared_strbuf)); 
    }
}
