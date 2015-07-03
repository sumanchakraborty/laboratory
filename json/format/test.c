
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "format.h"

static const char *ixjson_format(void) {
  char buf[MAX_LENGTH], *p = buf;

  p += ixjson_format_raw_str(buf, p, "{");
  p += ixjson_format_quoted_str(buf, p, "foo");
  p += ixjson_format_raw_str(buf, p, ":[");
  p += ixjson_format_int(buf, p, -123);
  p += ixjson_format_raw_str(buf, p, ",");
  p += ixjson_format_double(buf, p, 1.23);
  p += ixjson_format_raw_str(buf, p, ",");
  p += ixjson_format_raw_str(buf, p, "true");
  p += ixjson_format_raw_str(buf, p, "]}");

  printf("JSON String - %s\n", buf);

  return NULL;
}

int main(void) {
  ixjson_format();
  return 0;
}

