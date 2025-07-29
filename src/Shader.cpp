#include "Shader.hpp"

void CShader::readFile(std::string szFileName) {
    std::string szSource;
    std::ifstream pFile;
    pFile.open(szFileName);
    
    if(!pFile.is_open()) {
        std::fprintf(stderr, "[ERROR] file not found: %s\n", szFileName.c_str());
        return;
    }
    
    std::stringstream pShaderStream;
    pShaderStream << pFile.rdbuf();
    
    pFile.close();
    
    szSource = pShaderStream.str();
    m_szShaderSourceCode =  szSource; //bad??
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
