run: main.o tree.o
	g++ main.o tree.o -o tree -std=c++11

main.o: main.cpp
	g++ -c -w main.cpp -std=c++11

tree.o: tree.cpp
	g++ -c -w tree.cpp -std=c++11

clean:
	rm -rf *.o tree
