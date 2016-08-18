module Tex
  def ref(id)
    %(<a href='#label_#{id}'>
        <span class='tex-ref' name='ref_#{id}'>?</span>
      </a>)
  end

  def figure(post, file, options = {})
    @tex.fig_num += 1
    langs = { en: 'Figure ', es: 'Figura ' }
    lang = options[:lang] || :en
    if options[:caption]
      caption = %Q(
      <p>
        <strong> #{langs[lang]} #{@tex.fig_num}.</strong> #{options[:caption]}.
      </p>
      )
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
    %(<a href='#label_#{id}'>
        <span class='tex-cite' name='cite_#{id}'>?</span>
      </a>)
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

  def add_bib(label, author, title, url = '')
    @tex.bibs << { label: label, author: author, title: title, url: url }
  end

  def generate_bib_table(lang = :es)
    at = { en: 'Available at ', es: 'Disponible en ' }
    html = "<table class='table'>"
    @tex.bibs.each_with_index do |bib, id|
      available_at = ''
      if bib[:url] && !bib[:url].empty?
        available_at = %(,
          #{at[:lang]} <a  href='#{bib[:url]}' target='_blank'>#{bib[:url]}</a>
        )
      end
      html += %(
      <tr>
        <td><a id='label_#{bib[:label]}'></a>[#{id + 1}]</td>
        <td>#{bib[:author].upcase}, <em>#{bib[:title]}</em>#{available_at}</td>
      </tr>
      )
    end
    html += '</table>'
  end

  def equation(eq, caption)
    "<div class='equation'>$#{eq}$</div>"
  end

  def finalize
  end

  def tex_set(k, v)
  end
end
