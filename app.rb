require 'sinatra'
require "rdiscount"

require_relative 'tex'

helpers Tex

get '/' do
  erb :index, locals: { name: "Rafael" }
end

get '/posts/:post/?' do
  post = params[:post].downcase.to_sym
  begin
    erb post
  rescue LoadError, Errno::ENOENT => e
    raise Sinatra::NotFound
  end
end
