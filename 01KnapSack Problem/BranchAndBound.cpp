#include <bits/stdc++.h>
#include <queue>

using namespace std;

struct Item {
private:
    int weight, profit;
public:
    Item() = default;

    Item(int w, int p) {
        this->weight = w;
        this->profit = p;
    }

    int getWeight() const { return weight; }

    int getProfit() const { return profit; }

    int setWeight(int w) {
        this->weight = w;
    }

    int setProfit(int p) {
        this->profit = p;
    }
};

struct queueNode {
private:
    int level, profit, bound, weight;
public:
    void setLevel(int l) {
        this->level = l;
    }

    void setProfit(int p) {
        this->profit = p;
    }

    void setBound(int b) {
        this->bound = b;
    }

    void setWeight(int w) {
        this->weight = w;
    }

    int getLevel() const { return level; }

    int getBound() const { return bound; }

    int getWeight() const { return weight; }

    int getProfit() const { return profit; }
};

typedef queueNode Node;

int bound(Node node, int n, int capacity, Item item[]) {
    if (node.getWeight() >= capacity) return 0;

    int profitBound = node.getProfit();
    int index = node.getLevel() + 1;
    int totalWeight = node.getWeight();

    while (index < n && (totalWeight + item[index].getWeight()) <= capacity) {
        totalWeight += item[index].getWeight();
        profitBound += item[index].getProfit();
        index++;
    }

    if (index < n) {
        profitBound += (capacity - totalWeight) * item[index].getProfit() / item[index].getWeight();
    }

    return profitBound;
}

bool compare(Item r1, Item r2) {
    return (double) r1.getProfit() / (double) r1.getWeight() > (double) r2.getProfit() / (double) r2.getWeight();
}

Item zeroOneKnapsack(int capacity, Item item[], int n) {
    sort(item, item + n, compare);
    Node a, b;
    queue<Node> queue;
    Item result = {};

    a.setLevel(-1);
    a.setProfit(0);
    a.setWeight(0);
    queue.push(a);
    int maxProfit = 0;

    while (!queue.empty()) {
        a = queue.front();
        queue.pop();
        if (a.getLevel() < 0) b.setLevel(0);
        if (b.getLevel() == n - 1) continue;
        b.setLevel(a.getLevel() + 1);

        b.setWeight(a.getWeight() + item[b.getLevel()].getWeight());
        b.setProfit(a.getProfit() + item[b.getLevel()].getProfit());

        if (b.getWeight() <= capacity && b.getProfit() > maxProfit) {
            maxProfit = b.getProfit();
            result.setWeight(b.getWeight());
            //cout << b.getWeight() <<' ';
        }
        b.setBound(bound(b, n, capacity, item));
        if (b.getBound() > maxProfit) {
            queue.push(b);
        }


        b.setWeight(a.getWeight());
        b.setProfit(a.getProfit());
        b.setBound(bound(b, n, capacity, item));
        if (b.getBound() > maxProfit) {
            queue.push(b);
        }
    }
    result.setProfit(maxProfit);
    return result;
}

int main() {
    int size, capacity;

    scanf(" %d%d", &size, &capacity);
    Item array[size];
    int w, p;
    for (int i = 0; i < size; ++i) {
        scanf(" %d%d", &w, &p);
        array[i] = Item(w, p);
    }
    Item ans = zeroOneKnapsack(capacity, array, size);
    printf("%d %d", ans.getWeight(), ans.getProfit());
}