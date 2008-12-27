#include "Thread.h"
#include "TestRunnable.h"
#include "ThreadException.h"
#include <iostream>

using libthread::Thread;
using std::cerr;
using std::endl;

int main(int argc, char** argv){
    try{
        TestRunnable* r = new TestRunnable;
        Thread* t = new Thread(r);
        t->start();
        t->join();

        delete t;
        delete r;
        return 0;
    }catch(ThreadException ex){
        cerr << ex.what() << endl;
    }
}
