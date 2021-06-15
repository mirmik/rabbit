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
//#include <rabbit/chart/chart.h>
#include <rabbit/camera.h>

#include <ralgo/linalg/vecops.h>
#include <nos/print.h>

#include <igris/tuple.h>
#include <igris/systime.h>

#include <chrono>

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

	glViewport(WIDTH*0.1, HEIGHT*0.1, WIDTH*0.8, HEIGHT*0.8);






	//rabbit::opengl_drawer drawer;

	nos::println("HERE");
	rabbit::opengl_drawer drawer;
	drawer.init_opengl_context();

	nos::println("HERE");
	float aspect = (float)WIDTH / (float)HEIGHT;
	rabbit::mat4 projection =
	    rabbit::opengl_perspective(rabbit::deg(100) / aspect, aspect, 0.1, 100);

/*	rabbit::opengl_shader_program sprg(
	    rabbit::simple_vertex_shader,
	    rabbit::simple_fragment_shader);
*/
	igris::start_local_time();
	while (!glfwWindowShouldClose(window))
	{
		nos::println("HERE");
		glfwPollEvents();
		nos::println("HERE");
		drawer.clean(0.2f, 0.3f, 0.3f, 1.0f);
		nos::println("HERE1");
		//sprg.use();
		drawer.set_vertices_stride(3);


		//glUseProgram(0);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
