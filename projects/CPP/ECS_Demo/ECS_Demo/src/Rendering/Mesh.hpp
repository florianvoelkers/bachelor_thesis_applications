#pragma once

// external libraries
#include <glm/vec3.hpp>

// standard libraries
#include <vector>

enum BasicMeshes
{
	CUBE, SPHERE
};

class Mesh
{
public:
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
	unsigned int m_VertexArrayObject;

	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
	Mesh(BasicMeshes meshType);

	void Draw();

private:

	void SetupMesh();
	void SetupCube();
	void SetupSphere();
};