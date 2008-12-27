/* 
 * File:   TestRunnable.h
 * Author: coen
 *
 * Created on December 26, 2008, 12:38 PM
 */

#ifndef TESTRUNNABLE_H
#define	TESTRUNNABLE_H

#include "Runnable.h"

using libthread::Runnable;

class TestRunnable : public Runnable {
public:
    TestRunnable();
    virtual ~TestRunnable();

    void run();
};

#endif	/* TESTRUNNABLE_H */

