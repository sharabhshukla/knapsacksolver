#!/usr/bin/env python3
"""
Basic example of using the knapsacksolver package.

This example demonstrates how to solve a simple knapsack problem
where you need to maximize value while staying within a weight constraint.
"""

from knapsacksolver import Item, KConstraints, KInputData, KModel


def main():
    print("=" * 60)
    print("Knapsack Solver - Basic Example")
    print("=" * 60)

    # Define items with (id, value, weight)
    items = [
        Item("laptop", 500, 2.5),
        Item("camera", 300, 1.5),
        Item("book", 50, 0.5),
        Item("tablet", 400, 1.0),
        Item("headphones", 100, 0.3),
        Item("charger", 30, 0.2),
        Item("water_bottle", 10, 0.5),
    ]

    print("\nAvailable items:")
    print(f"{'ID':<15} {'Value':>10} {'Weight':>10}")
    print("-" * 40)
    for item in items:
        print(f"{item.id:<15} {item.value:>10.1f} {item.weight:>10.2f}")

    # Set knapsack capacity
    capacity = 5.0
    print(f"\nKnapsack capacity: {capacity} kg")

    # Create input data
    constraints = KConstraints(capacity)
    input_data = KInputData(items, constraints)

    print("\nSolving...")

    # Create and solve the model
    model = KModel(input_data)
    result = model.optimize()

    # Display results
    print("\n" + "=" * 60)
    print("RESULTS")
    print("=" * 60)
    print(f"\nTotal value:  ${result.total_value:.2f}")
    print(f"Total weight: {result.total_weight:.2f} kg")
    print(f"Items selected: {len(result.selected_items)} out of {len(items)}")

    print("\nSelected items:")
    print(f"{'ID':<15} {'Value':>10} {'Weight':>10}")
    print("-" * 40)
    for item in result.selected_items:
        print(f"{item.id:<15} {item.value:>10.1f} {item.weight:>10.2f}")

    print("\n" + "=" * 60)


if __name__ == "__main__":
    main()
