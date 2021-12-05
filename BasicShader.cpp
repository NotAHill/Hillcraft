#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
    : Shader(vertexFile, fragmentFile)
{
    getUniforms();
}

void BasicShader::loadProjectionMatrix(const Matrix4& matrix)
{
    loadMatrix4(locPvMatrix, matrix);
}

void BasicShader::loadModelMatrix(const Matrix4& matrix)
{
    loadMatrix4(locModelMatrix, matrix);
}

void BasicShader::getUniforms()
{
    useProgram();
    locPvMatrix = glGetUniformLocation(id, "projViewMatrix");
    locModelMatrix = glGetUniformLocation(id, "modelMatrix");
}