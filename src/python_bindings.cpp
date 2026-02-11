#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "kmodel.h"

namespace py = pybind11;

PYBIND11_MODULE(cknapsacksolver, m) {
    m.doc() = "Python bindings for Knapsack Solver using OR-Tools";

    // Expose Item struct
    py::class_<Item>(m, "Item")
        .def(py::init<>(), "Default constructor")
        .def(py::init<std::string, float, float>(),
             py::arg("id"), py::arg("value"), py::arg("weight"),
             "Constructor with id, value, and weight")
        .def_readwrite("id", &Item::id, "Item identifier")
        .def_readwrite("value", &Item::value, "Item value")
        .def_readwrite("weight", &Item::weight, "Item weight")
        .def("__repr__", [](const Item &item) {
            return "Item(id='" + item.id + "', value=" +
                   std::to_string(item.value) + ", weight=" +
                   std::to_string(item.weight) + ")";
        });

    // Expose KConstraints struct
    py::class_<KConstraints>(m, "KConstraints")
        .def(py::init<>(), "Default constructor")
        .def(py::init<float>(),
             py::arg("capacity"),
             "Constructor with capacity")
        .def_readwrite("capacity", &KConstraints::capacity, "Knapsack capacity")
        .def("__repr__", [](const KConstraints &c) {
            return "KConstraints(capacity=" + std::to_string(c.capacity) + ")";
        });

    // Expose KInputData struct
    py::class_<KInputData>(m, "KInputData")
        .def(py::init<>(), "Default constructor")
        .def(py::init<const std::vector<Item>&, const KConstraints&>(),
             py::arg("items"), py::arg("constraints"),
             "Constructor with items and constraints")
        .def_readwrite("items", &KInputData::items, "List of items")
        .def_readwrite("constraints", &KInputData::constraints, "Knapsack constraints")
        .def("__repr__", [](const KInputData &data) {
            return "KInputData(items=[" + std::to_string(data.items.size()) +
                   " items], capacity=" + std::to_string(data.constraints.capacity) + ")";
        });

    // Expose KOutputData struct (read-only)
    py::class_<KOutputData>(m, "KOutputData")
        .def(py::init<>(), "Default constructor")
        .def_readonly("selected_items", &KOutputData::selected_items, "Selected items")
        .def_readonly("total_value", &KOutputData::total_value, "Total value of selected items")
        .def_readonly("total_weight", &KOutputData::total_weight, "Total weight of selected items")
        .def("__repr__", [](const KOutputData &data) {
            return "KOutputData(selected_items=[" + std::to_string(data.selected_items.size()) +
                   " items], total_value=" + std::to_string(data.total_value) +
                   ", total_weight=" + std::to_string(data.total_weight) + ")";
        });

    // Expose KModel class
    py::class_<KModel>(m, "KModel")
        .def(py::init<const KInputData&>(),
             py::arg("input_data"),
             "Constructor with input data")
        .def_readwrite("inputData", &KModel::inputData, "Input data for the model")
        .def_readwrite("results", &KModel::results, "Results from optimization")
        .def("optimize", &KModel::optimize,
             "Solve the knapsack problem and return the results")
        .def("__repr__", [](const KModel &) {
            return "KModel(knapsack optimization model)";
        });
}
