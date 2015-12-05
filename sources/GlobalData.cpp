//
// Created by Kamil on 21.11.15.
//

#include "../headers/GlobalData.h"
#include "../headers/Exception.h"

void GlobalData::loadFromFile(string const location) {
    ifstream file;
    file.open(location);
    if (file.good()){
        for (int i = 0; i< numberOfVars; i++){
            string name;
            file >> name;
            if (name == "nh") file>>nh;
            else if (name == "ne") file>>ne;
            else if (name == "L") file>>L;
            else if (name == "K") file>>K;
            else if (name == "S") file>>S;
            else if (name == "Q") file>>Q;
            else if (name == "Alfa") file>>Alfa;
            else if (name == "envT") file>>envT;
        }
        cout<<"**********************************"<<endl;
        cout<<"nh: " <<"\t"<< nh << endl;
        cout<<"ne: " <<"\t"<< ne<< endl;
        cout<<"L: " <<"\t"<< "\t"<<L<< endl;
        cout<<"K: " <<"\t"<<"\t"<< K<< endl;
        cout<<"S: " << "\t"<<"\t"<<S<< endl;
        cout<<"Q: " << "\t"<<"\t"<<Q<< endl;
        cout<<"Alfa: "<<"\t"<<Alfa<< endl;
        cout<<"envT: "<<"\t"<< envT<< endl;
        cout<<"**********************************"<<endl;
        file.close();
    }
    else{
        throw Exception("Initializing of GlobalData failed.");
    }
}