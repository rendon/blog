require 'htmlentities'
module Code
  def code(name)
    text = HTMLEntities.new.encode(File.read(File.join('public', 'code', name)))
    "<pre><code>#{text}</code></pre>"
  end

  def src_file(name)
    "<a href='/#{File.join('public', 'code', name)}' target='_blank'>#{name}</a>"
  end
end
