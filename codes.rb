# frozen_string_literal: true

require 'cgi'

# Functions to render code snippets.
module Codes
  def code(post, name, opts = {})
    src = File.read(File.join('public', 'code', post, name))
    text = CGI.escapeHTML(src)
    caption = "<p><strong>Snippet X</strong>. #{opts[:caption]}.</p>" if opts[:caption]
    %(
    <div class='code-snippet'>
      #{caption}
      <pre><code>#{text}</code></pre>
    </div>
    )
  end

  def inline_code(src)
    "<pre><code>#{CGI.escapeHTML(src)}</code></pre>"
  end

  def src_file(post, name)
    file = File.join('public', 'code', post, name)
    "<a href='/#{file}' target='_blank'>#{name}</a>"
  end
end
