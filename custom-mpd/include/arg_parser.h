#ifndef ARG_PARSER_H
#define ARG_PARSER_H

struct Opts {
    char            mpd_sun_path[108];
    unsigned short  max_text_len;
    unsigned int    update_rate_ms;
    unsigned int    scroll_delay_ticks;

    char           *textf;
    char           *tooltipf;
};
struct Opts parse_opts(int argc, char *argv[]);

#endif
