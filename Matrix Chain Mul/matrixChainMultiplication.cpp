#include <iostream>
#include <vector>

using namespace std;
int matrixAmount;
vector<vector<int>> cutLoc;
int mpy(int i,int j, vector<vector<int>> currentTimes){


    return i;
}
vector<vector<int>> calcMinMultiplicationTimes(vector<int> p) {
    vector<vector<int>> mulTimes;
    vector<vector<int>> cutLocation;
    mulTimes.resize(matrixAmount, vector<int>(matrixAmount, 0));
    cutLocation.resize(matrixAmount, vector<int>(matrixAmount, 0));


    return mulTimes;
}

void calcCutLocation(int i,int j, int k){
    cutLoc.resize(matrixAmount,vector<int>(matrixAmount,0));
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


}