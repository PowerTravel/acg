#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include "Node.hpp"
#include "Vec3.hpp"
#include <assimp/scene.h>

#include <GL/glew.h>
#include <vector>

class RenderVisitor;

#ifndef GEOMETRY_PTR
#define GEOMETRY_PTR
class Geometry;
typedef std::shared_ptr<Geometry> geometry_ptr;
#endif //GEOMETRY_PTR

class Geometry : public Node{

	public:
		Geometry();
		Geometry(const char* filePath);
		virtual ~Geometry();
	
		void update();

		void acceptVisitor(NodeVisitor& v);

		void draw();
	private:

		Vec3 _cm;

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
