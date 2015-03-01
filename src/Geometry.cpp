#include "Geometry.hpp"
#include "RenderVisitor.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Geometry::Geometry() 
{
	nrVertices = 0;
	nrFaces = 0;
	_cm = Vec3();
	loaded = false;
}

Geometry::Geometry(const aiMesh* mesh)
{
	nrVertices = 0;
	nrFaces = 0;
	
	createGeom(  mesh );
	loaded = true;	
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

geometry_vec Geometry::loadFile(const char* filePath){

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
							aiProcess_OptimizeMeshes |
							aiProcess_Triangulate | 
							aiProcess_JoinIdenticalVertices|
							aiProcess_GenSmoothNormals);
	if(!scene){
		fprintf(stderr, "Failed to load model '%s' \n '%s'\n ", filePath, importer.GetErrorString());
		return geometry_vec();
	}
	//geom_mat_vec geomMatVec = geom_mat_vec(scene->mNumMeshes);
	geometry_vec geomVec = geometry_vec(scene->mNumMeshes);
	for(int i=0; i<scene->mNumMeshes; i++){

		aiMesh* mesh = scene-> mMeshes[i];
		if( !mesh )
		{
			fprintf(stderr, "failed to load mesh. \n");
		}else{
			geomVec[i] = geometry_ptr(new Geometry(mesh));

			if(mesh->mMaterialIndex != 0){
				aiMaterial* mat =scene->mMaterials[mesh->mMaterialIndex];
				State materialState = State();
				materialState.setMaterial(Material(mat));
				geomVec[i] -> setState( &materialState );
			}
		}
	}

	return geomVec;
}

void Geometry::createGeom( const aiMesh* mesh )
{
	nrVertices = mesh->mNumVertices;
	nrFaces = mesh->mNumFaces;	

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Copy over Vertices
	if(mesh->HasPositions()){
//		std::cerr << "Has " << nrVertices << " Vertices" << std::endl;
		float* vertices = new float[3*nrVertices];

		for(int i = 0; i<nrVertices; i++)
		{
			Vec3 v = Vec3(	mesh->mVertices[i].x,
							mesh->mVertices[i].y,
							mesh->mVertices[i].z);
			vertices[3*i+0] = v[0];
			vertices[3*i+1] = v[1];
			vertices[3*i+2] = v[2];
		}

		loadVertices(nrVertices, vertices);

		delete vertices;
	}

	if(mesh->HasTextureCoords(0)){
		//std::cout << "Has Textures" << std::endl;
		float* texCoords = new float[nrVertices * 2];
		for(int i=0; i<nrVertices; i++)
		{
			texCoords[i*2+0] = mesh->mTextureCoords[0][i].x;
			texCoords[i*2+1] = mesh->mTextureCoords[0][i].y;
		}

		loadTextureCoordinates(nrVertices, texCoords);

		delete texCoords;
	}

	if( mesh->HasNormals() ){
//		std::cout << "Has Normals" << std::endl;
		float* normals = new float[3*nrVertices];

		for(int i = 0; i<nrVertices; i++){
			normals[3*i+0]=mesh->mNormals[i].x;
			normals[3*i+1]=mesh->mNormals[i].y;
			normals[3*i+2]=mesh->mNormals[i].z;

			//printf("%d %d %d\n" normals[3*i+0],normals[3*i+1],normals[3*i+2]);
		}
		
		loadNormals(nrVertices, normals);
		
		delete normals;
	}


	// Copy over Faces and Normals
	if( mesh->HasFaces()){
		//std::cout << "Has "<<nrFaces<<" Faces" << std::endl;
		int* faces = new int[3*nrFaces];

		for(int i = 0; i<nrFaces; i++)
		{
			faces[3*i+0] = mesh->mFaces[i].mIndices[0];
			faces[3*i+1] = mesh->mFaces[i].mIndices[1];
			faces[3*i+2] = mesh->mFaces[i].mIndices[2];

		}
		
		loadFaces(nrFaces, faces);

		delete faces;
	}
/*
	if( mesh->HasMaterials())
	{
		std::cout << "We have material \n"<< std::endl;
	}
*/
	glBindVertexArray(0);
}

void Geometry::loadVertices(int nrVertices, float* vertices)
{
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3*nrVertices*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)NULL);
		glEnableVertexAttribArray(VERTEX);
}
void Geometry::loadTextureCoordinates(int nrTexCoords, float* coords)
{
		glGenBuffers(1, &textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer );
		glBufferData(GL_ARRAY_BUFFER, 2*nrTexCoords*sizeof(GLfloat), coords, GL_STATIC_DRAW);
	
		glVertexAttribPointer(TEXTURECOORDINATE, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)NULL);
		glEnableVertexAttribArray(TEXTURECOORDINATE);


}
void Geometry::loadNormals(int nrNormals, float* normals)
{
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3*nrNormals*sizeof(GLfloat), normals, GL_STATIC_DRAW);

		glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*) NULL);
		glEnableVertexAttribArray(NORMAL);

}
void Geometry::loadFaces(int nrFaces, int* faces)
{
	glGenBuffers(1, &faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*nrFaces*sizeof(int), faces, GL_STATIC_DRAW);
	glVertexAttribPointer(FACE, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*) NULL);
	glEnableVertexAttribArray(FACE);
}
void Geometry::draw()
{
	//if(_state != NULL){
	//	_state->getShader().use();
	//}
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3*nrVertices);
	glDrawElements(GL_TRIANGLES, 3*nrFaces, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Geometry::update()
{

}

void Geometry::acceptVisitor(NodeVisitor& v)
{
	v.apply(this);
}

