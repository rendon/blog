MaxPrimeFactor3(n)
  max = 1
  if (n MOD 2 == 0)
    max = 2
    while n MOD 2 == 0
      n = n / 2
  d = 3
  while d <= sqrt(n)
    if n MOD d == 0
      max = d
      while n MOD d == 0
        n = n/d
    d = d + 2
  if n > 1
    max = n
  return max
