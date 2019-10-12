// internal code
#include "Model.hpp"

// standard libraries
#include <iostream>

// external libraries
#include <glm/vec3.hpp>

Model::Model(const std::string& path)
{
	LoadModel(path);
}

Model::Model(BasicMeshes meshType)
{
	m_Meshes.push_back(Mesh(meshType));
}

void Model::Draw(const Shader& shader)
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
		m_Meshes[i].Draw();
}

void Model::LoadModel(const std::string& path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 vector;

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;

		vertices.push_back(vector);
	}

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices);
}
