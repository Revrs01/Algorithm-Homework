#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

void createSpaceForVector(vector<vector<int>> &container, int i, int j) {
    container.resize(i);
    for (int k = 0; k < i; ++k) {
        container[k].resize(j, 0);
    }
}

void mulMatrix(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB,
               vector<vector<int>> &matrixC, int rowA, int columnA, int columnB) {
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < columnB; ++j) {
            matrixC[i][j] = 0;
            for (int k = 0; k < columnA; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void popCalc(stack<vector<vector<int>>> &stack) {
    vector<vector<int>> m2(stack.top().size(), vector<int>(stack.top()[0].size(), 0));
    m2 = stack.top();
    stack.pop();
    vector<vector<int>> m1(stack.top().size(), vector<int>(stack.top()[0].size(), 0));
    m1 = stack.top();
    stack.pop();
    vector<vector<int>> temp(m1.size(), vector<int>(m2[0].size(), 0));
    mulMatrix(m1, m2, temp, m1.size(), m1[0].size(), m2[0].size());
    stack.push(temp);
}

void putParentheses(int i, int j, int n, vector<vector<int>> brackets, int &mNumber, stack<vector<vector<int>>> &s,
                    vector<vector<vector<int>>> &container) {
    if (i == j) {
        s.push(container[mNumber++]);
        return;
    }

    putParentheses(i, brackets[j][i], n, brackets, mNumber, s, container);
    putParentheses(brackets[j][i] + 1, j, n, brackets, mNumber, s, container);
    popCalc(s);
}

void matrixChainMul(vector<int> &p, vector<vector<int>> &matrix) {

    for (int i = 0; i < p.size(); ++i) {
        matrix[i][i] = 0;       // set diagonal cost to 0
    }

    for (int chainLength = 2; chainLength < p.size(); ++chainLength) {
        for (int i = 1; i < p.size() - chainLength + 1; ++i) {
            int j = i + chainLength - 1;
            matrix[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int mpy = matrix[i][k] + matrix[k + 1][j] + p[i - 1] * p[j] * p[k];
                if (mpy < matrix[i][j]) {
                    matrix[i][j] = mpy;
                    matrix[j][i] = k;
                }
            }
        }
    }
}

vector<vector<int>> order(vector<vector<int>> &matrix, vector<int> &p, vector<vector<vector<int>>> &container) {
    stack<vector<vector<int>>> stack;
    int size = p.size();
    int mNumber = 0;   // starts after ')', which ASCII code is 42

    putParentheses(1, size - 1, size, matrix, mNumber, stack, container);
    return stack.top();
}

int main() {
    int sign = 0;
    cin >> sign;
    int matrixAmount;

    cin >> matrixAmount;
    vector<vector<vector<int>>> inputMatrix(matrixAmount, vector<vector<int>>(1, vector<int>(1, 0)));
    vector<int> p(matrixAmount + 1, 0);
    for (int i = 0; i <= matrixAmount; i++) {
        cin >> p[i];
    }

    vector<vector<int>> minCostMatrix(p.size(), vector<int>(p.size(), 0));
    for (int i = 0; i < matrixAmount; ++i) {
        createSpaceForVector(inputMatrix[i], p[i], p[i + 1]);
        for (int j = 0; j < p[i]; ++j) {
            for (int k = 0; k < p[i + 1]; ++k) {
                cin >> inputMatrix[i][j][k];
            }
        }
    }
    matrixChainMul(p, minCostMatrix);

    vector<vector<int>> ans = order(minCostMatrix, p, inputMatrix);

    if (sign == 0) {
        // show answer
        cout << p[0] << ' ' << p[p.size() - 1] << ' ' << endl << endl;
        for (int i = 0; i < ans.size(); ++i) {
            for (int j = 0; j < ans[0].size(); ++j) {
                cout << ans[i][j] << ' ';
            }
            cout << endl;
        }
    } else {
        clock_t start, end;
        start = clock();
        // don't need to show answer
        end = clock();
        double diff = end - start; // ms
        printf(" %lf,", diff);
    }

    return 0;
}