#OBJS specifies which files to compile as part of the project 
OBJ_FILES = lab1.o Shader.o Node.o Geometry.o Transform.o State.o Group.o  NodeVisitor.o RenderVisitor.o UpdateVisitor.o

#TARGET specifies the name of our exectuable 
TARGET = lab1.out

SOURCE_DIR = src
INCLUDE_DIR = include
OBJECT_DIR = obj
#SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# OBJS shows the path to the .o files
OBJS = $(patsubst %,$(OBJECT_DIR)/%,$(OBJ_FILES)) 


#CC specifies which compiler we're using 
CC = g++ 

#COMPILER_FLAGS specifies the additional compilation options we're using 
COMPILER_FLAGS = -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lGL -lGLU -lGLEW -lglut -lassimp


DEPS := $(OBJS:.o=.d)


all : $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LINKER_FLAGS) 


$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -MMD -MP  $(COMPILER_FLAGS) -Iinclude -c $< -o $@ 

-include $(DEPS)

clean: 
	rm -f $(TARGET) $(DEPS) $(OBJS)
tidy:
	rm -f $(DEPS) $(OBJS) 
