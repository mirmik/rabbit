// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/opengl/projection.h>
#include <rabbit/opengl/drawer.h>
#include <rabbit/opengl/shader_collection.h>
#include <rabbit/mesh.h>
#include <rabbit/util.h>
#include <rabbit/space/pose3.h>

#include <nos/print.h>
#include <rabbit/space/htrans.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <rabbit/opengl/util.h>
#include <rabbit/opengl/drawer.h>
#include <rabbit/font/naive.h>
#include <rabbit/camera.h>
#include <rabbit/font/font.h>

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


    glEnable(GL_BLEND);




    rabbit::opengl_drawer drawer;

    nos::println("HERE");
    drawer.init_opengl_context();
    nos::println("HERE2");

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

    /*GLfloat vertices[] =
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
    };*/

//    rabbit::opengl_drawer drawer;

    //rabbit::opengl_texture texture = rabbit::naive_font16x26_texture('B');
    rabbit::font font(rabbit::naive_font16x26_texture);
    rabbit::opengl_texture & texture = font['Y'];
    //texture.create(16, 16, GL_RED, GL_RED, GL_UNSIGNED_BYTE);
    //texture.set_finish_flag_texture(16, 16);
    texture.bind();

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

        float lo = 0.7;
        float hi = 0.9;

        drawer.draw_onecolored_texture_2d(
        {
            {{lo, lo, 0.99999}, {0, 0}},
            {{lo, hi, 0.99999}, {0, 1}},
            {{hi, lo, 0.99999}, {1, 0}},
            {{hi, hi, 0.99999}, {1, 1}},
        },
        {{0, 1, 2}, {1, 3, 2}},
        texture, {0, 1, 0});



        drawer.opengl_mesh_program.use();

        drawer.draw_mesh(
            mesh,
            (rabbit::rot3(rabbit::vec3{0.3, 0.7, 0}, rabbit::deg(20)) * model).to_mat4(),
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
            (rabbit::rot3(rabbit::vec3{0.6, 0.2, 0}, rabbit::deg(20)) * model.inverse()).to_mat4(),
            camera.view_matrix(),
            projection
        );

        drawer.draw_mesh(
            mesh5,
            (rabbit::mov3({5.5f * sinf(glfwGetTime()), 5.5f * cosf(glfwGetTime()), 0}) * model).to_mat4(),
            camera.view_matrix(),
            projection
        );

        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
