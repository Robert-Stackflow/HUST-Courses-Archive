#include "socket/exception.h"
#include <cstring>
#pragma warning(disable:4996)
string SocketException::what() const {
    if (errno == 0)
        return "Socket异常:" + msg;
    return "Socket异常:" + msg + strerror(errno);
}
