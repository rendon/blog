MaxPrimeFactor1(n)
  max = 1
  for d = 2 to n - 1
    if n MOD d == 0
      max = d
      while n MOD d == 0
        n = n/d
      if n > 1
        max = n
  return max
