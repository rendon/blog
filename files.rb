module Files
  def file(post, name, caption = nil)
    caption ||= name
    file = File.join('public', 'files', post, name)
    "<a href='/#{file}' target='_blank'>#{caption}</a>"
  end
end
