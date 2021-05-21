#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/opengl/projection.h>
#include <rabbit/opengl/mesh_drawer.h>
#include <rabbit/mesh.h>
#include <rabbit/util.h>
#include <rabbit/space/pose3.h>

#include <rabbit/space/htrans.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <rabbit/opengl/util.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);

    rabbit::opengl_shader_program opengl_mesh_program(
        "../../rabbit/opengl/mesh_shader.vs",
        "../../rabbit/opengl/mesh_shader.frag"
    );

    GLuint VBO, VAO, EBO;
    
    //auto surf = rabbit::parabolic_surface(1,1, rabbit::mov3({0,0,-5}));
    //auto mesh = rabbit::surface_rubic_mesh(surf, -2, 2, 20, -2, 2, 20);
    auto surf = rabbit::sphere_surface(2);
    auto mesh = rabbit::surface_rubic_mesh(surf, 20, 20);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glLineWidth(2);

    rabbit::mat4 model = rabbit::rot3({0, 1, 0}, rabbit::deg(45)).to_mat4();
    rabbit::mat4 view = rabbit::mov3({0,0,-10}).to_mat4();
    
    //rabbit::mat4 projection = rabbit::opengl_ortho(-10, 10, -10,10, -10000, 10000);
    rabbit::mat4 projection = rabbit::opengl_perspective(rabbit::deg(90), 1, 0.01, 100);
    
    while (!glfwWindowShouldClose(window))
    {
        model = rabbit::rot3({0, 1, 0}, rabbit::deg(glfwGetTime() * 16)).to_mat4();

        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     mesh.vertices.size()*sizeof(float) * 3, mesh.vertices.data(), GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh.triangles.size()*sizeof(int) * 3, mesh.triangles.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        GLint vertexColorLocation = glGetUniformLocation(opengl_mesh_program.Program, "vertexColor");
        opengl_mesh_program.use();

        opengl_mesh_program.uniform_mat4f("model", model);
        opengl_mesh_program.uniform_mat4f("view", view);
        opengl_mesh_program.uniform_mat4f("projection", projection);

        glBindVertexArray(VAO);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1, 1);
        glUniform4f(vertexColorLocation, 0.3f, 0.4f, 0.6f, 1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonOffset(0, 0);
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
