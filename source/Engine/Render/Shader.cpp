#include "Shader.h"

Shader::Shader(const string& vertexName, const string& fragmentName)
{
	ResourceManager& manager = ResourceManager::getInstance();
	Resource* vertex = manager.getResource(vertexName);
	Resource* fragment = manager.getResource(fragmentName);

	stringstream vertexStream, fragmentStream;
	vertexStream << vertex->getShader().rdbuf();
	fragmentStream << fragment->getShader().rdbuf();

    string vertexCode, fragmentCode;
    vertexCode = vertexStream.str();
    fragmentCode = fragmentStream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cerr << "[Error] 버텍스 셰이더 컴파일 실패: " << infoLog << endl;
        cout << "Process Terminated" << endl;
        exit(0);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cerr << "[Error] 프래그먼트 셰이더 컴파일 실패: " << infoLog << endl;
        cout << "Process Terminated" << endl;
        exit(0);
    }

    shaderId = glCreateProgram();

    glAttachShader(shaderId, vertexShader);
    glAttachShader(shaderId, fragmentShader);
    glLinkProgram(shaderId);

    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        cerr << "[Error] 셰이더 프로그램 링크 실패: " << infoLog << endl;
        cout << "Process Terminated" << endl;
        exit(0);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}