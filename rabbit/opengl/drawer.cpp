#include <rabbit/opengl/drawer.h>
#include <rabbit/opengl/shader_collection.h>

rabbit::opengl_drawer::opengl_drawer() {}

void rabbit::opengl_drawer::init_opengl_context()
{
	opengl_mesh_program.open(
	    rabbit::mesh_vertex_shader,
	    rabbit::mesh_fragment_shader
	);

	opengl_simple_program.open(
	    rabbit::simple_vertex_shader,
	    rabbit::simple_fragment_shader
	);


	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glLineWidth(2);
}

void rabbit::opengl_drawer::create_buffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void rabbit::opengl_drawer::draw_simple_triangles(
    float * vertices,
    int vertices_total,
    GLuint * triangles,
    int triangles_total)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float)*vertices_total, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(float)*triangles_total, triangles, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	opengl_simple_program.use();
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}

void rabbit::opengl_drawer::draw_simple_triangles(
    const std::vector<vec3> & vertices,
    const std::vector<ivec3> & triangles)
{
	draw_simple_triangles(
	    (float*)vertices.data(),
	    vertices.size(),
	    (GLuint*)triangles.data(),
	    triangles.size());
}




void rabbit::opengl_drawer::destroy_opengl_context()
{


}

void rabbit::opengl_drawer::clean(real r, real g, real b, real a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void rabbit::opengl_drawer::draw_mesh(
    const rabbit::mesh & mesh,
    const mat4 & model,
    const mat4 & view,
    const mat4 & projection)
{
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonOffset(0, 0);
	//glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
	//glDrawElements(GL_TRIANGLES, mesh.triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void rabbit::opengl_drawer::draw_points(
    const vec3 * pnts,
    int count,
    const mat4 & model,
    const mat4 & view,
    const mat4 & projection)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
	             count * sizeof(float) * 3, pnts, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	GLint vertexColorLocation = glGetUniformLocation(opengl_mesh_program.Program, "vertexColor");
	opengl_mesh_program.use();

	opengl_mesh_program.uniform_mat4f("model", model);
	opengl_mesh_program.uniform_mat4f("view", view);
	opengl_mesh_program.uniform_mat4f("projection", projection);

	glBindVertexArray(VAO);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glDrawArrays(GL_POINTS, 0, count);

	glBindVertexArray(0);
	glUseProgram(0);
}
