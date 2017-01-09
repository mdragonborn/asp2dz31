//
// Created by Milena on 28/12/2016.
//

#ifndef ASP2DZ31_ADDRESSFUNCTION_H
#define ASP2DZ31_ADDRESSFUNCTION_H

#include "table.h"
#include <cmath>
class AddressFunction{
protected:
public:
    int operator()(int key,int address,int attempt, table& tab){
        return getAddress(key, address,attempt, tab);
    }
    virtual int getAddress(int key,int address, int attempt, table& tab) =0;
};

class BidirLinHash:public AddressFunction{
protected:
    int getAddress(int key, int address,int attempt, table& tab) override{
        int hash=key%tab.size_;
        if(tab[hash].key_==-1) return hash;
        if(tab[hash].key_<key){
            while(tab[hash].occupied()) hash=(hash+1)%tab.size_;
            while (tab[hash-1].key_<key && !tab[(hash)?(hash-1):(tab.size_-1)].occupied()){
                tab[hash]=tab[(hash)?(hash-1):(tab.size_-1)];
                hash=hash-1;
            }
        }
        else{
            while(tab[hash].occupied()) hash=(hash)?(hash-1):(tab.size_-1);
            while (tab[(hash+1)%tab.size_].key_>key && !tab[(hash+1)%tab.size_].occupied()){
                tab[hash]=tab[(hash+1)%tab.size_];
                hash=(hash+1)%tab.size_;
            }
        }
        return hash;
    }
public:
};

class BidirectLinHash:public AddressFunction{
protected:
    int step_;
    int getAddress(int key,int address, int attempt, table& tab){
        if (address==-1) return key%tab.size();
        else {
            int a=(address+step_*(int)ceil(attempt/2.0)*((attempt%2)?1:-1));
            return (a<0)?(-1*a)%tab.size():a%tab.size();
        }
    }
public:
    BidirectLinHash(int step):step_(step){};
};

class UniversalHash:public AddressFunction{
protected:
    int koef_[2][20];
    int prime_;
public:
    //mozda znam
    UniversalHash(int);
    int getAddress(int key, int address, int attempt, table&tab);
    void setPrime(int p){
        prime_=p; return;
    }
};

#endif //ASP2DZ31_ADDRESSFUNCTION_H
