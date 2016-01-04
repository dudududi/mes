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
            else if (name == "K") file>>K;
            else if (name == "Q") file>>Q;
            else if (name == "C") file>>C;
            else if (name == "ro") file>>ro;
            else if (name == "Alfa") file>>Alfa;
            else if (name == "envT") file>>envT;
            else if (name == "beginT") file>>beginT;
            else if (name == "minR") file>>minR;
            else if (name == "maxR") file>>maxR;
            else if (name == "maxTau") file>>maxTau;
        }
        cout<<"**********************************"<<endl;
        cout<<"nh: " <<"\t"<< nh << endl;
        cout<<"ne: " <<"\t"<< ne<< endl;
        cout<<"L: " <<"\t"<< "\t"<<L<< endl;
        cout<<"K: " <<"\t"<<"\t"<< K<< endl;
        cout<<"S: " << "\t"<<"\t"<<S<< endl;
        cout<<"Q: " << "\t"<<"\t"<<Q<< endl;
        cout<<"C: " << "\t"<<"\t"<<C<< endl;
        cout<<"ro: " <<"\t"<<ro<< endl;
        cout<<"Alfa: "<<"\t"<<Alfa<< endl;
        cout<<"envT: "<<"\t"<< envT<< endl;
        cout<<"beginT: "<<beginT<< endl;
        cout<<"minR: " <<"\t"<<minR<< endl;
        cout<<"maxR: " <<"\t"<<maxR<< endl;
        cout<<"maxTau: "<<maxTau<< endl;
        cout<<"**********************************"<<endl;
        file.close();
    }
    else{
        throw Exception("Initializing of GlobalData failed.");
    }
}