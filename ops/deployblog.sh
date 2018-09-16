#!/usr/bin/env bash
export BLOG_PATH=$PWD
cd $BLOG_PATH
mkdir -p pids logs
git pull origin master
killall ruby
unicorn -c unicorn.rb -D
sudo systemctl restart nginx


