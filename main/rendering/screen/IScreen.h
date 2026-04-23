//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ISCREEN_H
#define MATHLIB_MAIN_ISCREEN_H
#include "glad/glad.h"
#include "math/parameters/IColor.h"
#include "rendering/renderable/Renderable2DVertexState.h"

#include <GLFW/glfw3.h>
#include <iostream>

class IScreen {


    public:

    const IColor& screenColor;

    const float& height;

    const float& width;

    float tick;

    GLFWwindow* window;
    unsigned int VAO, VBO, shaderProgram;


    IScreen(const float& height_, const float& width_, const IColor& color) : screenColor(color), height(height_), width(width_) {}

    static void framebuffer_size_callback(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    void init() {

          glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);

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
    // RENDER SETTINGS (DEPOIS DO GLAD)
    // =========================

    glEnable(GL_MULTISAMPLE); // 🔥 ativa MSAA de fato

    glEnable(GL_BLEND); // útil pra transparência e efeitos
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // =========================
    // SHADERS
    // =========================

    const auto vertexShaderSource = R"(
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

    const auto fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 uColor;

    void main() {
        FragColor = uColor;
    }
    )";

    const unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, nullptr);
    glCompileShader(vs);

    const unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, nullptr);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

      glfwSwapInterval(5);

      setCallbacks();

      while (!glfwWindowShouldClose(window)) {
          tick = glfwGetTime();

          int width_, height_;
          glfwGetFramebufferSize(window, &width_, &height_);

          const float aspect = (float)width_ / (float)height_;

          glViewport(0, 0, width_, height_);

          glUseProgram(shaderProgram);

          const int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");
          glUniform1f(aspectLoc, aspect);


          glClearColor(screenColor.getRed(tick)/ 255.0f, screenColor.getGreen(tick)/ 255.0f,
              screenColor.getBlue(tick)/ 255.0f, screenColor.getAlpha(tick)/ 255.0f);



          glClear(GL_COLOR_BUFFER_BIT);


          render();

          glfwSwapBuffers(window);
          glfwPollEvents();
      }

      glfwTerminate();
    }

    virtual void setCallbacks() = 0;

    virtual void render() = 0;

    virtual void renderLine(const Renderable2DVertexState& p1, const Renderable2DVertexState& p2, const float& thickness) const = 0;



};

#endif //MATHLIB_MAIN_ISCREEN_H
