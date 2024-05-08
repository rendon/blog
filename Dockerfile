# syntax = docker/dockerfile:1
FROM rendon/ruby:latest AS base


WORKDIR /home/admin/app
COPY . .
USER root

RUN apt update && apt install -y pandoc fd-find

RUN mkdir -p pids/ logs/
RUN chown -R admin:admin Gemfile Gemfile.lock pids/ logs/ public/ views/
USER admin

RUN rbenv local ${RUBY_VERSION}

RUN bundle install && rm -rf ~/.bundle/

RUN bin/index-posts.sh && bin/md2html.sh

FROM base AS build

EXPOSE 8080
ENV BLOG_PATH="/home/admin/app"
CMD ["unicorn", "-c", "unicorn.rb"]
