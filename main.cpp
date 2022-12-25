
#include "Collection.h"
#include "BTree.h"
#include "random"
#include "cmath"
#include "climits"
#include "iostream"
#include "ctime"
#include "SkipList.h"
#include "Treap.h"
#include <fstream>
#include "HashTable.h"
#include "SortedArrays.h"


using namespace std;

std::random_device rd;
std::mt19937 eng(rd());
std::uniform_int_distribution<int> distr(0, INT_MAX);

fstream insertO;
fstream searchO;

void process(Collection* (*func)()){
    Collection* c = func();

    insertO<<c->name() << endl;
    searchO<<c->name() << endl;
    delete c;
    for(int i=10;i<30;i++){
        Collection* collection = func();

        int n = pow(2,i);
        try{
            clock_t insertStart = clock();
            for(int j=0;j<n;j++){
                collection->insert(distr(eng));
            }
            clock_t insertEnd = clock();
            //insertO << collection->name() << " took "<< insertEnd-insertStart << " inserting 2^"<<i<<" datas"<<endl;
            insertO << insertEnd-insertStart <<endl;
            clock_t searchStart = clock();
            for(int j=0;j<n;j++){
                collection->search(distr(eng));
            }
            clock_t searchEnd = clock();
            //searchO << collection->name() << " took "<< searchEnd-searchStart << " searching 2^"<<i<<" datas"<<endl;
            searchO<<searchEnd-searchStart<<endl;
            if(insertEnd-insertStart > 1000*30*60){
                insertO << collection->name() <<" timed out on k="<<i<<endl;
                delete collection;
                break;
            }
        }
        catch(const bad_alloc& e) {
            insertO<<"not enough memory "<<endl;
            delete collection;
            break;
        }
    }
}

Collection* bTree(){
    return new BTree(10);
}

Collection* treap(){
    return new Treap();
}
Collection* hashTable(){
    return new HashTable();
}

Collection* skipList(){
    return new SkipList(6,0.5);
}

Collection* sortedArrays(){
    return new SortedArrays();
}

int main(){
    insertO.open("./insertO.txt");
    searchO.open("./searchingO.txt");
    process(skipList);
    return 0;
}

/*

    process(bTree);
    process(treap);
    process(hashTable);
    process(skipList);
 */