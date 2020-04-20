all:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
	g++ sandbox.cpp -o sandbox
