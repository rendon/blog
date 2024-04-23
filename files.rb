# frozen_string_literal: true

# Functions for handling files.
module Files
  def file(post, name, caption = nil)
    caption ||= name
    file = File.join('public', 'files', post, name)
    "<a href='/#{file}' target='_blank'>#{caption}</a>"
  end
end
