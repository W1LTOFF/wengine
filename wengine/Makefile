all: cmake_build

cmake_build:
	-mkdir build
	cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
	cd build; make
