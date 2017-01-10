//
// Created by Milena on 28/12/2016.
//

#include "table.h"
#include <iostream>

void table::print(std::ostream& os)const{
    for(int i=0; i<size_; i++){
        os<<i<<" "<<table_[i].key_<<" "<<((table_[i].key_<=-1)?"EMPTY":*(table_[i].string_))<<std::endl;
    }
}