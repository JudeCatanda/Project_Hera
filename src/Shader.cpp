#include "Shader.hpp"

void CShader::readFile(std::string fileName) {
    std::string shader_souce;
    std::ifstream shader_file;
    shader_file.open(fileName);
    
    if(!shader_file.is_open()) {
        std::fprintf(stderr, "[ERROR] file not found: %s\n", fileName.c_str());
        return;
    }
    
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    
    shader_file.close();
    
    shader_souce = shader_stream.str();
    m_szShaderSourceCode =  shader_souce; //bad??
}

void CShader::Create(std::string szFileName, GLenum nType) {
        readFile(szFileName);
        const char* data = m_szShaderSourceCode.c_str(); // also bad???
        this->m_nHandle = glCreateShader(nType);
        glShaderSource(this->m_nHandle, 1, &data, nullptr);
        glCompileShader(this->m_nHandle);
        this->m_nShaderType = nType;
        CheckErrors();
}

GLenum CShader::GetShaderType() const  {
    return m_nShaderType; 
}

unsigned int CShader::GetHandle() const {
    return m_nHandle;
}

void CShader::CheckErrors() {
    int nSuccess;
    char szErrorBuffer[1024];
    glGetShaderiv(this->m_nHandle, GL_COMPILE_STATUS, &nSuccess);
    if(!nSuccess) {
        glGetShaderInfoLog(this->m_nHandle, 1024, nullptr, szErrorBuffer);
        std::fprintf(stderr, "[SHADER ERROR] %s\n", szErrorBuffer);
    }
}

void CShader::Destroy() {
    glDeleteShader(m_nHandle);
}

void CShaderProgram::CreateProgram(CShader* pVertex, CShader* pFragment) {
    m_nHandle = glCreateProgram();
    glAttachShader(m_nHandle, pVertex->GetHandle());
    glAttachShader(m_nHandle, pFragment->GetHandle());
    glLinkProgram(m_nHandle);
    CheckErrors();
    pVertex->Destroy();
    pFragment->Destroy();
    BindProgram();
}

void CShaderProgram::BindProgram() {
    glUseProgram(m_nHandle);
}

void CShaderProgram::UnbindProgram() {
    glUseProgram(0);
}

unsigned int CShaderProgram::GetHandle() const {
    return m_nHandle;
}

void CShaderProgram::CheckErrors() {
    int nSuccess;
    char szErrorBuffer[1024];
    glGetShaderiv(this->m_nHandle, GL_COMPILE_STATUS, &nSuccess);
    if(!nSuccess) {
        glGetShaderInfoLog(this->m_nHandle, 1024, nullptr, szErrorBuffer);
        std::fprintf(stderr, "[SHADER ERROR] %s\n", szErrorBuffer);
    }
}

void CShaderProgram::Destroy() {
    UnbindProgram();
    glDeleteProgram(m_nHandle);
}

void CShaderProgram::CreateUniformBlock(const std::string& szBlockName) {

};
