all: clean debug compile build run
# all: compile_imgui

CC = clang++ --std=c++23
INDEPTH = engine/
COMPILER_FLAGS = -Wall -w
INCLUDE_FLAGS = -I$(INDEPTH)include -I$(INDEPTH)include/imgui
LINKER_FLAGS = -L$(INDEPTH)lib -static -l$(INDEPTH)lib/wengine/wengine -l$(INDEPTH)lib/wengine/imgui -l$(INDEPTH)lib/wengine/glad -lglfw3dll -lopengl32
EXECUTABLE = wilt_engine
IMGUI_SRC = $(INDEPTH)include/imgui/*.cpp
LIB_SRC = $(INDEPTH)src/engine/*.cpp
GLAD_SRC = $(INDEPTH)include/glad/glad.c
SRC = $(INDEPTH)src/*.cpp
ARGS = 

compile_glad:
	$(CC) $(EDITION_FLAGS) -c $(GLAD_SRC) -I$(INDEPTH)include
	ar r glad.lib *.o
	-rm engine/lib/wengine/glad.lib
	mv glad.lib engine/lib/wengine
	rm *.o

compile_imgui:
	$(CC) $(EDITION_FLAGS) -c $(IMGUI_SRC) -I$(INDEPTH)include/imgui -I$(INDEPTH)include
	ar r imgui.lib *.o
	-rm engine/lib/wengine/imgui.lib
	mv imgui.lib engine/lib/wengine
	rm *.o

compile_lib:
	$(CC) $(EDITION_FLAGS) -c $(LIB_SRC) -I$(INDEPTH)include/imgui -I$(INDEPTH)include
	ar r wengine.lib *.o
	-rm engine/lib/wengine/wengine.lib
	mv wengine.lib engine/lib/wengine
	rm *.o

compile:
	mkdir ./bin
	$(CC) $(EDITION_FLAGS) $(SRC) $(COMPILER_FLAGS) -o bin/$(EXECUTABLE).exe $(INCLUDE_FLAGS) $(LINKER_FLAGS)

release:
	$(eval EDITION_FLAGS = -O3)
	$(eval EDITION = release)

debug:
	$(eval EDITION_FLAGS = --debug)
	$(eval EDITION = debug)

run:
	@echo "build/$(EDITION)/$(EXECUTABLE).exe running..."
	@./build/$(EDITION)/$(EXECUTABLE).exe $(ARGS)

build:
	mkdir -p ./build/$(EDITION)
	cp $(INDEPTH)/lib/glfw3.dll build/$(EDITION)
	cp bin/$(EXECUTABLE).exe build/$(EDITION)
	cp -r ./shader/ ./build/$(EDITION)
	cp -r ./res/ ./build/$(EDITION)

clean:
	-rm -rf build
	-rm -rf bin
