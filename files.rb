module Files
  def file(post, name)
    file = File.join('public', 'files', post, name)
    "<a href='/#{file}' target='_blank'>#{name}</a>"
  end
end
