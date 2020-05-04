all:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
	g++ main.cpp -o sandbox
test:
	g++ -o sandbox.so -shared -fPIC sandbox.cpp -ldl
	g++ main.cpp -o sandbox
	g++ main.cpp -o sandbox64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

