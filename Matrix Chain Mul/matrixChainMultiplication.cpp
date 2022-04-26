#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void mulMatrix(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB,
               vector<vector<int>> &matrixC, int rowA, int columnA,
               int columnB) {  // standard matrix multiplication function
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

void order(int i, int j, int n, vector<vector<int>> brackets, int &mNumber, stack<vector<vector<int>>> &s,
           vector<vector<vector<int>>> &container) {    // determine the order by dynamic programming order
    if (i == j) {
        s.push(container[mNumber++]);   // push the current matrix into stack
        return;
    }

    order(i, brackets[j][i], n, brackets, mNumber, s, container);
    order(brackets[j][i] + 1, j, n, brackets, mNumber, s, container);
    popCalc(s); // pop two matrix in stack -> mul and then push back
}

void matrixChainMul(vector<int> &p, vector<vector<int>> &matrix) {
    int j, minimalK;
    for (int i = 0; i < p.size(); ++i) {
        matrix[i][i] = 0;       // set diagonal to 0
    }

    for (int diagonal = 1; diagonal < p.size(); ++diagonal) {
        for (int i = 1; i < p.size() - diagonal; ++i) {
            j = i + diagonal;
            minimalK = i;
            for (int k = i + 1; k < j; ++k) {
                if ((long) matrix[i][k] + (long) matrix[k + 1][j] +
                    (long) p[i - 1] * (long) p[j] * (long) p[k] <
                    (long) matrix[i][minimalK] + (long) matrix[minimalK + 1][j] +
                    (long) p[i - 1] * (long) p[j] * (long) p[minimalK]) {
                    minimalK = k;
                }
            }
            matrix[i][j] = matrix[i][minimalK] + matrix[minimalK + 1][j] + p[i - 1] * p[j] * p[minimalK];
            matrix[j][i] = minimalK;
        }
    }
}

vector<vector<int>>
matrixMulUsingChainOrder(vector<vector<int>> &matrix, vector<int> &p, vector<vector<vector<int>>> &container) {
    stack<vector<vector<int>>> stack;   // initialize the stack

    int mNumber = 0;

    order(1, p.size() - 1, p.size(), matrix, mNumber, stack, container);
    return stack.top();     // the result is store in stack top (that is, the last element in stack)
}

int main() {
    int sign = 0;
    scanf("%d", &sign);
    int matrixAmount;

    scanf("%d", &matrixAmount);
    vector<vector<vector<int>>> inputMatrix(matrixAmount, vector<vector<int>>(1, vector<int>(1, 0)));
    vector<int> p(matrixAmount + 1, 0);
    for (int i = 0; i <= matrixAmount; i++) {
        scanf("%d", &p[i]);
    }

    vector<vector<int>> minCostMatrix(p.size(), vector<int>(p.size(),
                                                            0));  // matrix stores minimum times to multiply at the upper triangle
    for (int i = 0; i < matrixAmount; ++i) {
        inputMatrix[i].resize(p[i]);
        for (int j = 0; j < p[i]; ++j) {
            inputMatrix[i][j].resize(p[i + 1]);
            for (int k = 0; k < p[i + 1]; ++k) {
                scanf("%d", &inputMatrix[i][j][k]);
            }
        }
    }
    matrixChainMul(p, minCostMatrix);   // calculate the minimum times needed in n matrix chain multiplication

    vector<vector<int>> ans = matrixMulUsingChainOrder(minCostMatrix, p,
                                                       inputMatrix); // start matrix multiplication using order we just calculate

    if (sign == 0) {
        // show answer
        printf("%d %d \n\n", p[0], p[p.size() - 1]);  // print how large is the last result
        for (int i = 0; i < ans.size(); ++i) {
            for (int j = 0; j < ans[0].size(); ++j) {
                printf("%d ", ans[i][j]);   // print every element in the last result
            }
            printf("\n");
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