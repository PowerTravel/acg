#include "Geometry.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Geometry::Geometry(const char* filePath)
{

	nrVertices = 0;
	vertices = NULL;
	normals = NULL;

	nrFaces = 0;
	faces = NULL;

	loadFile(filePath);
}

Geometry::~Geometry()
{
	if(vertices !=NULL)
	{
		delete[] vertices;
	}
	if(normals !=NULL)
	{
		delete[] normals;
	}
	if(faces != NULL)
	{
		delete[] faces;
	}
}

bool  Geometry::loadFile(const char* filePath){

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
							aiProcess_Triangulate | 
							aiProcess_JoinIdenticalVertices |
							aiProcess_GenNormals);
	if(!scene){
		fprintf(stderr, "Failed to load model '%s' \n '%s'\n ", filePath, importer.GetErrorString());
		return false;
	}
	
	const aiMesh* mesh = scene-> mMeshes[0];
	if( !mesh || !createGeom(mesh) )
	{
		fprintf(stderr, "failed to load mesh. \n");
		return false;
	}
	return true;
}

bool Geometry::createGeom( const aiMesh* mesh )
{
	nrVertices = mesh->mNumVertices;
	nrFaces = mesh->mNumFaces;	

//	vertices = std::vector<float>(3*nrVertices);
//	faces = std::vector<int>(3 * nrFaces);
//	normals = std::vector<float>(3*nrVertices);

	try{
		vertices = new float[3*nrVertices];
		normals = new float[3*nrVertices];
		faces = new int[3*nrFaces];
	}catch(const std::bad_alloc& e){
		fprintf(stderr,"%s \n", e.what() );
		return false;
	}


	// Copy over Vertices
	for(int i = 0; i<nrVertices; i++)
	{
		aiVector3D v3 = mesh->mVertices[i];
		vertices[3*i+0] = v3[0];
		vertices[3*i+1] = v3[1];
		vertices[3*i+2] = v3[2];
		
		aiVector3D n3 = mesh->mNormals[i];
		normals[3*i+0]=n3[0];
		normals[3*i+1]=n3[1];
		normals[3*i+2]=n3[2];
	}
	
	// Copy over Faces and Normals
	for(int i = 0; i<nrFaces; i++)
	{
		const aiFace& faceStruct = mesh->mFaces[i];
		
		unsigned int* f3 = faceStruct.mIndices;
		
		faces[3*i+0] = f3[0];
		faces[3*i+1] = f3[1];
		faces[3*i+2] = f3[2];
	}
	
	print();
	return true;
}

void Geometry::loadToVBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nrVertices*sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrFaces*sizeof(int), faces, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Geometry::draw()
{
	glUseProgram(state->program);
	glBindVertexArray(VAO);	
	glDrawElements(GL_TRIANGLES, nrFaces, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Geometry::print()
{
	printf("\nVertices:\n\n");
	for(int i=0; i<nrVertices; i++)
	{
		printf("%1.2f, %1.2f, %1.2f ",vertices[i*3+0], vertices[i*3+1], vertices[i*3+2]);
		printf(" - %1.2f, %1.2f, %1.2f \n", normals[i*3+0], normals[i*3+1], normals[i*3+2]);
	}

	printf("\nFaces - Normals:\n\n");
	for(int i=0; i<nrFaces; i++)
	{
		printf("%d, %d, %d \n", faces[i*3+0], faces[i*3+1], faces[i*3+2]);
	}
}
