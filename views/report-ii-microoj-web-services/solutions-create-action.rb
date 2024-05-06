def create
  @id_problem = params[:id_problem]
  @id_user = params[:id_user]
  @source_code = params[:source_code]
  @language = params[:language]

  client = Savon::Client.new do
      wsdl.document = WSDL_LOCATION
  end

  request = client.request "Judge.save_solution" do
      soap.body = {
          :user => current_user.name,
          :password => current_user.password,
          :id_problem => params[:id_problem],
          :source_code => params[:source_code],
          :language => params[:language]
      }
  end

  response = request.to_hash[:judge_save_solution_response]
  @submission_answer = response[:return]

  if @submission_answer[:error].to_i == SU_COMPILATION
      id = @submission_answer[:id].to_i
      request = client.request "Judge.test_solution" do
          soap.body = { 
              :user => current_user.name,
              :password => current_user.password,
              :id_solution => id,
          }
      end

      response = request.to_hash[:judge_test_solution_response]
      @test_results = response[:return][:item]
  else
      request = client.request "Judge.get_last_error"
      response = request.to_hash[:judge_get_last_error_response]
      @error_message = response[:message]
  end

  render 'submission_result'
end
