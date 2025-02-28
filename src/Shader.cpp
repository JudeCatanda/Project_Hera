#include "Shader.hpp"

void Shader::read_file(std::string file_name) {
  std::string shader_souce;
  std::ifstream shader_file;
  shader_file.open(file_name);

  if(!shader_file.is_open()) {
    std::fprintf(stderr, "[ERROR] file not found: %s\n", file_name.c_str());
    return;
  }
  
  std::stringstream shader_stream;
  shader_stream << shader_file.rdbuf();

  shader_file.close();

  shader_souce = shader_stream.str();
  this->source_code = shader_souce; //bad?????????
}

void Shader::create(std::string file_name, GLenum type) {
  this->read_file(file_name);
  const char* data = this->source_code.c_str(); // also bad???
  this->handle = glCreateShader(type);
  glShaderSource(this->handle, 1, &data, NULL);
  glCompileShader(this->handle);
  this->type = type;
  this->check_errors();
}

GLenum Shader::get_type() {
  return this->type;
}

unsigned int Shader::get_handle() {
  return this->handle;
}

void Shader::check_errors() {
  int success;
  char err_out[1024];
  glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->handle, 1024, NULL, err_out);
    std::fprintf(stderr, "[SHADER ERROR] %s\n", err_out);
  }
}

void Shader::destroy() {
  glDeleteShader(this->handle);
}

void ShaderProgram::create(Shader* vertex, Shader* fragment) {
  this->handle = glCreateProgram();
  glAttachShader(this->handle, vertex->get_handle());
  glAttachShader(this->handle, fragment->get_handle());
  glLinkProgram(this->handle);
  this->check_errors();
  vertex->destroy();
  fragment->destroy();
  this->bind(); //basically use_program!
}

void ShaderProgram::bind() {
  glUseProgram(this->handle);
}

void ShaderProgram::unbind() {
  glUseProgram(0);
}

unsigned int ShaderProgram::get_handle() {
  return this->handle;
}

void ShaderProgram::check_errors() {
  int success;
  char err_out[1024];
  glGetShaderiv(this->handle, GL_LINK_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->handle, 1024, NULL, err_out);
    std::fprintf(stderr, "[SHADER PROGRAM ERROR] %s\n", err_out);
  }
}

void ShaderProgram::destroy() {
  this->unbind();
  glDeleteProgram(this->handle);
}

void ShaderProgram::send_uniform_float(std::string uniform, float data) {
  glUniform1f(glGetUniformLocation(this->handle, uniform.c_str()), data);
}
void ShaderProgram::send_uniform_float2(std::string uniform, float x, float y) {
  glUniform2f(glGetUniformLocation(this->handle, uniform.c_str()), x, y);
}

void ShaderProgram::send_uniform_float3(std::string uniform, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(this->handle, uniform.c_str()), x, y, z);
}

void ShaderProgram::send_uniform_float4(std::string uniform, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(this->handle, uniform.c_str()), x, y, z, w);
}
