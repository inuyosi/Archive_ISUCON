#!/bin/sh

alp json --sort sum -r -m "/api/livestream/[0-9]+/statistics","/api/user/.*/icon","/api/livestream/[0-9]+/livecomment","/api/livestream/[0-9]+/reaction","/api/livestream/[0-9]+/moderate","/api/livestream/[0-9]+/report","/api/livestream/[0-9]+/ngwords","/api/livestream/[0-9]+/enter","/api/livestream/[0-9]+/exit" -o count,method,uri,min,avg,max,sum < /var/log/nginx/access.log