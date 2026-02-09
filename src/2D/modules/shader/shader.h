#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>


class ShaderModule
{
private:
	unsigned int ID;
	void check_compile_errors(GLuint shader, const std::string& type);
public:
	ShaderModule();
	ShaderModule(const char* vertex_path, const char* fragment_path, const char* geometry_path = nullptr);
	void generate(const char* vertex_path, const char* fragment_path, const char* geometry_path = nullptr);

	void use() const;
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void set_vec2(const std::string& name, float x, float y) const;
	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void set_vec3(const std::string& name, float x, float y, float z) const;
	void set_vec4(const std::string& name, const glm::vec4& value) const;
	void set_vec4(const std::string& name, float x, float y, float z, float w) const;
	void set_mat2(const std::string& name, const glm::mat2& mat) const;
	void set_mat3(const std::string& name, const glm::mat3& mat) const;
	void set_mat4(const std::string& name, const glm::mat4& mat) const;

	unsigned int get_ID();
};