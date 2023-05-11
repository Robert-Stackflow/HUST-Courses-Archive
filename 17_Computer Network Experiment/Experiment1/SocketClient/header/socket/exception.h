#ifndef EXCEPTION_H
#define EXCEPTION_H
#pragma once
#include <string>
using namespace std;
class SocketException {
public:
    string what() const;
    SocketException();
    SocketException(const string& _msg = string()) :msg(_msg) {}
private:
    string msg;
};

#endif // SOCKETEXCEPTION_H
