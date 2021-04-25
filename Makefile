

cflags=-std=c99 -pedantic

target="program2"


#compile main executable
all: node0_c.o node1_c.o node2_c.o node3_c.o prog3_c.o
	gcc $(cflags)  -g *.o -o $(target)



node0_c.o:
	gcc $(cflags)  -g -c node0_c.c -o node0_c.o


node1_c.o:
	gcc $(cflags)  -g -c node1_c.c -o node1_c.o


node2_c.o:
	gcc $(cflags)  -g -c node2_c.c  -o node2_c.o

node3_c.o:
	gcc $(cflags)  -g -c node3_c.c -o node3_c.o



prog3_c.o:
	gcc $(cflags)  -g -c prog3_c.c -o prog3_c.o



clean:
	rm -rf $(target) *.o