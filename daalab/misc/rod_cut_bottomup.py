n = 3
p = [3, 4, 5]

def f(n):
	memo = [-1 for _ in range(n+1)]
	memo[0] = 0
	for i in range(1, n+1):
		memo[i] = max(p[j] + memo[i-j-1] for j in range(0, i))
	return memo[n]

print(f"maximum revenue for n={n} is {f(n)}")

