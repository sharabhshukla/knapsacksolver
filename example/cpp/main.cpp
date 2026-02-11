//
// Created by sharabh on 2/11/26.
//

#include <iostream>
#include "kmodel.h"
#include "kmodel.cpp"

int main(int argc, char** argv) {

    // Create test items
    std::vector<Item> items = {
        Item("A", 60, 10),
        Item("B", 100, 20),
        Item("C", 120, 30)
    };

    // Capacity = 50
    KConstraints constraints(50);

    KInputData input(items, constraints);

    // Build model
    KModel model(input);

    // Solve
    KOutputData result = model.optimize();

    // Print results
    std::cout << "\nSelected items:\n";
    for (const auto& item : result.selected_items) {
        std::cout << "  " << item.id
                  << " (value=" << item.value
                  << ", weight=" << item.weight
                  << ")\n";
    }

    std::cout << "\nTotal value: " << result.total_value << std::endl;
    std::cout << "Total weight: " << result.total_weight << std::endl;

    return 0;
}
