#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int value, weight;
};

// Comparator to sort items by value/weight ratio in descending order
bool compare(Item a, Item b) {
    double r1 = (double)a.value / (double)a.weight;
    double r2 = (double)b.value / (double)b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, std::vector<Item>& items) {
    // 1. Sort items by ratio
    std::sort(items.begin(), items.end(), compare);

    double finalValue = 0.0;
    for (auto& item : items) {
        // 2. If item fits fully, add it
        if (item.weight <= W) {
            W -= item.weight;
            finalValue += item.value;
        } 
        // 3. If it doesn't fit, take the fractional part
        else {
            finalValue += item.value * ((double)W / item.weight);
            break; // Knapsack is full
        }
    }
    return finalValue;
}

int main() {
    int W = 50; 
    std::vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    std::cout << "Max value: " << fractionalKnapsack(W, items) << std::endl;
    return 0;
}
