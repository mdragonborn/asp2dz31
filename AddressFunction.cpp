//
// Created by Milena on 09/01/2017.
//

#include "AddressFunction.h"
#include <ctime>
UniversalHash::UniversalHash(int size){
    time_t timer;
    srand((unsigned int)time(&timer));
    for(int i=0;i<20;i++){
        koef[0][i]=(int)(((double)rand())/RAND_MAX*size);
        koef[1][i]=(int)(((double)rand())/RAND_MAX*size);
    }
}
int UniversalHash::getAddress(int key, int address, int attempt, table& tab){
    int c=attempt--, rtvalue;
    if(!(c==1 || c==0)) return -1;

    return rtvalue;
}