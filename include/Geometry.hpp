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

#ifndef GEOMETRY_VEC
#define GEOMETRY_VEC
class Geometry;
typedef std::vector< std::shared_ptr<Geometry> > geometry_vec;
#endif //GEOMETRY_VEC

class Geometry : public Node{

	public:

		enum DataType{
			VERTEX,
			TEXTURECOORDINATE,
			NORMAL,
			FACE
		};

		Geometry();
		Geometry(const aiMesh* mesh);
		virtual ~Geometry();
	
		void update();

		void acceptVisitor(NodeVisitor& v);

		void draw();
		static geometry_vec loadFile(const char* filePath);
	
		void loadVertices(int nrVertices, float* vertices);
		void loadTextureCoordinates(int nrTexCoords, float* coords);
		// Assumes they are triangles
		void loadFaces(int nrFaces, int* faces); 
		void loadNormals(int nrNormals, float* normals);
		//static bool loadFile(const char* filePath);
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
		
		void createGeom( const aiMesh* mesh );
		//bool loadFile(const char* filePath);
};

#endif // GEOMETRY_HPP
