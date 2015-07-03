
#ifndef FORMAT_HEADER
#define FORMAT_HEADER

#define MAX_LENGTH 1024

int ixjson_format_int(char *buf, char *off, long int value);
int ixjson_format_double(char *buf, char *off, double value);
int ixjson_format_quoted_str(char *buf, char *off, const char *str);
int ixjson_format_raw_str(char *buf, char *off, const char *str);

#endif /* FORMAT_HEADER */
