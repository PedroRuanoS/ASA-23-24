'''
   3º Projeto ASA 2023/2024

   Autores:
       Pedro Silveira - 106642
       Gonçalo Aleixo - 106900

'''

from pulp import LpProblem, LpMaximize, LpVariable, lpSum, GLPK, LpInteger, value

def solve_problem(t, p, max_toys, x, y, toys, packs):
    prob = LpProblem("Max Profit", LpMaximize)

    toy_profits = [toys[i]['l'] for i in range(t)]
    prob += lpSum([x[i] * toy_profits[i] for i in range(t)]) + lpSum([y[i] * (packs[i]['profit']
    - lpSum([toy_profits[toy - 1] for toy in packs[i]['items']])) for i in range(p)])

    prob += lpSum(x.values()) <= max_toys
    pack_items_set = [set(packs[i]['items']) for i in range(p)]
    for i in range(t):
        prob += x[i] >= lpSum([y[j] for j in range(p) if i + 1 in pack_items_set[j]])

    solver = GLPK(msg=0) 
    prob.solve(solver)
    return value(prob.objective)

def main():
    t, p, max_toys = map(int, input().split())

    toy_vars, toys = {}, {}
    for i in range(t):
        profit, limit = map(int, input().split())
        toys[i] = {'l': profit, 'c': limit}
        toy_vars[i] = LpVariable(f"toy_vars{i}", 0, toys[i]['c'], LpInteger)

    pack_vars, packages = {}, {}
    for i in range(p):
        items_profit = list(map(int, input().split()))
        items, profit = items_profit[:-1], items_profit[-1]
        packages[i] = {'items': items, 'profit': profit}
        pack_vars[i] = LpVariable("pack_vars%d" % i, 0, None, LpInteger)

    max_profit = solve_problem(t, p, max_toys, toy_vars, pack_vars, toys, packages)
    print(max_profit)

if __name__ == "__main__":
    main()
