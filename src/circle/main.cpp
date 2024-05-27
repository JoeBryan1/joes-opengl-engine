// Include standard headers
#include <cstdio>
#include <map>

// Include GLEW
#include "GL/glew.h"

// Include GLFW
#include "GLFW/glfw3.h"
GLFWwindow* window;

#include "common/shader.hpp"

void RenderCircle(Shader &s, float width, float height, float xpos, float ypos, float currentTime, GLuint vertexbuffer);

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

int main()
{
    // Initialize GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( WIDTH, HEIGHT, "MyWindow", nullptr, nullptr);
    if( window == nullptr ){
        fprintf( stderr, "Failed to open GLFW window\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    Shader circleShader = Shader( "/Users/joebryan/CLionProjects/opengl-learn/src/shaders/circle.vert",
                                  "/Users/joebryan/CLionProjects/opengl-learn/src/shaders/circle.frag" );

    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, 1.0f, 0.0f, // top left point
            1.0f, 1.0f, 0.0f, // top right point
            1.0f, -1.0f, 0.0f, // bottom right point
            1.0f, -1.0f, 0.0f, // bottom right point
            -1.0f, -1.0f, 0.0f, // bottom left point
            -1.0f, 1.0f, 0.0f, // top left point
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    int width, height;
    double xpos, ypos;

    do{
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 0.1 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f FPS\n", double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        glfwGetWindowSize(window, &width, &height);
        glfwGetCursorPos(window, &xpos, &ypos);

        RenderCircle(circleShader, (float) width, (float) height, (float) xpos,
                     (float) ypos, (float) currentTime, vertexbuffer);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(circleShader.ID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

void RenderCircle(Shader &s, float width, float height, float xpos, float ypos, float currentTime, GLuint vertexbuffer) {
    s.use();
    s.setVec2("u_resolution", width, height);
    s.setVec2("u_mouse", xpos, ypos);
    s.setFloat("u_time", currentTime);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)nullptr         // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
}