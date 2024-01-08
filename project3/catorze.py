from pulp import *

t, p, max_producao = map(int, input().split())

toys = [list(map(int, input().split())) for _ in range(t)]
    
packs = [list(map(int, input().split())) for _ in range(p)]
    
# Problema
problem = LpProblem("Max Profit Problem", LpMaximize)

# Criar variáveis de decisão para a quantidade de brinquedos
x = [LpVariable("x%d" % i, 0, toys[i][1], LpInteger) for i in range(t)]

# Criar variáveis de decisão para a quantidade de pacotes especiais
y = [LpVariable("y%d" % i, 0, None, LpInteger) for i in range(p)]

# Função objetivo
problem += lpSum([x[i] * toys[i][0] for i in range(t)]) + lpSum([y[i] * (packs[i][3] - lpSum([toys[toy - 1][0] for toy in packs[i][:3]])) for i in range(p)])

# Restriçāo: limites de produçāo
problem += lpSum([x[i] for i in range(t)]) <= max_producao

# Restriçāo: limites de produçāo de pacotes
for i in range(t):
    problem += x[i] >= lpSum([y[j] for j in range(p) if i + 1 in packs[j][:3]])

# Resolver o problema
solver = GLPK(msg=0) 
max_profit = problem.solve(solver)
print(value(problem.objective))
