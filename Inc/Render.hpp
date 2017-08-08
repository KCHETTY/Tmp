#pragma once

#include "base.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Render
{
    private:
        Shaders shader;

        int Screen_Width;
        int Screen_Height;

        static GLFWwindow *window;
        static Camera *camera;

        static GLfloat lastX;
        static GLfloat lastY;

        static bool keys[1024];
        static bool firstmouse ;

        static GLfloat deltaTime;
        static GLfloat lastFrame;

    public:

        Render();
        ~Render();

        void init();
        void render();
        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
        static void MouseCallback( GLFWwindow *window, double posX, double posY );
        void DoMovement();
};
