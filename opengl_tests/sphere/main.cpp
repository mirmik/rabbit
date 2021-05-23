#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/opengl/projection.h>
#include <rabbit/opengl/drawer.h>
#include <rabbit/opengl/shader_collection.h>
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
#include <rabbit/opengl/drawer.h>
#include <rabbit/camera.h>

// Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 800;

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




    

    rabbit::opengl_drawer drawer;

    drawer.init_opengl_context();

    auto surf = rabbit::torus_surface(4, 0.2);
    auto surf2 = rabbit::sphere_surface(2);
    auto surf3 = rabbit::torus_surface(7, 0.2);
    auto surf4 = rabbit::torus_surface(8, 0.2);
    auto surf5 = rabbit::sphere_surface(0.6);

    auto mesh = rabbit::surface_rubic_mesh(surf, 30, 20);
    auto mesh2 = rabbit::surface_rubic_mesh(surf2, 30, 20);
    auto mesh3 = rabbit::surface_rubic_mesh(surf3, 30, 20);
    auto mesh4 = rabbit::surface_rubic_mesh(surf4, 30, 20);
    auto mesh5 = rabbit::surface_rubic_mesh(surf5, 30, 20);

    float aspect = (float)WIDTH / (float)HEIGHT;
    rabbit::mat4 projection =
        rabbit::opengl_perspective(rabbit::deg(100) / aspect, aspect, 0.1, 100);

    rabbit::camera camera;

    GLfloat vertices[] =
    {
        0.5f,  0.5f, 0.999999f,  // Top Right
        0.5f, -0.5f, 0.999999f,  // Bottom Right
        -0.5f, -0.5f, 0.999999f,  // Bottom Left
        -0.5f,  0.5f, 0.999999f   // Top Left
    };
    GLuint indices[] =    // Note that we start from 0!
    {
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };

    rabbit::opengl_shader_program sprg(
        rabbit::simple_vertex_shader,
        rabbit::simple_fragment_shader);

    while (!glfwWindowShouldClose(window))
    {
        auto model = rabbit::rot3({0, 0, 1}, rabbit::deg(glfwGetTime() * 16));

        camera.set_eye({10, 0, 3});
        camera.set_target({0, 0, 0});

        glfwPollEvents();

        drawer.clean(0.2f, 0.3f, 0.3f, 1.0f);

        sprg.use();

        drawer.set_vertices_stride(3);
        drawer.draw_triangles(vertices, 4, indices, 2);


        //drawer.draw_simple_triangles(vertices, 4, indices, 2);
        
        glUseProgram(0);
        /*drawer.draw_mesh(_mesh,
            rabbit::pose3().to_mat4(),
            rabbit::pose3().to_mat4(),
            rabbit::pose3().to_mat4()
        );*/

        drawer.opengl_mesh_program.use();

        drawer.draw_mesh(
            mesh,
            (rabbit::rot3(rabbit::vec3{0.3,0.7,0}, rabbit::deg(20)) * model).to_mat4(),
            camera.view_matrix(),
            projection);

        drawer.draw_mesh(
            mesh2,
            model.inverse().to_mat4(),
            camera.view_matrix(),
            projection
        );

        drawer.draw_mesh(
            mesh3,
            model.to_mat4(),
            camera.view_matrix(),
            projection
        );

        drawer.draw_mesh(
            mesh4,
            (rabbit::rot3(rabbit::vec3{0.6,0.2,0}, rabbit::deg(20)) * model.inverse()).to_mat4(),
            camera.view_matrix(),
            projection
        );

        drawer.draw_mesh(
            mesh5,
            (rabbit::mov3({5.5*sin(glfwGetTime()), 5.5*cos(glfwGetTime()), 0}) * model).to_mat4(),
            camera.view_matrix(),
            projection
        );

        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
