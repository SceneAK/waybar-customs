#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/arg_parser.h"

void print_usage(void)
{
    printf("Options: \n");
    printf("  -U [arg]      Path to the MPD unix socket. Default is $XDG_RUNTIME_DIR/mpd/socket \n");
    printf("  -R [arg]      Update rate (ms) at which polling timeouts and song title text scrolls\n");
    printf("  -T [arg]      Set the text format (Example: \"Title: $_title_or_filename, Progress: $elapsed_fmtted:$duration_fmtted(s)). NOTE: escape the sigil with (\\) if you're in the terminal\n");
    printf("  -t [arg]      Set the tooltip format\n");
}

struct Opts parse_opts(int int_argc, char *argv[])
{
    struct Opts opts;
    const char  *run_dir = getenv("XDG_RUNTIME_DIR");
    char        dflt_sun_path[sizeof(opts.mpd_sun_path)];
    size_t      i;
    size_t      argc = (size_t)int_argc;

    memset(&dflt_sun_path, 0, sizeof(dflt_sun_path));
    strncpy(dflt_sun_path, run_dir != NULL ? run_dir : "/run", sizeof(dflt_sun_path)-1);
    strncat(dflt_sun_path, "/mpd/socket", sizeof(dflt_sun_path) - strlen(dflt_sun_path) - 1);

    memset(&opts, 0, sizeof(struct Opts));
    opts.max_text_len = 45;
    opts.update_rate_ms = 1000;
    opts.textf = "$_title_or_filename";
    opts.tooltipf = "Artist: $Artist\\nAlbum: $Album\\nPos:$song/$playlistlength\\n ($elapsed_fmtted/$duration_fmtted)";
    strncpy(opts.mpd_sun_path, dflt_sun_path, sizeof(opts.mpd_sun_path)-1);

    for(i = 1; i < argc; i++) 
    {
        if(strcmp(argv[i], "-h") == 0){
            print_usage();
            exit(EXIT_SUCCESS);
        }else if(strcmp(argv[i], "-U") == 0){
            if(i + 1 < argc){
                strncpy(opts.mpd_sun_path, argv[i+1], sizeof(opts.mpd_sun_path)-1);
                i++; 
            }else{
                printf("Missing argument for -U, using default socket path\n");
            }
        }else if(strcmp(argv[i], "-R") == 0){
            if(i + 1 < argc){
                opts.update_rate_ms = (int)strtol(argv[i+1], NULL, 10);
                i++;
            }else{
                printf("Missing update rate after -R\n");
                exit(EXIT_FAILURE);
            }
        }else if(strcmp(argv[i], "-T") == 0){
            if(i + 1 < argc){
                opts.textf = argv[i+1];
                i++;
            }else{
                printf("Missing text after -T\n");
                exit(EXIT_FAILURE);
            }
        }else if(strcmp(argv[i], "-t") == 0){
            if(i + 1 < argc){
                opts.tooltipf = argv[i+1];
                i++;
            }else{
                printf("Missing tooltip after -t\n");
                exit(EXIT_FAILURE);
            }
        }else{
            printf("Unknown argument: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return opts;
}
