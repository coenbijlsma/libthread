#include "TestRunnable.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

TestRunnable::TestRunnable(){
    cout << "TestRunnable::TestRunnable()" << endl;
}

TestRunnable::~TestRunnable(){
    cout << "TestRunnable::~TestRunnable()" << endl;
}

void TestRunnable::run(){
    cout << "TestRunnable::run()" << endl;
    
        while(true){
            usleep(100000);
        }
    cout << "Return from TestRunnable::run()" << endl;
}
