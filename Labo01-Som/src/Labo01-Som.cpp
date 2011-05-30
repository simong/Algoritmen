//============================================================================
// Name        : Labo01-Som.cpp
// Author      : Simon Gaeremynck
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int sum(int* arr, int size) {
    if (size > 0) {
        int sum = arr[0] > 0 ? arr[0] : 0;
        int biggestSum = sum;
        for (int i = 1; i < size; i++) {
            if (sum + arr[i] > 0) {
                sum += arr[i];
            }
            else {
                sum = 0;
            }

            if (sum > biggestSum) {
                biggestSum = sum;
            }
        }
        return biggestSum;
    }
    else
        return 0;
}

int main() {
    const int AANTAL = 8;
    int arr[AANTAL] = { 3, 1, -5, 2, 4, -3, 5, -10 };

    int s = sum(arr, AANTAL);
    cout << "Biggest sum was: " << s << endl;
    return 0;
}
