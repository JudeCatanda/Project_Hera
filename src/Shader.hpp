#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class CShader {
private:
  unsigned int m_Handle;
  GLenum m_ShaderType;
  std::string m_ShaderSourceCode;
  void readFile(std::string fileName);
public:
  CShader() = default;
  void Create(std::string fileName, GLenum type);
  GLenum Type() const;
  unsigned int Handle() const;
  void CheckErrors();
  void Destroy();
};

class CShaderProgram {
private:
  unsigned int m_Handle;
  unsigned int m_BlockIndex;
public:
  CShaderProgram() = default;
  void CreateProgram(CShader* vertex, CShader* fragment);
  /// @brief its just use program
  void BindProgram();
  void UnbindProgram();
  unsigned int Handle() const;
  void CheckErrors();
  void Destroy();

  void CreateUniformBlock(const std::string& block_name);

  void send_uniform_float(std::string uniform, float data);
  void send_uniform_float2(std::string uniform, float x, float y);
  void send_uniform_float3(std::string uniform, float x, float y, float z);
  void send_uniform_float4(std::string uniform, float x, float y, float z, float w);
};
