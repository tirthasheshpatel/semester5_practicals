n = 3
p = [3, 4, 5]


memo = [-1 for _ in range(n+1)]
memo[0] = 0

def f(n):
	if memo[n] != -1: return memo[n]
	memo[n] = max([p[i] + f(n-i-1) for i in range(0, n)])
	return memo[n]


print(f"maximum revenue for n={n} is {f(n)}")

