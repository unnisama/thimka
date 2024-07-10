#include "shader.h"

Shader::Shader(const char *fragpath, const char *vertpath)
{
    auto frag = readFile(fragpath);
    auto vert = readFile(vertpath);

    GLDEBUGCALL(vs = glCreateShader(GL_VERTEX_SHADER));
    GLDEBUGCALL(fs = glCreateShader(GL_FRAGMENT_SHADER));

    auto fragp = frag.c_str();
    auto vertp = vert.c_str();

    GLDEBUGCALL(glShaderSource(vs, 1, &vertp, nullptr));
    GLDEBUGCALL(glShaderSource(fs, 1, &fragp, nullptr));

    GLDEBUGCALL(glCompileShader(vs));
    GLDEBUGCALL(glCompileShader(fs));

    if (!LogError())
    {
        return;
    }

    GLDEBUGCALL(program = glCreateProgram());
    GLDEBUGCALL(glAttachShader(program, vs));
    GLDEBUGCALL(glAttachShader(program, fs));
    GLDEBUGCALL(glLinkProgram(program));
    GLDEBUGCALL(glValidateProgram(program));

    GLDEBUGCALL(glDeleteShader(vs));
    GLDEBUGCALL(glDeleteShader(fs));
}

void Shader::Delete()
{
    if (status)
    {
        status = false;
        GLDEBUGCALL(glDeleteProgram(program));
    }
}

bool Shader::LogError()
{
    int result;
    GLDEBUGCALL(glGetShaderiv(vs, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLDEBUGCALL(glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)malloc(length);
        GLDEBUGCALL(glGetShaderInfoLog(vs, length, &length, message));

        std::cout << "Failed to compile vertex shader!" << std::endl;

        std::cout << message << std::endl;
        GLDEBUGCALL(glDeleteShader(vs));
        free(message);
    }

    int result1;
    GLDEBUGCALL(glGetShaderiv(fs, GL_COMPILE_STATUS, &result1));

    if (result1 == GL_FALSE)
    {
        int length;
        GLDEBUGCALL(glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)malloc(length);
        GLDEBUGCALL(glGetShaderInfoLog(fs, length, &length, message));

        std::cout << "Failed to compile fragment shader!" << std::endl;

        std::cout << message << std::endl;
        GLDEBUGCALL(glDeleteShader(fs));
        free(message);
    }

    status = bool(result1 && result);
    return status;
}

GLuint Shader::GetUniformLocation(const GLchar *name)
{
    auto it = uniformStored.find(name);
    if(it != uniformStored.end()){
        return it->second;
    }

    int ret;
    GLDEBUGCALL(ret = glGetUniformLocation(program, name));
    if (ret == -1){
        printf("[Uniform Error] %s doesn't exist\n", name);
        return -1;
    }
    uniformStored[name] = ret;
    return ret;
}

void Shader::SetUniform1f(const GLchar *name, float v)
{
    GLDEBUGCALL(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(const GLchar *name, float v0, float v1, float v2, float v3)
{
    GLDEBUGCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const GLchar *name, float v0, float v1, float v2)
{
    GLDEBUGCALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}


void Shader::SetMat4f(const GLchar *name, glm::mat4& m4)
{
    GLDEBUGCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m4)));
}
void Shader::SetMat4f(const GLchar *name, float *data, int count)
{
    GLDEBUGCALL(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, data));
}
void Shader::SetVec3f(const GLchar *name, float *data, int count)
{
    GLDEBUGCALL(glUniform3fv(GetUniformLocation(name), count, data));
}
void Shader::SetUniform1i(const GLchar *name, int v)
{
    GLDEBUGCALL(glUniform1i(GetUniformLocation(name), v));
}

Shader::~Shader()
{
    if (status)
    {
        GLDEBUGCALL(glDeleteProgram(program));
    }
}

std::string Shader::readFile(const char *path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        perror("couldn't load shader");
        glfwTerminate();
        exit(-1);
    }

    std::stringstream code;

    std::string line;

    while (std::getline(file, line))
    {
        code << line << std::endl;
    }

    file.close();

    return code.str();
}

bool Shader::GetStatus()
{
    return status;
}

void Shader::Use()
{
    GLDEBUGCALL(glUseProgram(program));
}
