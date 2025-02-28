#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class Shader {
private:
  unsigned int handle;
  GLenum type;
  std::string source_code;
  void read_file(std::string file_name);
public:
  Shader() = default;
  void create(std::string file_name, GLenum type);
  GLenum get_type();
  unsigned int get_handle();
  void check_errors();
  void destroy();
};

class ShaderProgram {
private:
  unsigned int handle;
public:
  ShaderProgram() = default;
  void create(Shader* vertex, Shader* fragment);
  /// @brief its just use program
  void bind();
  void unbind();
  unsigned int get_handle();
  void check_errors();
  void destroy();

  void send_uniform_float(std::string uniform, float data);
  void send_uniform_float2(std::string uniform, float x, float y);
  void send_uniform_float3(std::string uniform, float x, float y, float z);
  void send_uniform_float4(std::string uniform, float x, float y, float z, float w);
};