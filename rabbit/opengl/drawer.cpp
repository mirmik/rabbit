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

	opengl_onecolored_texture.open(
	    rabbit::onecolored_texture_vertex_shader,
	    rabbit::onecolored_texture_fragment_shader
	);

	opengl_rgb_texture.open(
	    rabbit::rgb_texture_vertex_shader,
	    rabbit::rgb_texture_fragment_shader
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

void rabbit::opengl_drawer::draw_triangles(
    float * vertices,
    int vertices_total,
    GLuint * triangles,
    int triangles_total)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_stride * vertices_total * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices_stride * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint) * triangles_total, triangles,
	             GL_DYNAMIC_DRAW);

	glDrawElements(GL_TRIANGLES, 3 * sizeof(GLuint)*triangles_total, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);

}

void rabbit::opengl_drawer::draw_triangles(
    const std::vector<vec3> & vertices,
    const std::vector<ivec3> & triangles)
{
	draw_triangles(
	    (float*)vertices.data(),
	    vertices.size(),
	    (GLuint*)triangles.data(),
	    triangles.size());
}


void rabbit::opengl_drawer::draw_lines(
    float * vertices,
    int vertices_total, GLint style)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_stride * vertices_total * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, vertices_stride, GL_FLOAT, GL_FALSE, vertices_stride * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(style, 0, vertices_total);

	glBindVertexArray(0);

}

void rabbit::opengl_drawer::draw_lines(
    const std::vector<vec3> & vertices, GLint style)
{
	draw_lines(
	    (float*)vertices.data(),
	    vertices.size(),
	    style);
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

	uniform_mat4f("model", opengl_mesh_program.Program, model);
	uniform_mat4f("view", opengl_mesh_program.Program, view);
	uniform_mat4f("projection", opengl_mesh_program.Program, projection);

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
	glEnableVertexAttribArray(VAO);

	GLint vertexColorLocation = glGetUniformLocation(opengl_mesh_program.Program, "vertexColor");
	opengl_mesh_program.use();

	uniform_mat4f("model", opengl_mesh_program.Program, model);
	uniform_mat4f("view", opengl_mesh_program.Program, view);
	uniform_mat4f("projection", opengl_mesh_program.Program, projection);

	glBindVertexArray(VAO);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glDrawArrays(GL_POINTS, 0, count);

	glBindVertexArray(0);
	glUseProgram(0);
}



void rabbit::opengl_drawer::uniform_mat4f(
    const char * locname, int program, const linalg::mat<float, 4, 4> & matrix)
{
	GLint modelLoc = glGetUniformLocation(program, locname);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*) &matrix);
}

void rabbit::opengl_drawer::uniform_mat4f(
    const char * locname, int program, const GLfloat* data)
{
	GLint modelLoc = glGetUniformLocation(program, locname);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, data);
}


void rabbit::opengl_drawer::uniform_mat4f(
    unsigned int location, const linalg::mat<float, 4, 4> & matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*) &matrix);
}

void rabbit::opengl_drawer::uniform_mat4f(
    unsigned int location, const GLfloat* data)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void rabbit::opengl_drawer::draw_onecolored_texture_2d(
    const std::vector<std::pair<linalg::vec<float, 3>, linalg::vec<float, 2>>> & vertices,
    const std::vector<ivec3> triangles,
    const rabbit::opengl_texture & texture,
    const linalg::vec<float, 3> & color,
    const linalg::mat<float, 4, 4> & transform
)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
	             vertices.size() * sizeof(float) * 5, vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             triangles.size()*sizeof(int) * 3, triangles.data(), GL_DYNAMIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	opengl_onecolored_texture.use();
	opengl_onecolored_texture.uniform_mat4f("transform", transform);
	texture.activate(opengl_onecolored_texture.id(), "ourTexture", 0);
	opengl_onecolored_texture.uniform_vec3f("textColor", color);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glUseProgram(0);
}


void rabbit::opengl_drawer::draw_rgb_texture_2d(
    const std::vector<std::pair<linalg::vec<float, 3>, linalg::vec<float, 2>>> & vertices,
    const std::vector<ivec3> triangles,
    const rabbit::opengl_texture & texture,
    const linalg::mat<float, 4, 4> & transform
)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
	             vertices.size() * sizeof(float) * 5, vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             triangles.size()*sizeof(int) * 3, triangles.data(), GL_DYNAMIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	opengl_rgb_texture.use();
	opengl_rgb_texture.uniform_mat4f("transform22", transform);
	texture.activate(opengl_rgb_texture.id(), "ourTexture", 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, triangles.size()*sizeof(int) * 3, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glUseProgram(0);
}

void rabbit::opengl_drawer::print_text(
	const rabbit::font & font,
	rabbit::textzone_cursor & cursor,
	const std::string_view & view,
	const linalg::vec<float,3> & color,
	const linalg::mat<float,4,4> & matrix) 
{
	for (unsigned int i = 0; i < view.size(); ++i) 
	{
		char c = view[i];
		auto & texture = font[c];
		auto cell = cursor.get(); 

        draw_onecolored_texture_2d(
        {
            {cell.ll, {0, 0}},
            {cell.lh, {0, 1}},
            {cell.hl, {1, 0}},
            {cell.hh, {1, 1}},
        },
        {{0, 1, 2}, {1, 3, 2}},
        texture, color, matrix);

        cursor.increment();
	}
}