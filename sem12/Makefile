static-lib:
	gcc -O2 -Wall -Werror -std=c11 -c hello/hello.c -o hello/hello.o
	ar rcs hello/libhello.a hello/hello.o

static-bin: static-lib
	gcc static_main.c -static -Lhello -o static_main -lhello

dynamic-lib:
	gcc -O2 -Wall -Werror -fPIC -DPIC  -std=c11 -c hello/hello.c -o hello/hello.o
	gcc -std=c11 -fPIC -shared hello/hello.o -o hello/libhello.so

dynamic-bin: dynamic-lib
	gcc static_main.c -Lhello -Wl,-rpath,hello -o dynamic_main -lhello

envp-bin: dynamic-lib
	gcc static_main.c -Lhello -o envp_main -lhello

runtime-bin: dynamic-lib
	gcc dynamic_main.c -o dynamic_main -ldl

clean:
	rm -f hello/hello.o static_main dynamic_main envp_main static_main.o
