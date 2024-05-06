#include "SortingAlgorithm.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace SortLibrary;

int main(int argc, char *argv[])
{
    const unsigned int n = stoi(argv[1]); // size of vectors taken into consideration
    cout << "Size of vectors: " << n << endl;
    const unsigned int iter = 5000;
    cout << "Number of iterations: " << iter << endl << endl;

    double meanTime_BS[4] = {0,0,0,0};
    double meanTime_MS[4] = {0,0,0,0};

    for(unsigned int it=0;it<iter;it++){
        // Case 1: best case scenario
        // we compare the performances of BubbleSort and MergeSort algorithms on vectors whose elements are already in increasing order
        vector<int> v1_1(n);
        iota(v1_1.begin(),v1_1.end(),rand()%100);
        vector<int> v2_1 = v1_1; // v2_1 is a copy of v1_1

        std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now();
        BubbleSort(v1_1);
        std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
        meanTime_BS[0] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
        t_begin = std::chrono::steady_clock::now();
        MergeSort(v2_1);
        t_end = std::chrono::steady_clock::now();
        meanTime_MS[0] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

        // Case 2: we create an ordered vector and make some of its elements random numbers
        vector<int> v1_2(n);
        iota(v1_2.begin(),v1_2.end(),rand()%100);
        for(unsigned int i=0;i<n;i++) {
            const unsigned int temp = rand()%3; // temp==0 or temp==1 or temp==2
            if(temp==0) { // if temp==0, change v1_2[i] to a random number
                v1_2[i] = rand();
            }
        }
        vector<int> v2_2 = v1_2; // v2 is a copy of v1

        t_begin = std::chrono::steady_clock::now();
        BubbleSort(v1_2);
        t_end = std::chrono::steady_clock::now();
        meanTime_BS[1] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
        t_begin = std::chrono::steady_clock::now();
        MergeSort(v2_2);
        t_end = std::chrono::steady_clock::now();
        meanTime_MS[1] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

        // Case 3: completely random vectors
        vector<int> v1_3(n);
        for(unsigned int i=0;i<n;i++){
            v1_3[i] = rand()%100;
        }
        vector<int> v2_3 = v1_3; // v2 is a copy of v1

        t_begin = std::chrono::steady_clock::now();
        BubbleSort(v1_3);
        t_end = std::chrono::steady_clock::now();
        meanTime_BS[2] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
        t_begin = std::chrono::steady_clock::now();
        MergeSort(v2_3);
        t_end = std::chrono::steady_clock::now();
        meanTime_MS[2] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

        // Case 4: worst case scenario
        // we consider vectors whose elements are in decreasing order
        vector<int> v1_4(n);
        unsigned int temp = rand()%100;
        generate(v1_4.begin(),v1_4.end(),[&temp](){return temp--;});
        vector<int> v2_4 = v1_4; // v2_4 is a copy of v1_4

        t_begin = std::chrono::steady_clock::now();
        BubbleSort(v1_4);
        t_end = std::chrono::steady_clock::now();
        meanTime_BS[3] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
        t_begin = std::chrono::steady_clock::now();
        MergeSort(v2_4);
        t_end = std::chrono::steady_clock::now();
        meanTime_MS[3] += std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

    }
    for(unsigned int i=0;i<4;i++) {
        cout << "Case " << i+1 << endl;
        meanTime_MS[i] = meanTime_MS[i]/iter;
        meanTime_BS[i] = meanTime_BS[i]/iter;
        cout << "BubbleSort mean elapsed time in microseconds: " << meanTime_BS[i] << endl;
        cout << "MergeSort mean elapsed time in microseconds: " << meanTime_MS[i] << endl << endl;
    }
    return 0;
}
