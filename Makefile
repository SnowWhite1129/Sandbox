all:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
