def create
    client = Savon::Client.new do
        wsdl.document = WSDL_LOCATION
    end

    request = client.request "Judge.authenticate_user" do
        soap.body = {
            :user => params[:session][:name],
            :password => params[:session][:password]
        }
    end

    answer = request[:judge_authenticate_user_response][:answer].to_i
    if answer == VALID_USER
        request = client.request "Judge.get_user_data" do
            soap.body = {
                :user => params[:session][:name],
                :password => params[:session][:password]
            }
        end

        response = request.to_hash[:judge_get_user_data_response]
        user_data = response[:user]
        user = User.new
        user.id = user_data[:id]
        user.name = params[:session][:name]
        user.password = params[:session][:password]
        user.remember_token = user_data[:remember_token]

        sign_in user
        redirect_to root_path
    else
        flash.now[:error] = 'Combinación usuario/contraseña invalida'
        render 'new'
    end
end
