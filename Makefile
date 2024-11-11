all: build_cmake run_example

EXAMPLE = main

build_cmake:
	-mkdir build
	cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
	cd build; make

run_example:
	cd build/examples/${EXAMPLE}; .\\${EXAMPLE}.exe
