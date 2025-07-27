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
  this->m_Handle = glCreateShader(type);
  glShaderSource(this->m_Handle, 1, &data, NULL);
  glCompileShader(this->m_Handle);
  this->type = type;
  this->check_errors();
}

GLenum Shader::get_type() {
  return this->type;
}

unsigned int Shader::GetHandle() {
  return this->m_Handle;
}

void Shader::check_errors() {
  int success;
  char err_out[1024];
  glGetShaderiv(this->m_Handle, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->m_Handle, 1024, NULL, err_out);
    std::fprintf(stderr, "[SHADER ERROR] %s\n", err_out);
  }
}

void Shader::destroy() {
  glDeleteShader(this->m_Handle);
}

void ShaderProgram::CreateProgram(Shader* vertex, Shader* fragment) {
  this->m_Handle = glCreateProgram();
  glAttachShader(this->m_Handle, vertex->GetHandle());
  glAttachShader(this->m_Handle, fragment->GetHandle());
  glLinkProgram(this->m_Handle);
  this->CheckErrors();
  vertex->destroy();
  fragment->destroy();
  this->BindProgram(); //basically use_program!
}

void ShaderProgram::BindProgram() {
  glUseProgram(this->m_Handle);
}

void ShaderProgram::UnbindProgram() {
  glUseProgram(0);
}

unsigned int ShaderProgram::GetHandle() {
  return this->m_Handle;
}

void ShaderProgram::CheckErrors() {
  int success;
  char err_out[1024];
  glGetShaderiv(this->m_Handle, GL_LINK_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->m_Handle, 1024, NULL, err_out);
    std::fprintf(stderr, "[SHADER PROGRAM ERROR] %s\n", err_out);
  }
}

void ShaderProgram::Destroy() {
  this->UnbindProgram();
  glDeleteProgram(this->m_Handle);
}

void ShaderProgram::send_uniform_float(std::string uniform, float data) {
  glUniform1f(glGetUniformLocation(this->m_Handle, uniform.c_str()), data);
}
void ShaderProgram::send_uniform_float2(std::string uniform, float x, float y) {
  glUniform2f(glGetUniformLocation(this->m_Handle, uniform.c_str()), x, y);
}

void ShaderProgram::send_uniform_float3(std::string uniform, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(this->m_Handle, uniform.c_str()), x, y, z);
}

void ShaderProgram::send_uniform_float4(std::string uniform, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(this->m_Handle, uniform.c_str()), x, y, z, w);
}

void ShaderProgram::CreateUniformBlock(const std::string& block_name) {

};
