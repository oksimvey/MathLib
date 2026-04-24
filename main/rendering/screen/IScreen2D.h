//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ISCREEN2D_H
#define MATHLIB_MAIN_ISCREEN2D_H
#include "IScreen.h"
#include "math/vectors/Vector2D.h"
#include "rendering/renderable/Renderable2DCurve.h"
#include <cmath>

class IScreen2D : public IScreen {

    public:


    std::vector<Renderable2DCurve<250>> curves;

    float zoom;

    float posx;

    float posy;

    float getLodFactor() const {
        return 1/(32*zoom*zoom);
    }

    IScreen2D(const float& height_, const float& width_, const IColor& color, const Vector2D& pos) : IScreen(height_, width_, color), zoom(1.0f), posx(pos.x), posy(pos.y) {}


    void render() override {

        for (auto& curve : curves) {
            const int step = fmax(1,std::round(getLodFactor()));
            for (int i = 0; i < (curve.getNodes() - step); i+= step) {
                Renderable2DVertexState p1 = curve.getVertex(i);
                Renderable2DVertexState p2 = curve.getVertex(i + step);
                renderLine(p1, p2, 5);
            }
        }

        Renderable2DVertexState p1 = Renderable2DVertexState(-2/zoom+posx, 0, ConstantColorParam(255, 255, 255, 255));
        Renderable2DVertexState p2 = Renderable2DVertexState(2/zoom+posx, 0, ConstantColorParam(255, 255, 255, 255));
        Renderable2DVertexState P1 = Renderable2DVertexState(0, -5/zoom+posy, ConstantColorParam(255, 255, 255, 255));
        Renderable2DVertexState P2 = Renderable2DVertexState(0, 5/zoom+posy, ConstantColorParam(255, 255, 255, 255));
        renderLine(p1, p2, 5);
        renderLine(P1, P2, 5);
        for (int i = std::round(-10/zoom); i < std::round(10/zoom); i++) {
            int t = std::round(posx);
            int t2 = std::round(posy);
            Renderable2DVertexState tx1 = Renderable2DVertexState(i+t, -0.1, ConstantColorParam(255, 255, 255, 255));
            Renderable2DVertexState tx2 = Renderable2DVertexState(i+t, 0.1, ConstantColorParam(255, 255, 255, 255));
            renderLine(tx1, tx2, 2.5f);
            Renderable2DVertexState ty1 = Renderable2DVertexState(-0.1, i+t2, ConstantColorParam(255, 255, 255, 255));
            Renderable2DVertexState ty2 = Renderable2DVertexState(0.1, i+t2, ConstantColorParam(255, 255, 255, 255));
            renderLine(ty1, ty2, 2.5f);
        }
    }



    void setCallbacks() override {

        glfwSetWindowUserPointer(window, this);

        glfwSetScrollCallback(window, scrollCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPositionCallback);
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        IScreen2D* screen = static_cast<IScreen2D*>(glfwGetWindowUserPointer(window));

        if (yoffset > 0) {
            screen->zoom = fmin(screen-> zoom + 0.05f, 2);
        }
        else if (yoffset < 0) {
            screen->zoom = fmax(0.05f, screen->zoom - 0.05f);
        }
    }

    bool dragging = false;
    double lastX = 0, lastY = 0;

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        IScreen2D* screen = static_cast<IScreen2D*>(glfwGetWindowUserPointer(window));
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
        auto* screen = static_cast<IScreen2D*>(glfwGetWindowUserPointer(window));
        if (!screen || !screen->dragging) return;

        const float& dx = xpos - screen->lastX;
        const float& dy = ypos - screen->lastY;
        const float& divisor = 250 * screen->zoom;

        screen-> posx -= dx / divisor;
        screen-> posy += dy / divisor;

        screen->lastX = xpos;
        screen->lastY = ypos;
    }



    std::array<float, 2> toScreen(const float& x, const float& y) const {
        return {(x - posx) * zoom, (y - posy) * zoom};
    }

    std::array<float, 2> toScreen(const Renderable2DVertexState& vertex_state) const {
        return toScreen(vertex_state.x, vertex_state.y);
    }

    void renderLine(const Renderable2DVertexState& p1, const Renderable2DVertexState& p2, const float& thickness) const override {

        const std::array<float, 2> P1 = toScreen(p1);
        const std::array<float, 2> P2 = toScreen(p2);

        const float vertices[] = {
            P1[0], P1[1], 0.0f,
            p1.getRed() / 255.0f, p1.getGreen() / 255.0f, p1.getBlue() / 255.0f, p1.getAlpha() / 255.0f,

            P2[0], P2[1], 0.0f,
            p2.getRed() / 255.0f, p2.getGreen() / 255.0f, p2.getBlue() / 255.0f, p2.getAlpha() / 255.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glLineWidth(thickness*zoom);
        glDrawArrays(GL_LINES, 0, 2);
    }

};

#endif //MATHLIB_MAIN_ISCREEN2D_H
