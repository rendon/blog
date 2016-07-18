require 'json'

class Quote
  def random
    quotes[rand(quotes.length)]
  end

  def quotes
    @data ||= JSON.parse(File.read(File.join('public', 'files', 'quotes.json')))
    @data['quotes']
  end
end
