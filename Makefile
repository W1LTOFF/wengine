all: build_cmake run
# all: engine_lib build_cmake run

engine_lib:
	cd wengine; make
	cp wengine/build/wengine.lib lib/wengine/

build_cmake:
	-mkdir build
	cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
	cd build; make

run:
	.\build\wengine-example.exe

# cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -S . -B build
