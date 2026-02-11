//
// Created by sharabh on 2/10/26.
//

#include "kmodel.h"
#include <ortools/linear_solver/linear_solver.h>
#include <ortools/init/init.h>

KModel::KModel(const KInputData& id) : inputData(id) {}

KOutputData KModel::optimize() {

        operations_research::MPSolver* solver = operations_research::MPSolver::CreateSolver("CBC");

        const int noItems = inputData.items.size();
        std::vector<operations_research::MPVariable*> itemChoosen;
        itemChoosen.reserve(noItems);

        //Create decision variables
        for (const auto& item : inputData.items) {
             itemChoosen.push_back(solver->MakeBoolVar(std::string("itemChoosen") + item.id));
        }
        operations_research::MPVariable* const totalWeight = solver->MakeIntVar(0, inputData.constraints.capacity,
            "totalWeight");
        operations_research::MPVariable* const totalValue = solver->MakeIntVar(0, solver->infinity(),
            "totalValue");


        //Create constraints
        operations_research::MPConstraint* const valueconstr = solver->MakeRowConstraint(0, 0,
            "valueconstr");
        valueconstr->SetCoefficient(totalValue, 1);
        for (int i = 0; i < noItems; i++) {
            valueconstr->SetCoefficient(itemChoosen[i],  -1 * inputData.items[i].value);
        }

        operations_research::MPConstraint* const weightconstr = solver->MakeRowConstraint(0, 0,
            "weightconstr");
        weightconstr->SetCoefficient(totalWeight, 1);
        for (int i = 0; i < noItems; i++) {
            weightconstr->SetCoefficient(itemChoosen[i],  -1 * inputData.items[i].weight);
        }

        operations_research::MPObjective* const objective = solver->MutableObjective();
        objective->SetCoefficient(totalValue, 1);
        objective->SetMaximization();

        LOG(INFO) << "Knapsack Optimization Model built";
        LOG(INFO) << "Number of Variables: " << solver->NumVariables() << std::endl;
        LOG(INFO) << "Number of Constraints: " << solver->NumConstraints() << std::endl;

        //Enable solver logging to console
        solver->EnableOutput();

        solver->Solve();

        // collect the results
        results.selected_items.reserve(noItems);
        for (int i = 0; i < noItems; i++) {
            if (itemChoosen[i]->solution_value() > 0.5) {
                results.selected_items.push_back(inputData.items[i]);
            }
        }
        results.total_weight = totalWeight->solution_value();
        results.total_value = totalValue->solution_value();
        return results;
}
