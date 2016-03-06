require 'htmlentities'
module Code
  def code(post, name)
    src = File.read(File.join('public', 'code', post, name))
    text = HTMLEntities.new.encode(src)
    "<pre><code>#{text}</code></pre>"
  end

  def src_file(post, name)
    file = File.join('public', 'code', post, name)
    "<a href='/#{file}' target='_blank'>#{name}</a>"
  end
end
