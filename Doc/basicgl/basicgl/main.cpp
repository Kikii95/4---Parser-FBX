#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "Shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(800, 600, "Basicgl", NULL, NULL);

    if (win == NULL)
    {
        const char* description;
        int code = glfwGetError(&description);
        std::cout << "Failed to create GLFW window: " << description << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, FrameBufferSizeCallback);

    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    mngl::Shader shader("shader/vertex.glsl", "shader/fragment.glsl");
    shader.SetMatrix4("_projection", glm::perspective(glm::radians(75.f), 800.f/600.f, 0.1f, 100.f));
    shader.SetMatrix4("_view", glm::translate(glm::mat4(1.f), {0, 0, -3.f}));
    shader.SetMatrix4("_model", glm::translate(glm::mat4(1.f), {0,0, 0}));
    shader.SetColor("_mainColor", mngl::Color::Red);
    shader.SetColor("_lightColor", mngl::Color::White);
    shader.SetFloat("_ambientStrength", 0.1f);
    shader.SetVector3("_lightPos", {0,0,3.f});

    glm::vec3 p1 = {-0.5f, -0.5f, 0.0f};
    glm::vec3 p2 = {0.5f, -0.5f, 0.0f};
    glm::vec3 p3 = {0.0f, 0.5f, 0.0f};

    glm::vec3 v = p2 - p1;
    glm::vec3 u = p3 - p1;

    glm::vec3 normal = glm::cross(v, u);

    float allVertice[] = {
        p1.x, p1.y, p1.z,
        p2.x, p2.y, p2.z,
        p3.x, p3.y, p3.z,
        normal.x, normal.y, normal.z,
        normal.x, normal.y, normal.z,
        normal.x, normal.y, normal.z
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allVertice), allVertice, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(win)) {

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        shader.Shutdown();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
