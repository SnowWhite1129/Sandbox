all:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
    g++ test.cpp -o sandbox