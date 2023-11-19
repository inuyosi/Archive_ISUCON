#!/bin/sh

pt-query-digest /var/log/mysql/mysql-slow.log | tee digest_$(date +%Y%m%d%H%M).txt
