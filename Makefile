all:
	g++ -I src/include -L src/lib -o merge main.cpp -lmingw32