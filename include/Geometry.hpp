#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include "Node.hpp"
#include <assimp/scene.h>

#include <GL/glew.h>
#include <vector>

class RenderVisitor;

class Geometry : public Node{

	public:
		Geometry();
		Geometry(const char* filePath);
		virtual ~Geometry();
	
		void update();

		void accept(NodeVisitor& v);

		void draw();
	private:

		bool loaded;

		int nrVertices;
		int nrFaces;
		
		GLuint VAO;
		GLuint vertexBuffer;
		GLuint textureBuffer;
		GLuint normalBuffer;
		GLuint faceBuffer;
		
		bool loadFile(const char* filePath);
		void createGeom( const aiMesh* mesh );


};

#endif // GEOMETRY_HPP
