#OBJS specifies which files to compile as part of the project 
LOCAL_OBJ_FILES = lab1.o Shader.o Node.o Geometry.o Transform.o State.o Group.o  NodeVisitor.o RenderVisitor.o UpdateVisitor.o Quaternion.o Vec3.o Vec4.o Hmat.o TransformMatrix.o Camera.o Scene.o UpdateCallback.o TransformSpinCallback.o CameraMovementCallback.o KeyState.o Light.o Material.o Texture.o Timer.o

REMOTE_OBJ_FILES = Image.o JPGReader.o PNGReader.o FileSystem.o 
OBJ_FILES = $(LOCAL_OBJ_FILES) $(REMOTE_OBJ_FILES)

#TARGET specifies the name of our exectuable 
TARGET = lab1.out

SOURCE_DIR = src
INCLUDE_DIR = include
OBJECT_DIR = obj
#SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# OBJS shows the path to the .o files
OBJS = $(patsubst %,$(OBJECT_DIR)/%,$(OBJ_FILES)) 


#CC specifies which compiler we're using 
CC = g++ -g

#COMPILER_FLAGS specifies the additional compilation options we're using 
COMPILER_FLAGS = -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lGL -lGLU -lGLEW -lglut -lassimp -ljpeg -lpng


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
