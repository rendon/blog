# frozen_string_literal: true

# Functions for rendering citations.
module Tex
  def ref(id)
    <<~HTML
      <a href='#label_#{id}'>
        <span class='tex-ref' name='ref_#{id}'>?</span>
      </a>
    HTML
  end

  def figure(post, file, opts = {})
    @tex.fig_num += 1
    langs = { en: 'Figure ', es: 'Figura ' }
    lang = opts[:lang] || :en

    if opts[:caption]
      caption = "<p><strong>#{langs[lang]} #{@tex.fig_num}.</strong> #{opts[:caption]}.</p>"
    end

    _figure(
      id: _id(opts), post: post, caption: caption, file: file,
      width: _width(opts), height: _height(opts), alt: _alt(opts)
    )
  end

  def cite(id)
    <<~HTML
      <a href='#label_#{id}'>
        <span class='tex-cite' name='cite_#{id}'>?</span>
      </a>
    HTML
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

  def generate_bib_table(_lang = :es)
    at = { en: 'Available at ', es: 'Disponible en ' }
    html = "<table class='table'>"
    @tex.bibs.each_with_index do |bib, id|
      available_at = ''
      unless blank?(bib[:url])
        available_at = %(, #{at[:lang]} <a  href='#{bib[:url]}' target='_blank'>#{bib[:url]}</a>)
      end
      html += bib_row(id, bib, available_at)
    end
    html += '</table>'
  end

  def equation(equ, _caption)
    "<div class='equation'>$#{equ}$</div>"
  end

  def finalize; end

  def tex_set(key, value); end

  private

  def blank?(str)
    str.nil? || str.empty?
  end

  def _figure(params = {})
    <<~HTML
      <figure #{params[:id]}>
        <img src="/#{File.join('public', 'pictures', params[:post], params[:file])}"
            #{params[:width]}
            #{params[:height]}
            #{params[:alt]}
        >
        #{params[:caption]}
      </figure>
    HTML
  end

  def bib_row(id, bib, available_at)
    <<~HTML
      <tr>
        <td><a id='label_#{bib[:label]}'></a>[#{id + 1}]</td>
        <td>#{bib[:author].upcase}, <em>#{bib[:title]}</em>#{available_at}</td>
      </tr>
    HTML
  end

  def _width(opts)
    opts[:width] ? "width='#{opts[:width]}'" : ''
  end

  def _height(opts)
    opts[:height] ? "height='#{opts[:height]}'" : ''
  end

  def _alt(opts)
    opts[:alt] ? "alt='#{opts[:alt]}'" : ''
  end

  def _id(opts)
    opts[:label] ? "id='label_#{opts[:label]}'" : ''
  end
end
