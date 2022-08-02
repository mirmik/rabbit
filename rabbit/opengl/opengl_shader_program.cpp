#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/opengl/util.h>

rabbit::opengl_shader_program::opengl_shader_program() {}

rabbit::opengl_shader_program::opengl_shader_program(
    const char * vShaderCode,
    const char * fShaderCode) 
{
	open(vShaderCode, fShaderCode);
}


void rabbit::opengl_shader_program::open(
    const char * vShaderCode,
    const char * fShaderCode)
{
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		abort();
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		abort();
	}
	// Shader Program
	this->Program = glCreateProgram();
	GLCHECK(glAttachShader(this->Program, vertex));
	GLCHECK(glAttachShader(this->Program, fragment));
	GLCHECK(glLinkProgram(this->Program));
	// Print linking errors if any
	GLCHECK(glGetProgramiv(this->Program, GL_LINK_STATUS, &success));
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		abort();
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	GLCHECK(glDeleteShader(vertex));
	GLCHECK(glDeleteShader(fragment));
}

// Uses the current shader
void rabbit::opengl_shader_program::use()
{
	GLCHECK(glUseProgram(this->Program));
}


void rabbit::opengl_shader_program::uniform_vec3f(
    const char * locname, const linalg::vec<float, 3> & v)
{
	GLint modelLoc = glGetUniformLocation(Program, locname);
	GLCHECK(glUniform3fv(modelLoc, 1, (GLfloat*) &v));
}


void rabbit::opengl_shader_program::uniform_mat4f(
    const char * locname, const linalg::mat<float, 4, 4> & v)
{
	GLint modelLoc = glGetUniformLocation(Program, locname);
	GLCHECK(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*) &v));
}