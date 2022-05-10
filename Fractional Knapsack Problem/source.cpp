#include <bits/stdc++.h>

using namespace std;

struct Item {
private:
    int value, weight;
public:
    Item() = default;  // null constructor, for initialize

    Item(int weight, int value) {
        this->weight = weight;
        this->value = value;
    }

    int getValue() const {
        return value;
    }

    int getWeight() const {
        return weight;
    }
};

bool compare(Item r1, Item r2) {
    return (double) r1.getValue() / (double) r1.getWeight() > (double) r2.getValue() / (double) r2.getWeight();
}

double fractionalKnapsack(int capacity, Item array[], int n) {
    sort(array, array + n, compare);    // sort the array

    double result = 0;

    for (int i = 0; i < n; ++i) {
        if (array[i].getWeight() <= capacity) {     // if capacity is enough to put in the next item, then put in
            capacity -= array[i].getWeight();
            result += array[i].getValue();
        } else {
            result += array[i].getValue() * ((double) capacity / (double) array[i].getWeight());
            break;  // there's no space for the next item, function ends
        }
    }
    return result;
}

int main() {

    int howManyThings,backpackCapacity;

    scanf("%d", &howManyThings);
    scanf("%d", &backpackCapacity);

    Item array[howManyThings];
    int weight, value;

    for (int i = 0; i < howManyThings; ++i) {
        scanf("%d%d", &weight, &value);
        array[i] = Item(weight, value);
    }

    printf("%.6f", fractionalKnapsack(backpackCapacity, array, howManyThings));

    return 0;
}