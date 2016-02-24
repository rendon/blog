module Tex
  def ref(id)
    "PENDING"
  end

  def figure(a, b, c, d, e)
    "-- IMG PENDING --"
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

  def add_bib(a, b, c, d)
    "--BIB PENDING--<br/>"
  end

  def generate_bib_table(lang)
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
