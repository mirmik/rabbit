#include <QtWidgets>
#include <QtOpenGL>
#include <rabbit/chart/chart.h>

namespace rabbit 
{
	class qtchart : public QOpenGLWidget
	{
		QGLShaderProgram * shader_program;
		QOpenGLBuffer * vertex_array_buffer;
		QOpenGLBuffer * element_array_buffer;
		QOpenGLBuffer * index_array_buffer;

		const char * chart_vertex_shader  = R"""(#version 300 es
layout (location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
}
)""";

		const char * chart_fragment_shader = R"""(#version 300 es

uniform lowp vec3 Color;
out lowp vec4 color;

void main()
{
    color = vec4(Color, 1.0f);
} 
)""";		

	public:
		qtchart(QWidget *parent = 0) 
		{
		}

		void initializeGL()
		{
			auto ctx = context();
			shader_program = new QGLShaderProgram(ctx);
			shader_program->addShaderFromSourceCode(QGLShader::Vertex, chart_vertex_shader);
			shader_program->addShaderFromSourceCode(QGLShader::Fragment, chart_fragment_shader);
			
			vertex_array_buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
			vertex_array_buffer->create();

    		// Enable depth buffer
   			glEnable(GL_DEPTH_TEST);

    		// Enable back face culling
    		glEnable(GL_CULL_FACE);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		void paintGL() override
		{
			std::vector<float> vertices = {
				 1.0f, 0.0f ,
				 -1.0f, 1.0f,
				 0.0f, 1.0f,
			};

/*index_array_buffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
index_array_buffer->create();
index_array_buffer->bind();
index_array_buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
index_array_buffer->allocate(m_indices, 6 * sizeof(GLint));*/


			nos::println("painting");
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			shader_program->bind();
			vertex_array_buffer->bind();
			vertex_array_buffer->allocate(vertices.data(), 6 * sizeof(GLfloat));
			vertex_array_buffer->setUsagePattern(QOpenGLBuffer::StreamDraw);
			glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
			shader_program->setUniformValue("Color", QColor(Qt::red).rgba());

			draw_line();
			glDrawArrays(GL_TRIANGLES, 0, 6);

			auto err = glGetError();
			nos::println(err, "error");

			shader_program->release();
		}

		void draw_line()
		{
		}

		void set_line_color(float r, float g, float b)
		{
			glColor3f(r, g, b);
		}

		void shader_program_init()
		{	
		}
	};
}
