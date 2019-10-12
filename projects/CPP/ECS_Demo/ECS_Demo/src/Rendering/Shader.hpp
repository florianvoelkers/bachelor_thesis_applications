#pragma once

// external libraries
#include <glm/glm.hpp>
#include <glad/glad.h>

// standard libraries
#include <string>


// taken from: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h

// Holds the functionality needed to represent an OpenGL shader
class Shader 
{
public:
	unsigned int m_ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetVec2(const std::string &name, const glm::vec2 &value) const;
	void SetVec2(const std::string &name, float x, float y) const;
	void SetVec3(const std::string &name, const glm::vec3 &value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;
	void SetVec4(const std::string &name, const glm::vec4 value) const;
	void SetVec4(const std::string &name, float x, float y, float z, float w) const;
	void SetMat2(const std::string &name, const glm::mat2 &mat) const;
	void SetMat3(const std::string &name, const glm::mat3 &mat) const;
	void SetMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	void CheckCompileErrors(GLuint shader, std::string type);
};

