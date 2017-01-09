//
// Created by Milena on 09/01/2017.
//

#include "AddressFunction.h"
#include <ctime>
UniversalHash::UniversalHash(int size){
    time_t timer;
    srand((unsigned int)time(&timer));
    for(int i=0;i<20;i++){
        koef_[0][i]=(int)(((double)rand())/RAND_MAX*size);
        koef_[1][i]=(int)(((double)rand())/RAND_MAX*size);
    }
}
int UniversalHash::getAddress(int key, int address, int attempt, table& tab){
    int c=attempt--, rtvalue=0, num, key_copy=key, mod=10, div=1, cnt=0;
    if(!(c==1 || c==0)) return -1;
    while(key_copy!=0){
        num=(key_copy/div)%mod;
        key_copy/=div; div*=10;
        rtvalue+=koef_[c][cnt]*num;
        cnt++;
    };
    rtvalue%=prime_;
    rtvalue%=tab.size();
    return rtvalue;
}