#ifndef ARG_PARSER_H
#define ARG_PARSER_H

struct Opts {
    char            mpd_sun_path[108];
    unsigned short  max_text_len;
    unsigned int    text_scroll_len;
    unsigned int    update_rate_ms;

    char           *textf;
    char           *tooltipf;
};
struct Opts parse_opts(int argc, char *argv[]);

#endif
