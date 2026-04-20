#ifndef SCREEN2D_H
#define SCREEN2D_H

#include "math/transformations/LinearTransformation.h"
#include "math/vectors/Vector2D.h"
#include "math/vectors/AbstractVector.h"
#include "rendering/Line.h"
#include "rendering/screen/AbstractScreen.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
class Screen2D : public AbstractScreen<2> {

public:

    float zoom = 1.0f;

    Screen2D(const int w, const int h, const AbstractVector<2> pos)
        : AbstractScreen(w, h, pos) {}

    GLFWwindow* window;

    unsigned int VAO, VBO;
    unsigned int shaderProgram;

    static void framebuffer_size_callback(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

 void init() override {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width_, height_, "OpenGL Window", NULL, NULL);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to init GLAD\n";
        return;
    }

    // =========================
    // SHADERS
    // =========================

    const char* vertexShaderSource = R"(
   #version 330 core
layout(location = 0) in vec3 aPos;

uniform float aspect;

void main()
{
    vec2 pos = aPos.xy;

    pos.x /= aspect;

    gl_Position = vec4(pos, 0.0, 1.0);
}

    )";

    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 uColor;

    void main() {
        FragColor = uColor;
    }
    )";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // =========================
    // VAO / VBO
    // =========================

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


        glfwSetWindowUserPointer(window, this);
        glfwSetScrollCallback(window, scrollCallback);


        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPositionCallback);

        glfwSwapInterval(2);

}

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        Screen2D* screen = static_cast<Screen2D*>(glfwGetWindowUserPointer(window));

        if (yoffset > 0) {
            screen->zoom = fmin(screen-> zoom + 0.05f, 2);
        }
        else if (yoffset < 0) {
            screen->zoom = fmax(0.25f, screen->zoom - 0.05f);
        }
    }

    bool dragging = false;
    double lastX = 0, lastY = 0;
    Vector2D pos;

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        Screen2D* screen = static_cast<Screen2D*>(glfwGetWindowUserPointer(window));
        if (!screen) return;

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                screen->dragging = true;
                glfwGetCursorPos(window, &screen->lastX, &screen->lastY);
            }
            else if (action == GLFW_RELEASE) {
                screen->dragging = false;
            }
        }
    }

    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        auto* screen = static_cast<Screen2D*>(glfwGetWindowUserPointer(window));
        if (!screen || !screen->dragging) return;

       float dx = xpos - screen->lastX;
       float dy = ypos - screen->lastY;

        screen-> position.components[0] += -dx / 100;
        screen-> position.components[1]  += dy / 100;

        screen->lastX = xpos;
        screen->lastY = ypos;
    }



    void loop() override {

     while (!glfwWindowShouldClose(window)) {


         int width, height;
         glfwGetFramebufferSize(window, &width, &height);

         const float aspect = (float)width / (float)height;

         glViewport(0, 0, width, height);

         glUseProgram(shaderProgram);

         const int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");
         glUniform1f(aspectLoc, aspect);


         glClearColor(0.1f, 0.1f, 0.15f, 1.0f);



         glClear(GL_COLOR_BUFFER_BIT);


         for (const Line& line : lines) {
                 renderLine(line);
         }

         glfwSwapBuffers(window);
         glfwPollEvents();
     }

     glfwTerminate();
 }



    void renderLine(const Line& line) override {

     const AbstractVector<2> p1 = (AbstractVector<2>(line.x1(), line.y1()) - position) * zoom;

        const AbstractVector<2> p2 =  (AbstractVector<2>(line.x2(), line.y2()) - position) * zoom;

    const float vertices[] = {
        p1.getComponents()[0], p1.getComponents()[1], 0.0f,
         p2.getComponents()[0], p2.getComponents()[1], 0.0f
     };

     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

     glUseProgram(shaderProgram);

     const int loc = glGetUniformLocation(shaderProgram, "uColor");

     glUniform4f(loc, line.r(), line.g(), line.b(), line.g());

     glBindVertexArray(VAO);
     glDrawArrays(GL_LINES, 0, 2);
     glLineWidth(fmin(line.thickness(), line.thickness() * zoom));
 }

};

#endif
