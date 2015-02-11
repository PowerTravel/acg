#include "Geometry.hpp"
#include "RenderVisitor.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Geometry::Geometry() 
{
	nrVertices = 0;
	nrFaces = 0;
	loaded = false;
}

Geometry::Geometry(const char* filePath)
{

	nrVertices = 0;
	nrFaces = 0;

	loaded = loadFile(filePath);
}

Geometry::~Geometry()
{
	if(vertexBuffer)
	{
		glDeleteBuffers(0, &vertexBuffer);	
	}
	if(textureBuffer)
	{
		glDeleteBuffers(0, &textureBuffer);	
	}
	if(normalBuffer)
	{
		glDeleteBuffers(0, &normalBuffer);	
	}
	if(faceBuffer)
	{
		glDeleteBuffers(0, &faceBuffer);	
	}
}

bool  Geometry::loadFile(const char* filePath){

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
							aiProcess_OptimizeMeshes |
							aiProcess_Triangulate | 
							aiProcess_JoinIdenticalVertices|
							aiProcess_GenSmoothNormals);
	if(!scene){
		fprintf(stderr, "Failed to load model '%s' \n '%s'\n ", filePath, importer.GetErrorString());
		return false;
	}
	
	const aiMesh* mesh = scene-> mMeshes[0];
	if( !mesh )
	{
		fprintf(stderr, "failed to load mesh. \n");
		return false;
	}
	createGeom(mesh);
	return true;
}

void Geometry::createGeom( const aiMesh* mesh )
{
	nrVertices = mesh->mNumVertices;
	nrFaces = mesh->mNumFaces;	
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	// Copy over Vertices
	if(mesh->HasPositions()){
		float* vertices = new float[3*nrVertices];

		for(int i = 0; i<nrVertices; i++)
		{
			vertices[3*i+0] = mesh->mVertices[i].x;
			vertices[3*i+1] = mesh->mVertices[i].y;
			vertices[3*i+2] = mesh->mVertices[i].z;
		}
		printf("\n");
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3*nrVertices*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)NULL);
		glEnableVertexAttribArray(0);
	/*	
		for(int i=0; i<nrVertices; i++)
		{
			printf("%1.2f, %1.2f, %1.2f \n", vertices[3*i], vertices[3*i+1], vertices[3*i+2]);
		}
	*/	
		delete vertices;
	}

	if(mesh->HasTextureCoords(0)){
		float* texCoords = new float[nrVertices * 2];
		for(int i=0; i<nrVertices; i++)
		{
			texCoords[i*2+0] = mesh->mTextureCoords[0][i].x;
			texCoords[i*2+1] = mesh->mTextureCoords[0][i].y;

		}
	
		glGenBuffers(1, &textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer );
		glBufferData(GL_ARRAY_BUFFER, 2*nrVertices*sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
	
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)NULL);
		glEnableVertexAttribArray(1);

		/*
		for(int i=0; i<nrVertices; i++)
		{
			printf("%1.2f, %1.2f \n", texCoords[2*i], texCoords[2*i+1]);
		}
		*/
		delete texCoords;
	}

	if( mesh->HasNormals() ){
		float* normals = new float[3*nrVertices];

		for(int i = 0; i<nrVertices; i++){
			normals[3*i+0]=mesh->mNormals[i].x;
			normals[3*i+1]=mesh->mNormals[i].y;
			normals[3*i+2]=mesh->mNormals[i].z;
		}

		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER,3*nrVertices*sizeof(GLfloat), normals, GL_STATIC_DRAW);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*) NULL);
		glEnableVertexAttribArray(2);
	/*	
		for(int i=0; i<nrVertices; i++)
		{
			printf("%1.2f, %1.2f, %1.2f \n", normals[3*i], normals[3*i+1], normals[3*i+2]);
		}
	*/
		delete normals;
	}


	// Copy over Faces and Normals
	if( mesh->HasFaces()){
		int* faces = new int[3*nrFaces];

		for(int i = 0; i<nrFaces; i++)
		{
			faces[3*i+0] = mesh->mFaces[i].mIndices[0];
			faces[3*i+1] = mesh->mFaces[i].mIndices[1];
			faces[3*i+2] = mesh->mFaces[i].mIndices[2];
		}

		glGenBuffers(1, &faceBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*nrFaces*sizeof(float), faces, GL_STATIC_DRAW);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*) NULL);
		glEnableVertexAttribArray(3);
/*
		for(int i=0; i<nrFaces; i++)
		{
			printf("%d, %d, %d \n", faces[3*i], faces[3*i+1], faces[3*i+2]);
		}
*/	
		delete faces;
	}	
	
	glBindVertexArray(0);
}

void Geometry::draw()
{
	if(state != NULL){
		state->mShader.use();
	}
	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, nrVertices);
	glDrawElements(GL_TRIANGLES, 3*nrFaces, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Geometry::update()
{

}

void Geometry::accept(NodeVisitor& v)
{
	v.apply(this);
}
