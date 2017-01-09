//
// Created by Milena on 28/12/2016.
//

#ifndef ASP2DZ31_HASHTABLE_H
#define ASP2DZ31_HASHTABLE_H
#include <string>
#include "AddressFunction.h"

using std::string;

class HashBase{
public:
    virtual string * findKey(int)=0;
    virtual bool insertKey(int, string&)=0;
    virtual bool deleteKey(int)=0;
    virtual double avgAccessSuccess()=0;
    virtual double avgAccessUnsuccess() const =0;
    virtual double avgAccessUnsuccessEst() const =0;
    virtual void resetStats()=0;
    virtual void clear()=0;
    virtual int keyCount() const =0;
    virtual int tableSize() const =0;
    friend std::ostream& operator<<(std::ostream& os, HashBase& table){ printtable(os); };
    virtual double fillRatio() const =0;
    virtual int minkey()const =0;
    virtual int maxkey()const =0;
    virtual void testFindKey(int)=0;
private:
    virtual void printtable(std::ostream&) const=0;
};

class HashTable:public HashBase {
protected:
    AddressFunction * function_;
    table table_;
    int unsuccess_=0;
    int unsuccess_acc_=0;
    void printtable(std::ostream&) const override;
public:
    HashTable():{};
    HashTable(int size,AddressFunction * function):function_(function), table_(size){};
    string * findKey(int);
    bool insertKey(int, string&);
    bool deleteKey(int);
    double avgAccessSuccess();
    double avgAccessUnsuccess() const{
        return unsuccess_acc_/(double)unsuccess_;
    };
    double avgAccessUnsuccessEst() const{
        if (table_.full()) return table_.size_;
        return (1.0)/(1-fillRatio());
    }
    void resetStats(){
        unsuccess_=0; unsuccess_acc_=0;
    }
    void clear(){
        table_.clear();
        return;
    };
    int keyCount() const{
        return table_.key_count_;
    };
    int tableSize() const{
        return table_.size_;
    };
    friend std::ostream& operator<<(std::ostream& os, HashTable& table);
    double fillRatio() const{
        return ((double)table_.key_count_)/table_.size_;
    };
    int minkey()const{
        return table_.min_;
    }
    int maxkey()const{
        return table_.max_;
    }
    void testFindKey(int);
};

class CuckooHashTable: public HashBase{
protected:
    table table1_;
    int unsuccess_, unsuccess_acc_;
    table table2_;
    AddressFunction * function2_, * function1_;
    void newFunctions();
    void rehash();
    void printtable(std::ostream);
public:
    CuckooHashTable(int size):table1_(size), table2_(size), unsuccess_(0), unsuccess_acc_(0){
        function1_=new UniversalHash(size);
        function2_=new UniversalHash(size);
    };
    string * findKey(int);
    bool insertKey(int, string&) override;
    bool deleteKey(int) override;
    double avgAccessSuccess()=0;
    double avgAccessUnsuccess() const =0;
    double avgAccessUnsuccessEst() const override{
        if (keyCount()==tableSize()) return log2(table1_.size_);
        return (1.0)/(1-fillRatio());
    };
    void resetStats(){
        unsuccess_=unsuccess_acc_=0;
    };
    void clear(){
        table1_.clear();
        return;
    };    int keyCount() const{
        return table1_.keyCount()+table2_.keyCount();
    };
    int tableSize() const override{
        return table1_.size();
    };
    double fillRatio() const override{
        return ((double)keyCount())/table1_.size_;
    };
    int minkey()const override{
        return (table1_.min()<table2_.min())?table1_.min():table2_.min();
    }
    int maxkey()const override{
        return (table1_.max()>table2_.max())?table1_.max():table2_.max();
    }
    virtual void testFindKey(int)=0;
};


#endif //ASP2DZ31_HASHTABLE_H
