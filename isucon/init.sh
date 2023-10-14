#!/bin/sh

## alp
wget https://github.com/tkuchiki/alp/releases/download/v1.0.21/alp_linux_amd64.tar.gz
tar -xvzf alp_linux_amd64.tar.gz

sudo install ./alp /usr/local/bin/alp

## ab
sudo apt update -y
sudo apt install apache2-utils -y
