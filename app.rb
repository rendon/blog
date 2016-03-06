require 'sinatra'
require 'rdiscount'

require_relative 'tex'
require_relative 'code'
require_relative 'post'

helpers Tex
helpers Code
helpers Post

get '/' do
  erb :index, locals: { name: "Rafael" }
end

get '/posts/:post/?' do
  post = params[:post].downcase
  begin
    erb post.to_sym, locals: { post: post }
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end

get '/public/code/:post/:file/?' do
  post = params[:post].downcase
  file = params[:file].downcase
  send_file File.join('public', 'code', post, file), :type => :text
end
