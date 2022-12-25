#include "Collection.h"
#include "BTree.h"
#include "SkipList.h"
#include "Treap.h"
#include "HashTable.h"
#include <iostream>
#include "SortedArrays.h"


using namespace std;

int main(){
    //Create BTree with max degree = 3
    Collection* collection = new BTree(3);
    //create hashtable
    collection = new HashTable();
    //create array of sorted arrays
    collection = new SortedArrays();
    //create a treap
    collection = new Treap();
    //create a skiplist with max=100 height and 0.5 chance to grow upwards
    collection = new SkipList(100,0.5);

    //insert into a collection
    collection->insert(10);

    //search a collection ,returns true if found the target
    if(collection->search(10)){
        cout<<"found";
    }
    else cout <<"not found";
}