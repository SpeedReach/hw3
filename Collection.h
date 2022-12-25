//
// Created by gomil on 2022/12/24.
//

#ifndef SCHOOLHW_COLLECTION_H
#define SCHOOLHW_COLLECTION_H

#include <string>


class Collection{


public:
    virtual void insert(int value) = 0;
    virtual bool search(int value) =0;
    virtual void print() = 0;
    virtual std::string name() = 0;
    virtual ~Collection(){

    }


};





#endif //SCHOOLHW_COLLECTION_H

