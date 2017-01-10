//
// Created by Milena on 28/12/2016.
//

#include "HashTable.h"
#include <iostream>

void HashTable::printtable(std::ostream& os) const{
    table_.print(os);
};

void CuckooHashTable::printtable(std::ostream& os) const {
    os << "Table 1" << std::endl;
    table1_.print(os);
    os << std::endl << "Table 2" << std::endl;
    table2_.print(os);

};

string * HashTable::findKey(int key){
    int hash=(*function_)(key,-1,0, table_); int attempt=1;
    while(table_[hash].key_!=-1 && table_[hash].key_!=key && attempt<table_.size())
        hash=(*function_)(key,hash,attempt++,table_);
    if(table_[hash].key_==-1 || attempt==table_.size()) {
        unsuccess_++; unsuccess_acc_+=attempt;
        return nullptr;
    }
    else return table_[hash].string_;
};

void HashTable::testFindKey(int key){
    int hash=(*function_)(key,-1,0, table_); int attempt=1;
    while(table_[hash].key_!=-1 && table_[hash].key_!=key && attempt<table_.size())
        hash=(*function_)(key,hash,attempt++,table_);
    if(table_[hash].key_==-1 || attempt==table_.size()) {
        unsuccess_++; unsuccess_acc_+=attempt;
        std::cout<<"Kljuc "<<key<< " nije nadjen"<<std::endl;
    }
    else std::cout<<"String " << table_[hash].string_ << " sa kljucem "<< key << " nadjen na poziciji "<< hash<<" posle "<<attempt<<" pokusaja"<<std::endl;
}

bool HashTable::insertKey(int key, string& str){
    if (table_.key_count_==table_.size_) return false;
    int attempt=0;
    int hash=(*function_)(key, -1,attempt++, table_);
    while(table_[hash].occupied()) {
        hash = (*function_)(key, hash, attempt++, table_);
        if(hash<0) system("pause");
    }
    if(key<table_.min_ || table_.key_count_==0) table_.min_=key;
    if(key>table_.max_ || table_.key_count_==0) table_.max_=key;
    table_.insert(hash,key,new string(str));
    table_.key_count_++;
    return true;
};

double HashTable::avgAccessSuccess(){
    if (table_.key_count_==0) return 0;
    int acc=0, size=table_.size(); int hash, attempt;
    for(int i=0;i<size;i++){
        if(table_[i].occupied()){
            hash=(*function_)(table_[i].key_,-1,0, table_); attempt=1;
            while(table_[hash].key_!=-1 && table_[hash].key_!=table_[i].key_ && attempt<table_.size())
                hash=(*function_)(table_[i].key_,hash,attempt++,table_);
            acc+=attempt;
        }
    }
    return acc/(double)table_.key_count_;
}

bool HashTable::deleteKey(int key){
    int addr=(*function_)(key,-1,0, table_); int attempt=1;
    while(table_[addr].key_!=-1 && table_[addr].key_!=key && attempt<table_.size())
        addr=(*function_)(key,addr,attempt++,table_);
    if(table_[addr].key_==-1 || attempt==table_.size()) {
        unsuccess_++; unsuccess_acc_+=attempt;
        return false;
    }
    else{
        table_[addr].key_=-2;
        delete table_[addr].string_; table_[addr].string_= nullptr;
        table_.key_count_--;
        return true;
    }
}

string * CuckooHashTable::findKey(int key){
    int h1=(*function1_)(key,-1,1,table1_), h2=(*function1_)(key,-1,2,table1_);
    if(table1_[h1].key_==key) return table1_[h1].string_;
    else if(table2_[h2].key_==key) return table2_[h2].string_;
    else return nullptr;
};
bool CuckooHashTable::insertKey(int key, string& str){
    if(keyCount()==table1_.size() || findKey(key)) return false;
    int tries=0, prevaddr=-1, prev=key;
    table::tableInstance temp; temp.key_=key; temp.string_=new string(str);
    while (tries<max_loop_){
        table1_.cuckoo(&temp, prevaddr=(*function1_)(key,prev,1,table1_));
        if (temp.key_==-1) {
            table1_.key_count_++;
            return true;
        }
        else prev=table1_[prevaddr].key_;
        tries++;
        table2_.cuckoo(&temp, prevaddr=(*function1_)(key,prev,2,table1_));
        if (temp.key_==-1) {
            table2_.key_count_++;
            return true;
        }
        else prev=table2_[prevaddr].key_;
        tries++;
    }
    std::cout<<"temp " <<" "<< temp.key_<<std::endl;
    rehash();
    string st=*temp.string_;
    delete temp.string_;
    temp.string_= nullptr;
    return insertKey(temp.key_,st);
}
bool CuckooHashTable::deleteKey(int key){
    int h1=(*function1_)(key,-1,1,table1_), h2=(*function1_)(key,-1,2,table1_);
    if(table1_[h1].key_==key) {
        table1_[h1].key_=-1;
        delete table1_[h1].string_;
        table1_[h1].string_=nullptr;
        return true;
    }
    else if(table2_[h2].key_==key) {
        table2_[h2].key_=-1;
        delete table2_[h2].string_;
        table2_[h2].string_=nullptr;
        return true;
    }
    else return false;
};

void CuckooHashTable::rehash(){
    printtable(std::cout);
    system("pause");
    return;
}