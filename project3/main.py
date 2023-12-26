import pulp

def solve_linear_programming(t, p, max_toys, toys, packages):
    # Initialize LP problem
    prob = pulp.LpProblem("MaximumProfit", pulp.LpMaximize)

    # Create decision variables for toys and packages
    toy_vars = [pulp.LpVariable(f"toy_{i}", 0, toys[i][1]) for i in range(t)]
    package_vars = [pulp.LpVariable(f"package_{i}", 0, cat="Integer") for i in range(p)]

    # Objective function: Maximize profit
    prob += pulp.lpSum([toys[i][0] * toy_vars[i] for i in range(t)] +
                       [packages[i][3] * package_vars[i] for i in range(p)])

    # Constraints
    # Constraint on total number of toys produced
    prob += pulp.lpSum([toy_vars[i] for i in range(t)]) <= max_toys

    # Constraints for packages
    for i in range(p):
        ijk = packages[i][:3]
        prob += pulp.lpSum([toy_vars[j-1] for j in ijk]) >= 3 * package_vars[i]

    # Solve the problem
    prob.solve(pulp.PULP_CBC_CMD(msg=False))  # Suppress detailed output

    # Return the result
    return pulp.value(prob.objective) if prob.status == 1 else "No feasible solution found"

def main():
    # Read input
    t, p, max_toys = map(int, input().split())
    toys = [list(map(int, input().split())) for _ in range(t)]
    packages = [list(map(int, input().split())) for _ in range(p)]

    # Solve and output the result
    print(int(solve_linear_programming(t, p, max_toys, toys, packages)))

if __name__ == "__main__":
    main()
