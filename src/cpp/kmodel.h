//
// Created by sharabh on 2/10/26.
//

#include <format>
#include <vector>
#include <string>

#ifndef UNTITLED_KMODEL_H
#define UNTITLED_KMODEL_H

struct Item {
    std::string id;
    double value;
    double weight;

    Item() = default;
    Item(std::string id, double v, double w) : id(id), value(v), weight(w) {}
};

struct KConstraints {
    float capacity;

    KConstraints() = default;
    KConstraints(float c) : capacity(c) {}
};

struct KInputData {
    std::vector<Item> items;
    KConstraints constraints;

    KInputData() = default;
    KInputData(const std::vector<Item>& i, const KConstraints& c) : items(i), constraints(c) {}
};

struct KOutputData {
    std::vector<Item> selected_items;
    double total_value;
    double total_weight;
};


class KModel {
public:
    KInputData inputData;
    KOutputData results;

    KModel(const KInputData& id);
    KOutputData optimize();
};


#endif //UNTITLED_KMODEL_H