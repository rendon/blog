module Posts
  def link_to_post(id, name)
    "<a href='/posts/#{id}' target='_blank'>#{name}</a>"
  end

  def link_to(url, text, options = {})
    target = options[:target] ? "target='#{options[:target]}'" : ''
    "<a href='#{url}' #{target}>#{text}</a>"
  end
end
