CLANG =	clang++

NAME = Render

CFLAGS =

C++_TYPE = -std=c++11 -g -o3

INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.1.0/include/ -I ~/.brew/include -I include/

LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib/ -L ~/.brew/Cellar/glew/2.1.0/lib/

LINKER_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW

TEXTURE = -L. libsoil2-debug.a

HEADER = ./Inc/

SRC_PATH = ./Src/

SRC = $(SRC_PATH)main.cpp $(SRC_PATH)Render.cpp $(SRC_PATH)Shaders.cpp $(SRC_PATH)Camera.cpp $(SRC_PATH)Object_Loader.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(INCLUDE_PATHS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -lGL -lGLU -lGLEW -lglut -lglfw -o $(NAME) $(OBJ) $(TEXTURE)

mac: $(OBJ) $(HEADER)
	$(CLANG) $(C++_TYPE) $(INCLUDE_PATHS) $(LINKER_FLAGS) -o $(NAME) $(OBJ) $(TEXTURE) $(LIBRARY_PATHS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
