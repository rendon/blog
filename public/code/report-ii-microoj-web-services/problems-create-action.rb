def create
    @problem_saved = false
    parameters = problem_params
    @problem = Problem.new(parameters)
    if not @problem.valid?
        render 'new'
    else
        client = Savon::Client.new do
            wsdl.document = WSDL_LOCATION
        end

        title = parameters[:title]
        description = parameters[:description]
        author = parameters[:author]

        request = client.request "Judge.create_problem" do
            soap.body = {
                :user => current_user.name,
                :password => current_user.password,
                :title => title,
                :description => CGI.escapeHTML(description),
                :author => author
            }
        end

        response = request.to_hash[:judge_create_problem_response]
        @insert_problem_code = response[:return]

        if @insert_problem_code.to_i > 0
            @problem_saved = true
            @problem_saved_id = @insert_problem_code
            @problem_title = parameters[:title]
            @problem_statement = parameters[:description]
            @problem_author = author

            @test_cases = []
            id = @insert_problem_code.to_i
            1.upto(TEST_CASES_PER_PROBLEM) do |tc|
                input_key  = "in_" + tc.to_s
                output_key = "out_" + tc.to_s
                request = client.request "Judge.save_test_case" do
                    soap.body = {
                        :user => current_user.name,
                        :password => current_user.password,
                        :id_problem => id,
                        :input => CGI.escapeHTML(params[input_key]),
                        :output => CGI.escapeHTML(params[output_key])
                    }
                end

                response = request.to_hash[:judge_save_test_case_response]
                test_id = response[:return].to_i
                @test_cases << {"id" => test_id, "in" => params[input_key],
                                "out" => params[output_key]}
            end

            render 'saved'
        else
            msg = "Ocurrio un error al intentar guardar el problema."
            @problem.errors.add("Error:", msg)
            render 'new'
        end

    end
end
