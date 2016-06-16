#!/bin/bash

tshark -r foo.pcap \
       -Y "http.response or http.request" \
       -T fields -E separator="|" \
       -e frame.time_epoch \
       -e frame.len \
       -e ip.checksum \
       -e ip.proto \
       -e ip.flags \
       -e ip.ttl \
       -e ip.src \
       -e ip.dst \
       -e tcp.len \
       -e tcp.flags \
       -e tcp.srcport \
       -e tcp.dstport \
#      -e http.request.method \
#      -e http.response.code \
#      -e http.request.version \
#      -e http.host \
#      -e http.request.uri \
#      -e http.user_agent \
#      -e http.response.code \
#      -e http.content_type \
#      -e http.content_length \
#      -e http.location \
#      -e http.referer

