//
// Created by Milena on 28/12/2016.
//

#ifndef ASP2DZ31_TABLE_H
#define ASP2DZ31_TABLE_H

#include <string>
using std::string;

class table {
    struct tableInstance{
        string *string_= nullptr;
        int key_=-1;
        bool occupied()const{ return key_>=0;}
    };
    tableInstance * table_;
    int size_, key_count_, min_, max_;
    friend class HashTable;
    friend class AddressFunction;
    friend class BidirLinHash;
    friend class CuckooHashTable;
public:
    table(int size):size_(size), key_count_(0){
        table_= new tableInstance[size];
    };
    bool full()const{ return size_==key_count_;}
    void shiftLeft(int addr){
        int bound=addr;
        while(table_[bound].key_!=-1) bound=(bound)?(bound-1):(size_-1);
        while (bound!=addr){
            table_[bound]=table_[(bound+1)%size_];
            bound=(bound+1)%size_;
        }
    }
    void shiftRight(int addr){
        int bound=addr;
        while(table_[bound].key_!=-1) bound=(bound+1)%size_;
        while(bound!=addr){
            table_[bound]=table_[(bound)?(bound-1):(size_-1)];
            bound=(bound)?(bound-1):(size_-1);
        }
    }
    void insert(int addr, int key, string * sstring){
        table_[addr].key_=key;
        table_[addr].string_=sstring;
        return;
    }
    void clear(){
        delete table_;
        table_=new tableInstance[size_];
        return;
    }
    int size()const{
        return size_;
    }
    tableInstance& operator[](int ind){
        return table_[ind];
    }
    ~table(){
        for(int i=0; i<size_; i++)
            if (table_[i].string_) delete table_[i].string_;
        delete table_;
    }
    int min()const{
        return min_;
    }
    int max()const{
        return max_;
    }
    int keyCount()const{
        return key_count_;
    }
    tableInstance * cuckoo(int newkey, string * newstring, int position){
        tableInstance * rtvalue=new tableInstance(table_[position]);
        table_[position].key_=newkey;
        table_[position].string_=newstring;
        return rtvalue;
    }
    tableInstance * cuckoo(tableInstance * source, int target){
        tableInstance tmp;
        tmp=table_[target];
        table_[target]=*source;
        *source=tmp;
        return source;
    }
};


#endif //ASP2DZ31_TABLE_H
