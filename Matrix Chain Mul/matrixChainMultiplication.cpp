#include <iostream>
#include <vector>
#include <stack>

using namespace std;
int matrixAmount;
vector<vector<int>> cutLoc;

void matrixChainMul(vector<int> &p) {
    int matrix[p.size()][p.size()];

    for (int i = 0; i < p.size(); ++i) {
        matrix[0][i] = 0;
        matrix[i][0] = 0;
        matrix[i + 1][i + 1] = 0;       // set diagonal cost to 0
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

    cout << "Min Cost = " << matrix[1][p.size() - 1];
}

void calcCutLocation(int i, int j, int k) {
    cutLoc.resize(matrixAmount, vector<int>(matrixAmount, 0));
    cutLoc[i][j] = k;
}

int main() {

    cin >> matrixAmount;
    vector<int> p;
    p.resize(matrixAmount, 0);
    for (int i = 0; i < matrixAmount; i++) {
        cin >> p[i];
    }

    //vector<vector<int>> getTimes = calcMinMultiplicationTimes(p);
    matrixChainMul(p);

}