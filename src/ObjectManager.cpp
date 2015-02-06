#include "ObjectManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <exception>

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	while(!geometries.empty())
	{
		geometries.pop_back();
	}
}

int ObjectManager::loadFile(const char* filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
							aiProcess_Triangulate | 
							aiProcess_JoinIdenticalVertices |
							aiProcess_GenNormals);
	if(!scene){
		fprintf(stderr, "Failed to load model '%s' \n '%s'\n ", filePath, importer.GetErrorString());
		return -1;
	}
	
	int meshCount = 0;
	for(int i=0; i<scene->mNumMeshes; i++){
	
		const aiMesh* mesh = scene-> mMeshes[0];
		if( !mesh || !createGeomStruct(mesh) )
		{
			fprintf(stderr, "failed to load mesh number %d in scene \n", i);
			return 0;
		}
		loadGeomToGPU(&geometries.back());
		meshCount++;	
	}
	return meshCount;	
}

bool ObjectManager::createGeomStruct(const aiMesh* mesh)
{
	geometry g;
	g.name = NULL;
	gpuBufferData gpuData;
	g.data.vertex_vbo = 0;

	g.nrVertices = mesh->mNumVertices;
	g.nrFaces = mesh->mNumFaces;	

	float* verticeArray = NULL;
	float* normalsArray = NULL;
	int* faceArray = NULL; 

	try{
		g.vertices = new float[3*g.nrVertices];
		g.faces = new int[3*g.nrFaces];
		g.normals = new float[3*g.nrFaces];
	}catch(const std::bad_alloc& e){
		fprintf(stderr,"%s \n", e.what() );
		return false;
	}
	
	// Copy over Vertices
	for(int i = 0; i<g.nrVertices; i++)
	{
		aiVector3D v3 = mesh->mVertices[i];
		g.vertices[3*i+0] = v3[0];
		g.vertices[3*i+1] = v3[1];
		g.vertices[3*i+2] = v3[2];
	}	
	
	// Copy over Faces and Normals
	for(int i = 0; i<g.nrFaces; i++)
	{
		const aiFace& faceStruct = mesh->mFaces[i];
		
		unsigned int* f3 = faceStruct.mIndices;
		
		g.faces[3*i+0] = f3[0];
		g.faces[3*i+1] = f3[1];
		g.faces[3*i+2] = f3[2];

		aiVector3D n3 = mesh->mNormals[i];
		g.normals[3*i+0]=n3[0];
		g.normals[3*i+1]=n3[1];
		g.normals[3*i+2]=n3[2];
	}
	g.ID = geometries.size();
	geometries.push_back(g);	
	//printGeomStruct(&g);
	return true;
}


void ObjectManager::printGeomStruct(geometry* g)
{
	printf("\nVertices:\n\n");
	for(int i=0; i<g->nrVertices; i++)
	{
		printf("%f, %f, %f \n",g->vertices[i*3+0], g->vertices[i*3+1], g->vertices[i*3+2]);
	}

	printf("\nFaces - Normals:\n\n");
	for(int i=0; i<g->nrFaces; i++)
	{
		printf("%d, %d, %d", g->faces[i*3+0], g->faces[i*3+1], g->faces[i*3+2]);
		printf(" - %f, %f, %f \n", g->normals[i*3+0], g->normals[i*3+1], g->normals[i*3+2]);
	}
}

void ObjectManager::loadGeomToGPU(geometry* g)
{
	//Generate VBO and VAO
	GLuint& VBO = g->data.vertex_vbo;
	GLuint& VAO = g->data.vertex_vao;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	
	// Bind our VAO
	glBindVertexArray(VAO);

	// Upload our data to the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3*g->nrVertices*sizeof(float), g->vertices, GL_STATIC_DRAW );

	// Bind our VBO and define how the data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Unbind our VAO 
	glBindVertexArray(0);
}
/*
void ObjectManager::loadFacesToGPU()
{
	GLuint& VBO = g->data.face_vbo;
	GLuint& VAO = g->data.face_vao;

	glGenVertexArrays();
}
*/
ObjectManager::gpuBufferData ObjectManager::getGeometryBufferData(int idx){
	return geometries[idx].data;
}
