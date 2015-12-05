//
// Created by Kamil on 21.11.15.
//


#include "../headers/Exception.h"

Exception::Exception(string message) {
    this->message = message;
}

string Exception::getMessage() {
    return message;
}
