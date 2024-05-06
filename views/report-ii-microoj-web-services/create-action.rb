def create
    @user = User.new(user_params)
    if @user.valid?
        client = Savon::Client.new do
            wsdl.document = WSDL_LOCATION
        end

        name = params[:user][:name]
        password = params[:user][:password]

        url = SecureRandom.urlsafe_base64
        remember_token = Digest::SHA1.hexdigest(url.to_s)
        request = client.request "Judge.create_user" do
            soap.body = {
                :user => name,
                :password => password,
                :remember_token => remember_token
            }
        end

        response = request.to_hash[:judge_create_user_response]
        id = response[:return].to_i

        if id > 0
            flash[:success] = "Bienvenido a Micro OJ"

            request = client.request "Judge.get_user_data" do
                soap.body = {
                    :user => name,
                    :password => password
                }
            end

            response = request.to_hash[:judge_get_user_data_response]
            user_data = response[:user]
            user = User.new
            user.id = user_data[:id]
            user.name = user_data[:id]
            user.password = user_data[:password]
            user.remember_token = user_data[:remember_token]

            sign_in user
            redirect_to root_path
        else
            render 'new'
        end

    else
        render 'new' # Pending
    end
end
