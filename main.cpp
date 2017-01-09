#include <iostream>
#include "HashTable.h"
#include <fstream>

using namespace std;

/*int main() {
    HashTable tabela(10, new BidirectLinHash(2));
    string string1="pera";
    tabela.insertKey(2,string1);
    cout<<tabela<<endl;
    tabela.insertKey(3,string1);
    cout<<tabela<<endl;
    tabela.insertKey(12,string1);
    cout<<tabela<<endl;
    tabela.insertKey(14,string1);
    cout<<tabela<<endl;
    tabela.insertKey(55,string1);
    cout<<tabela.findKey(32)<<endl;
    cout<<tabela<<endl;
    tabela.insertKey(208,string1);
    cout<<tabela<<endl;
    cout<<"procena "<<tabela.avgAccessUnsuccessEst()<<endl;
    tabela.insertKey(33,string1);
    cout<<tabela<<endl;
    cout<<"procena "<<tabela.avgAccessUnsuccessEst()<<endl;

    tabela.insertKey(15,string1);
    cout<<tabela<<endl;
    cout<<"procena "<<tabela.avgAccessUnsuccessEst()<<endl;
    tabela.deleteKey(208);
    tabela.insertKey(1,string1);
    cout<<tabela.findKey(8)<<endl;
    cout<<tabela<<endl;
    cout<<"procena "<<tabela.avgAccessUnsuccessEst()<<endl;
    tabela.insertKey(10,string1);
    cout<<tabela<<endl;
    cout << *tabela.findKey(10)<<endl;
    cout<<tabela.findKey(100)<<endl;
    cout<<"uspesno "<<tabela.avgAccessSuccess()<<endl;
    cout<<"neuspesno "<< tabela.avgAccessUnsuccess()<<endl;
    cout<<"procena "<<tabela.avgAccessUnsuccessEst()<<endl;
}*/

int randkey(HashBase* table){
    return (int)((double)rand()/RAND_MAX*(table.maxkey()-table.minkey())+table.minkey());
}
int step(int size){
    return 29%size;
}
void pretraga(HashBase* tabela){
    int key;
    cout << "Kljuc za pretragu: " <<flush;
    cin >> key;
    string * str=tabela->findKey(key);
    if(str) cout << "Nadjen string " << *str << " sa kljucem " << key;
    else cout << "Kljuc ne postoji u tabeli" <<endl;
    return;
}
void umetanje(HashBase* tabela){
    int key; string str;
    cout << "String: "<<flush; cin >>str;
    cout << "Kljuc: "<<flush;
    cin>>key;
    while (key<0) {
        cout<<"Nevalidna vrednost"<<endl;
        cin>>key;
    }
    if (tabela->insertKey(key, str))
        cout<<"Uspesno umetanje."<<endl;
    else cout<<"Neuspesno umetanje. Tabela puna."<<endl;
    return;
}
void statistika(HashBase*tabela){
    cout << "Prosecan broj pristupa prilikom uspesne pretrage: " << tabela->avgAccessSuccess()<<endl;
    cout << "Procenjena efikasnost neuspesne pretrage "<< tabela->avgAccessUnsuccessEst()<<endl;
    cout << "Prosecan broj pristupa prilikom neuspesne pretrage: " << tabela->avgAccessUnsuccess()<<endl;
    cout << "Popunjenost tabele: "<< tabela->fillRatio()<<endl;
    return;
}
void brisanje(HashBase* tabela){
    int key;
    cout<<"Kljuc za brisanje: "<<flush;
    cin>>key;
    if (tabela->deleteKey(key))
        cout<<"Uspesno brisanje";
    else
        cout<<"Kljuc ne postoji";
    return;
}
void ciscenje(HashBase* tabela){
    tabela->clear();
    cout<<"Svi kljucevi obrisani."<<endl;
    return;
}
void brisanjeStat(HashBase* tabela){
    tabela->resetStats();
    cout<<"Statistika resetovana"<<endl;
}
void test(HashBase* table){
    int src=table->tableSize()*10; int random_key;
    cout << "Sadrzaj tabele" << endl << table<<endl;
    cout << "Test pretraga na "<<src<< " kljuceva"<<endl;

    for(int i=0;i<src;i++){
        random_key=randkey(table);
        table->testFindKey(random_key);
    }

    statistika(table);

    return;
}

void menu(){
    cout << "1. Test"<<endl;
    cout << "2. Pretraga"<<endl;
    cout << "3. Umetanje"<<endl;
    cout << "4. Statistika" <<endl;
    cout << "5. Brisanje kljuca" << endl;
    cout << "6. Brisanje svih kljuceva" <<endl;
    cout << "7. Brisanje statistike" << endl;
    cout << "0. Izlaz"<<endl<<endl;
    cout << "Unos: "<<endl;
    return;
}

int main(){
    int input=-1;
    while(input!=1 && input!=2) {
        cout << "1. Standardno hesiranje sa bidirekcionom metodom razresavanja kolizija" << endl <<
        "2.Cuckoo hesiranje" << endl;
        cin >> input;
    }
    cout << "Velicina hes tabele: "<<endl;
    cin>>input;
    while(input<0){
        cout << "Nevalidna vrednost. Velicina hes tabele: "<<endl;
        cin>>input;
    }

    HashBase * tabela;
    if(input==1) tabela=new HashTable(input,new BidirectLinHash(step(input)));
    else tabela=new CuckooHashTable(input);

    cout << "1.Unos sa standardnog ulaza"<<endl<<"2. Unos iz datoteke"<<endl<<endl<<"0. Izlaz"<<endl;
    cin >>input;
    while(input!=1 && input!=2 && input!=0){
        cout << "Nevalidna vrednost. Opcija: "<<endl;
        cin>>input;
    }

    switch(input){
        case 1: break;
        case 2: {
            string path;
            cout<<"Putanja: "<<endl;
            cin>>path;
            ifstream fajl;
            fajl.open("C:\\Users\\Milena\\Faks\\ASP 2\\13S112ASP2_DZ3_materijali_1617\\DZ3_Recnik_10K.txt");
            if(!fajl.is_open()) {
                cout << "Neuspesno otvaranje" <<endl;
                system("pause"); exit(0);
            }
            for(int i=0;i<10000;i++){
                string str; int key;
                fajl >> str;
                fajl >> key;
                if(!tabela->insertKey(key,str)) {
                    cout<<"Tabela puna"<<endl;
                    break;
                };
            }
            fajl.close();
        }; break;
        case 0: exit(0);
        default: cout<<"Ako je upao u default obesicu se na terazijskoj cesmi"<<endl;
    }
    menu();
    cin>>input;
    while(input!=0){
        switch(input){
            case 1: test(tabela); break;
            case 2: pretraga(tabela); break;
            case 3: umetanje(tabela); break;
            case 4: statistika(tabela); break;
            case 5: brisanje(tabela); break;
            case 6: ciscenje(tabela); break;
            case 7: brisanjeStat(tabela); break;
            default: cout<<"Pogresan unos"<<endl; break;
        }
        system("pause");
        cout<<endl;
        menu();
        cin>>input;
    }

}