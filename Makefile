all: build_cmake run_example

EXAMPLE = main
BUILD_TYPE = Debug
# BUILD_TYPE = Release

build_cmake:
	-mkdir build
	cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
	cd build; make

run_example:
	cd build/examples/${EXAMPLE}; .\\${EXAMPLE}.exe
