#include <QtWidgets>
#include <QtOpenGL>
#include <rabbit/chart/chart.h>

namespace rabbit 
{
	class qtchart : public QOpenGLWidget, protected QOpenGLFunctions
	{
		QOpenGLShaderProgram * shader;
		//QOpenGLBuffer * vertex_array_buffer;
		//QOpenGLBuffer * element_array_buffer;
		//QOpenGLBuffer * index_array_buffer;

		//QOpenGLVertexArrayObject * vertex_array_object;


		int posAttribute;

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

    const char* vertexShaderSource =
        "#version 330 core\n"
        "in vec2 posAttr;\n"
        //"attribute lowp vec3 colAttr;\n"
        //"varying lowp vec4 col;\n"
        //"uniform highp mat4 matrix;\n"
        "void main() {\n"
        //"   col = colAttr;\n"
        "   gl_Position = vec4(posAttr, 0, 1) ;\n"
        "}\n";


	const char* fragmentShaderSource = R"(
    #version 330 core

    out vec4 fragColor;

    void main() {
        fragColor = vec4(1.0, 0.0, 1.0, 0.0);
    }
)";

	public:
		qtchart(QWidget *parent = 0) 
		{
		}

		void initializeGL()
		{    
			connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &qtchart::cleanup);

    		initializeOpenGLFunctions();
    		glClearColor(.0f, .0f, .0f, 1.0f);
    		shader = new QOpenGLShaderProgram(this);
		
    		shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    		shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
		
    		Q_ASSERT(shader->link());
    		posAttribute = shader->attributeLocation("posAttr");
		
    		//Q_ASSERT(shader->bind());
    		glEnable(GL_DEPTH_TEST);
    		glEnable(GL_CULL_FACE);
		}

		void paintGL()
		{
			shader->bind();

		     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		     GLfloat vertices[] = { 0.0f, 0.707f, -0.5f, -0.5f, 0.5f, -0.5f };
		     shader->setAttributeArray(posAttribute,vertices, 2);
		
		     glEnableVertexAttribArray(posAttribute);
		     glDrawArrays(GL_LINE_STRIP, 0, 3);
		     glDisableVertexAttribArray(posAttribute);

		     shader->release();
		}

		void cleanup() 
		{

		}
	};
}
