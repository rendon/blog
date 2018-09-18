#!/bin/sh
echo 'set -o vi' >> ~/.bashrc
sudo apt-get update
sudo apt-get -y install vim ruby git nginx curl tree

# Get certificate
echo deb http://ftp.debian.org/debian jessie-backports main | sudo tee /etc/apt/sources.list.d/backports.list
sudo apt-get update
sudo apt-get -y install certbot -t jessie-backports
sudo systemctl stop nginx
sudo certbot certonly --standalone -d letmethink.mx -m rafaelrendonpablo@gmail.com --agree-tos

sudo mkdir -p /blog
sudo chown admin:admin /blog
cd /blog
git clone https://github.com/rendon/blog.git

export BLOG_PATH=/blog/blog
cd $BLOG_PATH

# Install RVM
gpg --keyserver hkp://keys.gnupg.net --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB
\curl -sSL https://get.rvm.io | bash -s stable
source /home/admin/.rvm/scripts/rvm
rvm install 2.5
rvm use 2.5 --default

gem install bundler
bundle install

mkdir -p pids/ logs/
git pull origin master
# killall ruby
unicorn -c unicorn.rb -D

# Copy Nginx configuration file
sudo cp config/nginx/sites-enabled/default /etc/nginx/sites-enabled/default

sudo systemctl restart nginx
