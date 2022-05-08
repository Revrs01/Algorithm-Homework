#include <iostream>
#include <stack>

using namespace std;

struct node {
    int **matrix;
    int row;
    int col;
};

void mulMatrix(node matrixA, node matrixB, node matrixC) {  // standard matrix multiplication function
    for (int i = 0; i < matrixA.row; ++i) {
        for (int j = 0; j < matrixB.col; ++j) {
            matrixC.matrix[i][j] = 0;
            for (int k = 0; k < matrixA.col; ++k) {
                matrixC.matrix[i][j] += matrixA.matrix[i][k] * matrixB.matrix[k][j];
            }
        }
    }
}

void order(int i, int j, int n, int **&multiOrder, int &mNumber, stack<node> &s,
           int ***&matrix, int *&p) {    // determine the order by dynamic programming order
    if (i == j) {
        node input{};
        input.row = p[mNumber];
        input.col = p[mNumber + 1];
        input.matrix = matrix[mNumber++];
        s.push(input);   // push the current matrix into stack
        return;
    }

    order(i, multiOrder[i][j], n, multiOrder, mNumber, s, matrix, p);
    order(multiOrder[i][j] + 1, j, n, multiOrder, mNumber, s, matrix, p);

    node m2 = s.top();
    s.pop();

    node m1 = s.top();
    s.pop();

    node result{};
    result.matrix = (int **) malloc(m1.row * sizeof(int *));
    result.row = m1.row;
    result.col = m2.col;
    for (int k = 0; k < result.row; ++k) {
        result.matrix[k] = (int *) malloc(result.col * sizeof(int));
    }
    mulMatrix(m1, m2, result);
    s.push(result);
}

void mulMatrix(int *&p, int **&cost, int **&multiOrder, int pSize) {
    int j, minK;
    for (int i = 0; i < pSize; ++i) {
        cost[i][i] = 0;       // set diagonal to 0
    }

    for (int diagonal = 1; diagonal < pSize; ++diagonal) {
        for (int i = 1; i < pSize - diagonal; ++i) {
            j = i + diagonal;
            minK = i;
            for (int k = i + 1; k < j; ++k) {
                if ((long) cost[i][k] + (long) cost[k + 1][j] +
                    (long) p[i - 1] * (long) p[j] * (long) p[k] <
                    (long) cost[i][minK] + (long) cost[minK + 1][j] +
                    (long) p[i - 1] * (long) p[j] * (long) p[minK]) {
                    minK = k;
                }
            }
            cost[i][j] = cost[i][minK] + cost[minK + 1][j] + p[i - 1] * p[j] * p[minK];
            multiOrder[i][j] = minK;
        }
    }
}

int main() {

    int signal;
    scanf("%d", &signal);
    int matrixAmount;
    scanf("%d", &matrixAmount);

    int *p = (int *) malloc((matrixAmount + 1) * sizeof(int));
    for (int i = 0; i < matrixAmount + 1; ++i) {
        scanf("%d", &*(p + i));
    }
    int pSize = matrixAmount + 1;

    int **multiOrder = (int **) malloc((matrixAmount + 1) * sizeof(int *));
    int **cost = (int **) malloc((matrixAmount + 1) * sizeof(int *));

    for (int i = 0; i < matrixAmount + 1; ++i) {
        multiOrder[i] = (int *) malloc((matrixAmount + 1) * sizeof(int));
        cost[i] = (int *) malloc((matrixAmount + 1) * sizeof(int));
    }

    int ***matrix = (int ***) malloc(matrixAmount * sizeof(int **));
    for (int i = 0; i < matrixAmount; ++i) {
        matrix[i] = (int **) malloc(*(p + i) * sizeof(int *));
        for (int j = 0; j < *(p + i); ++j) {
            matrix[i][j] = (int *) malloc(*(p + i + 1) * sizeof(int));
            for (int k = 0; k < *(p + i + 1); ++k) {
                scanf("%d", &matrix[i][j][k]);
            }
        }
    }

    stack<node> stack;
    mulMatrix(p, cost, multiOrder, pSize);

    int count = 0;
    order(1, pSize - 1, pSize, multiOrder, count, stack, matrix, p);
    node ans = stack.top();

    cout << ans.row << ' ' << ans.col << ' ' << endl << endl;
    for (int i = 0; i < ans.row; ++i) {
        for (int j = 0; j < ans.col; ++j) {
            cout << ans.matrix[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}