# syntax = docker/dockerfile:1
from rendon/ruby:latest AS base

WORKDIR /home/admin/app
COPY . .
USER root
RUN mkdir -p pids/ logs/
RUN chown -R admin:admin Gemfile Gemfile.lock pids/ logs/ public/
USER admin

RUN rbenv local ${RUBY_VERSION}

RUN bundle install && rm -rf ~/.bundle/

FROM base AS build

EXPOSE 8080
ENV BLOG_PATH="/home/admin/app"
CMD ["unicorn", "-c", "unicorn.rb"]
