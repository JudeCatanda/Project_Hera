#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class CShader {
    private:
    unsigned int m_nHandle;
    GLenum m_nShaderType;
    std::string m_szShaderSourceCode;
    void readFile(std::string szFileName);

    public:
    CShader() = default;
    void                               Create(std::string szFileName, GLenum nType);
    GLenum                             GetShaderType() const;
    unsigned int                       GetHandle() const;
    void                               CheckErrors();
    void                               Destroy();
};

class CShaderProgram {
    private:
    unsigned int m_nHandle;
    unsigned int m_nBlockIndex;

    public:
    CShaderProgram() = default;
    void                               CreateProgram(CShader* pVertex, CShader* pFragment);
    void                               BindProgram();
    void                               UnbindProgram();
    unsigned int                       GetHandle() const;
    void                               CheckErrors();
    void                               Destroy();

    void                               CreateUniformBlock(const std::string& szBlockName);
};
