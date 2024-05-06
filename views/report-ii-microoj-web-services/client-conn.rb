require 'savon'

client = Savon::Client.new do
    # Dirección de nuestro servicio
    wsdl.document = "http://localhost/microoj_ws/judge.php?wsdl"
end

user_name = "usuario"
password = "1a2b3c"
request = client.request "Judge.create_user" do
    soap.body = {
        :name => user_name,
        :password => password
    }
end

response = request.to_hash[:judge_create_user_response]
puts response
insert_id = response[:return].to_i
puts insert_id
