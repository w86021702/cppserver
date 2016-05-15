
test : demo.o
	g++ -I/usr/include -std=c++11 -o test demo.cpp -L/usr/lib64 -levent 
	g++ -I/usr/include -o testcli democli.cpp -L/usr/lib64 -levent

clean:
	rm ./*.o
