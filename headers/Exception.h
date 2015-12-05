//
// Created by Kamil on 21.11.15.
//

#ifndef MES_EXCEPTION_H
#define MES_EXCEPTION_H

#include <iostream>
#include <string>
using namespace std;


class Exception {
private:
    string message;
public:
    Exception(string message);
    string getMessage();
};


#endif //MES_EXCEPTION_H
