#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include "Node.hpp"
#include <assimp/scene.h>

#include <GL/glew.h>
#include <vector>

class Geometry : public Node{

	public:
		Geometry(const char* filePath);
		virtual ~Geometry();

		void draw();

	private:

	


		int nrVertices;
//		std::vector< float > vertices;
		float* vertices;
		float* normals;

		int nrFaces;
		int* faces;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		//std::vector<int>faces;
		//std::vector< float > normals;

		bool loadFile(const char* filePath);
		bool createGeom( const aiMesh* mesh );
		void loadToVBO();
		void print();

		

};

#endif // GEOMETRY_HPP
