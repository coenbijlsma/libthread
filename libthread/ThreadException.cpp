#include "ThreadException.h"

libthread::ThreadException::ThreadException(){
    _what = "Unknown exception";
    _cause = 0;
}

libthread::ThreadException::ThreadException(string what){
    _what = what;
    _cause = 0;
}

libthread::ThreadException::ThreadException(ThreadException* cause, string what){
    _what = what;
    _cause = cause;
}

string libthread::ThreadException::what(){
    return _what;
}

libthread::ThreadException* libthread::ThreadException::getCause(){
    return _cause;
}