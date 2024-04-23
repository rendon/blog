# frozen_string_literal: true

require 'tilt/erb'
require './app'
require 'sass/plugin/rack'
Sass::Plugin.options[:style] = :compressed
use Sass::Plugin::Rack

run Sinatra::Application
