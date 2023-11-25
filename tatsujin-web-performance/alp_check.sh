#!/bin/sh

alp json --sort sum -r -o count,method,uri,min,avg,max,sum < /var/log/nginx/access.log
