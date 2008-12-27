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
#ifndef THREAD_H
#define	THREAD_H

#include "Runnable.h"
#include "ThreadException.h"
#include <pthread.h>

using libthread::Runnable;
using libthread::ThreadException;

namespace libthread {
    
    class Thread : public Runnable {

    public:
        enum state_t {STATE_UNINITIALIZED, STATE_INACTIVE, STATE_RUNNING, STATE_KILLED};
        
        Thread() throw();
        Thread(Runnable* target) throw(ThreadException);
        virtual ~Thread() throw();

        void join() throw (ThreadException);

        void detach() throw(ThreadException);

        void start() throw(ThreadException);

        void run();

        state_t state() throw();

    private:
        void* _target;
        pthread_t _thread;
        state_t _state;
        
        void _init() throw(ThreadException);
        static void* _execute(void* ptr);
    };
}

typedef libthread::Thread* create_thread_t(libthread::Runnable* target);
typedef bool destroy_thread_t(libthread::Thread* thread);

#endif	/* THREAD_H */

