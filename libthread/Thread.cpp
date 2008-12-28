/**
 * This file is part of libthread.
 *
 * Sentry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libthread is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sentry.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Thread.h"
#include <signal.h>
#include <errno.h>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

libthread::Thread::Thread() throw(){
    _target = (void*)this;
    _state = Thread::STATE_UNINITIALIZED;
}

libthread::Thread::Thread(Runnable* target) throw(ThreadException){
    if( ! target){
        throw ThreadException("The target cannot be NULL");
    }
    _target = (void*)target;
    _state = Thread::STATE_UNINITIALIZED;
}

libthread::Thread::~Thread() throw(){
    if(_state == Thread::STATE_RUNNING){

        switch(pthread_kill(_thread, SIGKILL) ){
            case 0:
                _state = Thread::STATE_KILLED;
                break;
            case ESRCH:
                cerr << "Could not kill thread: Thread not found." << endl;
                break;
            case EINVAL:
                cerr << "Invalid signal argument while killing thread." << endl;
                break;
            default:
                 cerr << "Unknown error while killing thread." << endl;
        }

    }
}

void libthread::Thread::_init() throw(ThreadException){
    switch(pthread_create(&_thread, NULL, libthread::Thread::_execute, (void*)_target)){
        case 0:
            _state = Thread::STATE_RUNNING;
            break;
        case EAGAIN:
            throw ThreadException("Not enough resources to create new thread.");
        case EINVAL:
            throw ThreadException("Invalid value(s) specified for thread attributes.");
        case EPERM:
            throw ThreadException("Not enough permissions to set scheduling parameters or policy.");
        default:
            throw ThreadException("Unknown error while creating thread.");
    }
    
}

void libthread::Thread::join() throw(ThreadException){
    if( _state == Thread::STATE_UNINITIALIZED ){
        throw ThreadException("Cannot join uninitialized thread, call Thread::start() first.");
    }
    switch(pthread_join(_thread, NULL)){
        case 0:
            return;
        case EINVAL:
            throw ThreadException("Invalid value(s) specified for thread attributes.");
        case ESRCH:
            throw ThreadException("Could not join thread: Thread not found.");
        case EDEADLK:
            throw ThreadException("Deadlock detected.");
        default:
            throw ThreadException("Unknown error while joining thread");
    }
}

void libthread::Thread::detach() throw(ThreadException){
    if( _state == Thread::STATE_UNINITIALIZED ){
        throw ThreadException("Cannot detach uninitialized thread, call Thread::start() first.");
    }
    switch(pthread_detach(_thread)){
        case 0:
            return;
        case EINVAL:
            throw ThreadException("Invalid value(s) specified for thread attributes.");
        case ESRCH:
            throw ThreadException("Could not detach thread: Thread not found.");
        default:
            throw ThreadException("Unknown error while detaching thread");
    }
}

void libthread::Thread::start() throw(ThreadException){
    this->_init();
}

void libthread::Thread::run(){
    
}

libthread::Thread::state_t libthread::Thread::state() throw(){
    return _state;
}

void* libthread::Thread::_execute(void* ptr){
    Runnable* runnable = (Runnable*)ptr;
    runnable->run();
    return 0;
}

extern "C" libthread::Thread* create_thread(libthread::Runnable* target){
    if(target){
        return new libthread::Thread(target);
    }
    return new libthread::Thread();
}

extern "C" bool destroy_thread(libthread::Thread* thread){
    delete thread;
    return true;
}
