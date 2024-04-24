Blog
====
After a while using WordPress and hating the lack of control I finally decided to create my own blogging software.

Who knows, maybe some day this software will be useful and others will be able to reuse it, but, at least for the time being, it's for me, just hacking and trying ideas.

## How to run locally
Make sure you have [rbenv](https://github.com/rbenv/rbenv) installed.
```sh
export BLOG_PATH=<path to the repository>
cd $BLOG_PATH

gem install bundler
bundle install


mkdir -p pids/ logs/

unicorn -c unicorn.rb -D
```

The server will listen on port 8080: http://127.0.0.1:8080.

## Run on a docker container
```
docker build -t blog .
docker run --rm --name myblog -p 8080:8080 -d blog
```
