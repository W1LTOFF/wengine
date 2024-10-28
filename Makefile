all: clean compile game run
#all: clear compile run

CC = clang++ --std=c++23
INDEPTH = engine/
# COMPILER_FLAGS = -Wall -Werror
# COMPILER_FLAGS = -Wall
COMPILER_FLAGS = -Wall -w
# INCLUDE_FLAGS = -IC:\VulkanSDK\1.3.290.0/Include -Iinclude # ? VULKAN
INCLUDE_FLAGS = -I$(INDEPTH)include # ? OPEN_GL
# LINKER_FLAGS = -LC:\VulkanSDK\1.3.290.0/Lib -Llib -static -lglfw3dll -lvulkan-1 # ? VULKAN
LINKER_FLAGS = -L$(INDEPTH)lib -static -lglfw3dll -lopengl32 # ? OPEN_GL
ASSEMBLY = wilt_engine
SRC = $(INDEPTH)include/glad/glad.c $(INDEPTH)src/*.cpp
ARGS = 

compile:
	mkdir ./bin
	$(CC) $(SRC) $(COMPILER_FLAGS) -o bin/$(ASSEMBLY).exe $(INCLUDE_FLAGS) $(LINKER_FLAGS)


game:
	mkdir ./build/
	cp $(INDEPTH)/lib/glfw3.dll build
	cp bin/$(ASSEMBLY).exe build
	cp -r ./shader/ ./build/
	cp -r ./res/ ./build/

run:
	@echo "build/$(ASSEMBLY).exe running..."
	@./build/$(ASSEMBLY).exe $(ARGS)

debug:
	-rm -rf build
	-rm -rf bin
	mkdir ./bin
	$(CC) --debug $(SRC) $(COMPILER_FLAGS) -o bin/$(ASSEMBLY).exe $(INCLUDE_FLAGS) $(LINKER_FLAGS)
	mkdir ./build/
	cp $(INDEPTH)/lib/glfw3.dll build
	cp bin/$(ASSEMBLY).exe build
	cp -r ./shader/ ./build/

clean:
	-rm -rf build
	-rm -rf bin
