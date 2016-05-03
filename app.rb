require 'sinatra'
require 'rdiscount'

require_relative 'tex'
require_relative 'code'
require_relative 'posts'
require_relative 'files'

helpers Tex
helpers Code
helpers Posts
helpers Files

get '/' do
  erb :index
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


get '/public/pictures/:post/:file/?' do
  post = params[:post].downcase
  file = params[:file].downcase
  send_file File.join('public', 'pictures', post, file)
end

get '/public/files/:post/:file/?' do
  post = params[:post].downcase
  file = params[:file].downcase
  send_file File.join('public', 'files', post, file)
end
