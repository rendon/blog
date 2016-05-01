module Posts
  def link_to_post(id, name)
    "<a href='/posts/#{id}' target='_blank'>#{name}</a>"
  end
end
