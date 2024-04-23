# frozen_string_literal: true

require 'json'

# Functions for rendering quotes.
class Quote
  def random
    quotes[rand(quotes.length)]
  end

  def quotes
    @data ||= JSON.parse(File.read(File.join('public', 'files', 'quotes.json')))
    @data['quotes']
  end
end
