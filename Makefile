all:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
	g++ main.cpp -o sandbox
