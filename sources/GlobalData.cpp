//
// Created by Kamil on 21.11.15.
//

#include "../headers/GlobalData.h"
#include "../headers/Exception.h"

void GlobalData::loadFromFile(string const location) {
    ifstream file;
    file.open(location);
    if (file.good()){
        for (int i = 0; i< numberOfCommonVars; i++){
            string name;
            file >> name;
            if (name == "Q") file>>Q;
            else if (name == "Alfa") file>>Alfa;
            else if (name == "envT") file>>envT;
            else if (name == "numberOfMaterials") file>>numberOfMaterials;
        }
        materials = new Material* [numberOfMaterials];
        nh=1; //we assuming, that here will be at least one node
        ne = 0;
        for (int i=0; i<numberOfMaterials; i++){
            materials[i] = new Material();
            for (int j = 0; j< Material::NUMBER_OF_VARS; j++) {
                string name;
                file >> name;
                if (name == "nh"){
                    file >> materials[i]->nh;
                    nh +=  materials[i]->nh-1;
                }
                else if (name == "ne") {
                    file >> materials[i]->ne;
                    ne += materials[i]->ne;
                }
                else if (name == "L") file >> materials[i]->L;
                else if (name == "K") file >> materials[i]->K;
                else if (name == "S") file >> materials[i]->S;
            }
        }
        cout<<"**********************************"<<endl;
        cout<<"nh: " <<"\t\t"<<nh<< endl;
        cout<<"ne: " <<"\t\t"<<ne<< endl;
        cout<<"Q: " << "\t\t"<<Q<< endl;
        cout<<"Alfa: "<<"\t\t"<<Alfa<< endl;
        cout<<"envT: "<<"\t\t"<< envT<< endl;
        cout<<"materials: "<<"\t"<<numberOfMaterials<<endl;
        for (int i=0; i<numberOfMaterials; i++){
            cout<<"materials["<<i+1<<"]: "<<endl;
            cout<<"--> nh:"<<"\t\t"<<materials[i]->nh<<endl;
            cout<<"--> ne:"<<"\t\t"<<materials[i]->ne<<endl;
            cout<<"--> L:"<<"\t\t"<<materials[i]->L<<endl;
            cout<<"--> K:"<<"\t\t"<<materials[i]->K<<endl;
            cout<<"--> S:"<<"\t\t"<<materials[i]->S<<endl;
        }
        cout<<"**********************************"<<endl;
        file.close();
    }
    else{
        throw Exception("Initializing of GlobalData failed.");
    }
}

GlobalData::~GlobalData() {
    for (int i=0; i<numberOfMaterials; i++){
        delete materials[i];
    }
    delete materials;
}
