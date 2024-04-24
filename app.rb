# frozen_string_literal: true

require 'sinatra'
require 'rdiscount'
require 'ostruct'

require_relative 'quote'

require_relative 'tex'
require_relative 'codes'
require_relative 'posts'
require_relative 'files'

helpers Tex
helpers Codes
helpers Posts
helpers Files

MIME_TYPES = {
  '.pdf' => 'application/pdf',
  '.png' => 'image/png',
  '.jpg' => 'image/jpeg',
  '.svg' => 'image/svg+xml'
}.freeze

def mime(file_name)
  MIME_TYPES[File.extname(file_name.downcase)] || 'text/plain'
end

get '/' do
  erb :index
end

get '/favicon.ico' do
  send_file File.join('public', 'pictures', 'favicon.ico'), type: mime('image/ico')
end

get '/posts/:post/?' do
  # TeX setup
  @tex = OpenStruct.new(fig_num: 0, bibs: [])
  post = params[:post].downcase
  begin
    erb post.to_sym, locals: { post: post }
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end

get '/public/code/:post/:file' do
  post = params[:post].downcase
  file = params[:file]
  begin
    send_file File.join('public', 'code', post, file), type: mime(file)
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end

get '/public/pictures/:post/:file' do
  post = params[:post].downcase
  file = params[:file]
  begin
    send_file File.join('public', 'pictures', post, file), type: mime(file)
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end

get '/public/files/:post/:file' do
  post = params[:post].downcase
  file = params[:file]
  begin
    send_file File.join('public', 'files', post, file), type: mime(file)
  rescue LoadError, Errno::ENOENT => e
    puts e.message
    raise Sinatra::NotFound
  end
end
