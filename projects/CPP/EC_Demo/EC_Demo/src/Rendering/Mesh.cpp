// external libraries
#include <glad/glad.h>

// internal code
#include "Mesh.hpp"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
	: m_Vertices(vertices), m_Indices(indices)
{
	SetupMesh();
}

Mesh::Mesh(BasicMeshes meshType)
{
	if (meshType == BasicMeshes::CUBE)
		SetupCube();
}

void Mesh::Draw()
{
	glBindVertexArray(m_VertexArrayObject);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::SetupMesh()
{
	// create buffers
	glGenVertexArrays(1, &m_VertexArrayObject);
	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(m_VertexArrayObject);
	//load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// since the memory layout of a struct is sequential for all its items
	// we can pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array
	// which again translates to 3/2 floats which translates to a byte array
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), &m_Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindVertexArray(0);
}

void Mesh::SetupCube()
{
	// adding the vertices
	// front face
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));

	// right face
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));

	// back face
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));

	// left face
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));

	// upper face
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));

	// bottom face
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));
	m_Vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));
	m_Vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));

	// adding the indices
	// front face
	m_Indices.push_back(0);
	m_Indices.push_back(1);
	m_Indices.push_back(2);
	m_Indices.push_back(0);
	m_Indices.push_back(2);
	m_Indices.push_back(3);

	// right face
	m_Indices.push_back(4);
	m_Indices.push_back(5);
	m_Indices.push_back(6);
	m_Indices.push_back(4);
	m_Indices.push_back(6);
	m_Indices.push_back(7);

	// back face
	m_Indices.push_back(8);
	m_Indices.push_back(9);
	m_Indices.push_back(10);
	m_Indices.push_back(8);
	m_Indices.push_back(10);
	m_Indices.push_back(11);

	// left face
	m_Indices.push_back(12);
	m_Indices.push_back(13);
	m_Indices.push_back(14);
	m_Indices.push_back(12);
	m_Indices.push_back(14);
	m_Indices.push_back(15);

	// upper face
	m_Indices.push_back(16);
	m_Indices.push_back(17);
	m_Indices.push_back(18);
	m_Indices.push_back(16);
	m_Indices.push_back(18);
	m_Indices.push_back(19);

	// bottom face
	m_Indices.push_back(20);
	m_Indices.push_back(21);
	m_Indices.push_back(22);
	m_Indices.push_back(20);
	m_Indices.push_back(22);
	m_Indices.push_back(23);

	SetupMesh();
}
