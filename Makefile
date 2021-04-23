


cflags="-std=c++11"
target="program2"


all: node0_c.o node1_c.o node2_c.o node3_c.o prog3_c.o
	g++ $(cflags) -g *.o -o $(target)



node0_c.o:
	g++ $(cflags) -g *.o -o node0_c.cpp


