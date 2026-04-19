#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

// shaders
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform float aspect;

void main()
{
    gl_Position = vec4(aPos.x / aspect, aPos.y, aPos.z, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.6, 0.2, 1.0);
}
)";

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Curva Parametrica", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // =========================
    // CURVA PARAMÉTRICA (círculo)
    // =========================
    std::vector<float> vertices;

    float T = 2.0f * 3.1415926535f;
    int N = 2000;

    for (int i = 0; i < N; i++) {
        float t = (float)i / (N - 1) * T;

        float x = cos(t);
        float y = sin(t);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    // =========================
    // OPENGL BUFFERS
    // =========================
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(float),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // =========================
    // SHADERS
    // =========================
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // pega location do uniform
    int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");

    // =========================
    // LOOP
    // =========================
    while (!glfwWindowShouldClose(window)) {

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float aspect = (float)width / (float)height;

        glViewport(0, 0, width, height);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glUniform1f(aspectLoc, aspect);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, N);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}