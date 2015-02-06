#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <assimp/scene.h>
#include <vector>
#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/freeglut.h>
#include "Vec3.hpp"

class ObjectManager{

	public:
		struct gpuBufferData{
			GLuint vertex_vbo;
			GLuint vertex_vao;
		};

		ObjectManager();
		virtual ~ObjectManager();

		int loadFile(const char* filePath);
		gpuBufferData getGeometryBufferData(int idx);
	private:
		struct geometry{
			int ID;
			char* name;
			float* vertices;
			int nrVertices;
			float* normals;
			int* faces;
			int nrFaces;
			gpuBufferData data;
		};
		
		std::vector< geometry > geometries;

		bool createGeomStruct(const aiMesh* mesh);
		void loadGeomToGPU(geometry* g);
		void printGeomStruct(geometry* g);
};


#endif //OBJECT_MANAGER_HPP
