Blog
====
After a while using Wordpress and hating the lack of control I finally decided to create my own blogging software.

Who knows, maybe some day this software will be useful and others will be able to reuse it, but, at least for the time being, it's for me, just hacking and trying ideas.

# How to run locally
Make sure you have RVM installed.

```sh
export BLOG_PATH=<path to the repository>
cd $BLOG_PATH

gem install bundler
bundle install


mkdir -p pids/ logs/

unicorn -c unicorn.rb -D
```

The server will listin on port 8080. http://127.0.0.1:8080.
