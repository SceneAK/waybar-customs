#define FIRST_TWO_BIT 0xC0
#define CONTINUATION 0x80

unsigned int atoul(const char *s)
{
    /* ChatGPT Generated */
    unsigned int n = 0;
    while (*s >= '0' && *s <= '9') {
        n = n * 10 + (*s++ - '0');
    }
    return n;
}
unsigned long utf8_strlen(char *str)
{
    unsigned long len = 0;
    for(; *str != '\0'; str++)
    {
        if( (*str & FIRST_TWO_BIT) != CONTINUATION ){
            len++;
        }
    }
    return len;
}
