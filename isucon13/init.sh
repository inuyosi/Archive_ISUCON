#!/bin/sh

## alp
wget https://github.com/tkuchiki/alp/releases/download/v1.0.21/alp_linux_amd64.tar.gz
tar -xvzf alp_linux_amd64.tar.gz

sudo install ./alp /usr/local/bin/alp

## pt-query-digest
sudo apt update
sudo apt install percona-toolkit -y

## query-digester
git clone https://github.com/kazeburo/query-digester.git
cd query-digester/
sudo install query-digester /usr/local/bin
