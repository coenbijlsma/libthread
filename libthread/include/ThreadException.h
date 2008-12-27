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
#ifndef THREADEXCEPTION_H
#define	THREADEXCEPTION_H

#include <string>

using std::string;

namespace libthread {

    class ThreadException {
        string _what;
        ThreadException* _cause;
        
    public:
        ThreadException();
        ThreadException(string what);
        ThreadException(ThreadException* cause, string what);

        string what();
        ThreadException* getCause();
    };
}

#endif	/* THREADEXCEPTION_H */

