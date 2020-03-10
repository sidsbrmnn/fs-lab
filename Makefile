all: out

out: p1 p2 p3 p4

p1: p1.cpp
	g++ -o p1.out p1.cpp

p2: p2.cpp
	g++ -o p2.out p2.cpp

p3: p3.cpp
	g++ -o p3.out p3.cpp

p4: p4.cpp
	g++ -o p4.out p4.cpp
