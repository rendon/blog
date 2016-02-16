require 'sinatra'

get '/' do
  erb :index, locals: { name: "Rafael" }
end
