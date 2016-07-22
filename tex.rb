module Tex
  def ref(id)
    "<a href='#label_#{id}'><span name='ref_#{id}'>?</span></a>"
  end

  def figure(post, file, options = {})
    langs = { en: 'Figure ', es: 'Figura ' }
    lang = options[:lang] || :en
    if options[:caption]
      caption = "<p><strong> #{langs[lang]} X.</strong> #{options[:caption]}."
    end

    width = options[:width] ? "width='#{options[:width]}'" : ''
    height = options[:height] ? "height='#{options[:height]}'" : ''
    alt = options[:alt] ? "alt='#{options[:alt]}'" : ''
    id = options[:label] ? "id='label_#{options[:label]}'" : ''
    %Q(
    <figure #{id}>
      <img src="/#{File.join('public', 'pictures', post, file)}"
           #{width}
           #{height}
           #{alt}
      >
      #{caption}
    </figure>
    )
  end

  def cite(id)
    "-- CITE PENDING --"
  end

  def section(title)
    "<h2>#{title}</h2>"
  end

  def subsection(title)
    "<h3>#{title}</h3>"
  end

  def subsubsection(title)
    "<h4>#{title}</h4>"
  end

  def add_bib(a, b, c, d = '')
    "--BIB PENDING--<br/>"
  end

  def generate_bib_table(lang = "ES")
    "PENDING"
  end

  def equation(eq, caption)
    "<div class='equation'>$#{eq}$</div>"
  end

  def finalize
  end

  def tex_set(k, v)

  end
end
