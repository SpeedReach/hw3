//
// Created by gomil on 2022/12/24.
//

#ifndef SCHOOLHW_HASHTABLE_H
#define SCHOOLHW_HASHTABLE_H
#include "Collection.h"
#include <unordered_set>
#include <iostream>

using namespace std;

class HashTable: public Collection{

    void insert(int value){
        internalMap.insert(value);
    }

    bool search(int value){
        return internalMap.count(value);
    }

    void print(){
        for (const auto &item : internalMap){
            cout<<item<<" ";
        }
        cout<<endl;
    }

    string name(){
        return "HashTable";
    }

private:
    std::unordered_set<int> internalMap;

};


#endif //SCHOOLHW_HASHTABLE_H
