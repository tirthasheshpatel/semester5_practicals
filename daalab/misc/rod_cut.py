n = 3
p = [3, 4, 5]


def f(n): return 0 if n == 0 else max([p[i] + f(n-i-1) for i in range(0, n)])

print(f"max revenue for n={n} is {f(n)}")

