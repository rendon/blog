#!/usr/bin/env bash
cd ~/blog
git pull origin master
killall ruby
unicorn -c unicorn.rb -D
sudo systemctl restart nginx


