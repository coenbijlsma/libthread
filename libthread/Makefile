all:
		g++ -g3 -I./include/ -fPIC -g -c -Wall \
		Thread.cpp
		g++ -g3 -I./include/ -fPIC -g -c -Wall \
		ThreadException.cpp
		g++ -g3 -shared -Wl,-soname,libthread.so -o ./libthread.so.1.0.0 \
		Thread.o ThreadException.o -lc -lpthread

clean:
		@if [ -f Thread.o ]; then rm Thread.o; fi
		@if [ -f ThreadException.o ]; then rm ThreadException.o; fi
		@if [ -f libthread.so.1.0.0 ]; then rm libthread.so.1.0.0; fi
		@if [ -f test ]; then rm test; fi

install: isroot all
		@cp -v ./libthread.so.1.0.0 /usr/lib/
		ldconfig
		@cp -v ./include/Thread.h /usr/include
		@cp -v ./include/ThreadException.h /usr/include
		@cp -v ./include/Runnable.h /usr/include

uninstall: isroot
		@if [ -f /usr/lib/libthread.so.1.0.0 ]; then \
			rm /usr/lib/libthread.so.1.0.0; \
			ldconfig; \
			rm /usr/include/Runnable.h; \
			rm /usr/include/ThreadException.h; \
			rm /usr/include/Thread.h; \
		fi

test:
		g++ -I./include -combine Thread.cpp TestRunnable.cpp ThreadException.cpp \
		main.cpp -o test -lpthread

isroot:
		@if [ `whoami` != 'root' ]; then \
			echo "You must be root to do this"; \
			exit 1; \
		fi
		
.PHONY: all clean install uninstall test isroot
