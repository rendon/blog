require 'sinatra'
require 'rdiscount'

require_relative 'tex'
require_relative 'code'

helpers Tex
helpers Code

get '/' do
  erb :index, locals: { name: "Rafael" }
end

get '/posts/:post/?' do
  post = params[:post].downcase.to_sym
  begin
    erb post
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end
