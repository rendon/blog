require 'htmlentities'
module Code
  def code(id)
    text = HTMLEntities.new.encode(File.read(File.join('public', 'code', id)))
    "<pre><code>#{text}</code></pre>"
  end
end
