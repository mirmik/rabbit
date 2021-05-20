#include <rabbit/opengl/opengl_shader_program.h>
#include <rabbit/opengl/mesh_drawer.h>
#include <rabbit/mesh.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    rabbit::opengl_shader_program opengl_mesh_program(
        "../../rabbit/opengl/mesh_shader.vs",
        "../../rabbit/opengl/mesh_shader.frag"
    );

    GLuint VBO, VAO, EBO;
    auto mesh = rabbit::sphere_rubic_mesh(10, 10, 0.5);

//    exit(0);

    for (int i = 0; i < mesh.vertices.size(); ++i) 
        nos::println(mesh.vertices[i]);
/*
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //             mesh.triangles.size() * sizeof(float), mesh.triangles.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);*/


    // Set up vertex data (and buffer(s)) and attribute pointers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
        mesh.vertices.size()*sizeof(float)*3, mesh.vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mesh.triangles.size()*sizeof(float)*3, mesh.triangles.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    PRINT(mesh.vertices.size());
    for (int i =0 ; i< mesh.triangles.size(); ++i) 
        nos::println(mesh.triangles[i]);


    glLineWidth(2);
    

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLint vertexColorLocation = glGetUniformLocation(opengl_mesh_program.Program, "vertexColor");
        opengl_mesh_program.use();

        // Draw our first triangle
        glBindVertexArray(VAO);

        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
        glUniform4f(vertexColorLocation, 0.3f, 0.4f, 0.6f, 1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(float)*3, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size()*sizeof(float)*3);

        //glDisable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonOffset(0,0);
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(float)*3, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose

    glfwTerminate();
    return 0;
}
