#pragma once

// standard libraries
#include <vector>
#include <string>

// external libraries
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// internal code
#include "Mesh.hpp"
#include "Shader.hpp"

class Model
{
public:
	std::vector<Mesh> m_Meshes;

	Model(const std::string& path);
	Model(BasicMeshes meshType);

	void Draw(const Shader& shader);

private:
	// loads a model with supported assimp extensions from file and stores the resulting meshes in the meshes vector
	void LoadModel(const std::string& path);
	// processes a node in a recursive fashion. Processes each individual mesh located at the node 
	// and repeats this process on its children nodes (if any)
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};