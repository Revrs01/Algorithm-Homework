#include <bits/stdc++.h>

using namespace std;

struct Item {
private:
    int weight, profit;
public:
    Item() = default;

    Item(int weight, int profit) {
        this->weight = weight;
        this->profit = profit;
    }

    int getProfit() const {
        return profit;
    }

    int getWeight() const {
        return weight;
    }

    void setWeight(int num) {
        this->weight = num;
    }

    void setProfit(int num) {
        this->profit = num;
    }
};

Item currentCapacity(int weight, Item item[], int n) {
    int row, maxWeight;
    int map[n + 1][weight + 1];     // create DP table
    for (row = 0; row < n + 1; ++row) {     // travel through every row, from top -> bottom
        for (maxWeight = 0; maxWeight < weight + 1; ++maxWeight) {  // travel through every column, from left -> right
            if (row == 0 || maxWeight == 0) {
                map[row][maxWeight] = 0;    // Initialize
            } else if (item[row - 1].getWeight() <= maxWeight) {    // create the value column by column
                // choose a bigger one, (new item input + ) or (previous one)
                map[row][maxWeight] = max(
                        item[row - 1].getProfit() + map[row - 1][maxWeight - item[row - 1].getWeight()],
                        map[row - 1][maxWeight]);

            } else {
                // if bigger than current maxWeight, then copy from previous row
                map[row][maxWeight] = map[row - 1][maxWeight];
            }
        }
    }

    int totalProfit = map[n][weight];
    Item result = {};
    result.setProfit(totalProfit);  // store the totalProfit result
    maxWeight = weight;

    for (row = n; row > 0; --row) {
        if (totalProfit) {
            if (totalProfit == map[row - 1][maxWeight]) continue;
            // compare whether the value is same in the previous row
            else {
                //printf("%d %d\n",item[row-1].getWeight(),item[row-1].getProfit());
                // take out things from knapsack
                totalProfit -= item[row - 1].getProfit();
                maxWeight -= item[row - 1].getWeight();
                // subtract maxWeight means go left x blocks, which x is the object's weight I take out previously
            }
        }
    }
    result.setWeight(maxWeight);
    return result;
}

int main() {
    int size;
    int capacity;

    scanf("%d%d", &size, &capacity);

    Item array[size];
    for (int i = 0; i < size; ++i) {
        int w, p;
        scanf("%d%d", &w, &p);
        array[i] = Item(w, p);
    }

    Item ans = currentCapacity(capacity, array, size);
    printf("%d %d", capacity - ans.getWeight(), ans.getProfit());
    return 0;

}