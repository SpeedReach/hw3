//
// Created by gomil on 2022/12/24.
//

#ifndef SCHOOLHW_SORTEDARRAYS_H
#define SCHOOLHW_SORTEDARRAYS_H

#include "Collection.h"
#include <vector>
#include <cmath>
#include "iostream"

using namespace std;

class SortedArrays: public Collection{

public:
    void insert(int value);
    bool search(int value);
    void print();
    void printTmp();
    string name(){
        return "SortedArrays";
    }

    ~SortedArrays();

    SortedArrays(){
        arrays = new int*[30];
        tmpArrays = new int*[30];
        createDepth(0);
    }

private:
    int** arrays;
    int** tmpArrays;
    //allocate depth 層的 array跟tmp array
    void createDepth(int depth);
    //把arrays 跟 tmpArrays的depth層 merge到 depth+1 層
    void merge(int depth);
    //把一個array的所有值設定為0
    void clearArray(int* array,int n);
    //把tmpArrays的depth層copy到arrays的depth層
    void copyTmpToMain(int depth);
    //當前allocate到的層數
    int maxDepth = 0;
    bool bsearch(int* array,int target,int l,int r);
};

SortedArrays::~SortedArrays(){
    for(int i=0;i< maxDepth;i++){
        delete[] arrays;
        delete[] tmpArrays;
    }
}

void SortedArrays::insert(int value) {

    if(arrays[0][0] == -1) {
        arrays[0][0] = value;
        return;
    }
    else tmpArrays[0][0] = value;

    for(int i=0;i<= maxDepth;i++){
        merge(i);
        if(arrays[i+1][0] == -1){
            copyTmpToMain(i+1);
            return;
        }
    }
}

void SortedArrays::copyTmpToMain(int depth) {
    for(int i=0;i< pow(2,depth);i++){
        arrays[depth][i] = tmpArrays[depth][i];
    }
}

void SortedArrays::createDepth(int depth) {
    int n = pow(2,depth);
    arrays[depth] = new int[n];
    clearArray(arrays[depth],n);
    tmpArrays[depth] =  new int[n];
    clearArray(tmpArrays[depth],n);
    maxDepth = depth;
}

void SortedArrays::clearArray(int *array, int n) {
    for(int i=0;i<n;i++){
        array[i] = -1;
    }
}

void SortedArrays::print() {
    for(int i=0;i<= maxDepth ;i++){
        int n = pow(2,i);
        for(int j=0;j<n;j++){
            cout<< arrays[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool SortedArrays::search(int value) {
    for(int i=0;i<= maxDepth;i++){
        if(bsearch(arrays[i],value,0, pow(2,i)-1)){
            return true;
        }
    }
    return false;
}

bool SortedArrays::bsearch(int *arr, int target, int l, int r) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target)
            return true;
        if (target < arr[mid])
            return bsearch(arr,target, l, mid - 1);
        else return bsearch(arr,target, mid + 1, r);
    }
    return false;
}

void SortedArrays::merge(int depth) {
    if(maxDepth < depth+1){
        createDepth(depth+1);
    }
    int* lPtr = arrays[depth];
    int* rPtr = tmpArrays[depth];
    int* newArray = tmpArrays[depth+1];
    int n = pow(2,depth+1);
    int i = 0;
    while (i<n){
        if(lPtr-arrays[depth] > n/2-1){
            newArray[i] = *rPtr;
            rPtr++;
            i++;
        }
        else if(rPtr-tmpArrays[depth] > n/2-1){
            newArray[i] = *lPtr;
            lPtr++;
            i++;
        }
        else if(*rPtr<*lPtr){
            newArray[i] = *rPtr;
            rPtr++;
            i++;
        } else {
            newArray[i] = *lPtr;
            lPtr++;
            i++;
        }

    }
    clearArray(arrays[depth],n/2);
    clearArray(tmpArrays[depth],n/2);
}

void SortedArrays::printTmp() {
    cout<<"======tmp======"<<endl;
    for(int i=0;i<= maxDepth ;i++){
        int n = pow(2,i);
        for(int j=0;j<n;j++){
            cout<< tmpArrays[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"======tmp======"<<endl;
}

#endif //SCHOOLHW_SORTEDARRAYS_H
