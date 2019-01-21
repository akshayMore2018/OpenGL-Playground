#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#define LOG(x) std::cout<<x<<std::endl;

const int WIDTH = 640;
const int HEIGHT = 480;
const char* TITLE = "OpenGL";

unsigned int CompileShader(unsigned int type, const char* source)
{	
	std::string shaderType;
	switch(type)
	{
		case GL_VERTEX_SHADER:
			shaderType="VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			shaderType="FRAGMENT";
			break;
	}
	unsigned int id= glCreateShader(type);
	glShaderSource(id,1, &source, NULL);
	glCompileShader(id);
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(id,512,NULL,infoLog);
		std::cout<<"ERROR::SHADER::"<<shaderType<<"::COMPILATION_FAILED\n"<<infoLog<<std::endl;
	}
	else
	{
		std::cout<<"SUCCESS::SHADER::"<<shaderType<<"::COMPILATION_SUCCESS"<<std::endl;
	}
	return id;
}

void CreateProgram(const char* vertexShaderSource, const char* fragmentShaderSource, unsigned int* id)
	{
		unsigned int vs= CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fs= CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		*id = glCreateProgram();
		glAttachShader(*id,vs);
		glAttachShader(*id,fs);
		glLinkProgram(*id);
		int success;
		char infoLog[512];
		glGetProgramiv(*id, GL_LINK_STATUS, &success);

		if(!success)
		{
			glGetProgramInfoLog(*id,512,NULL,infoLog);
			std::cout<<"ERROR::SHADER::LINKING_FAILED\n"<<infoLog<<std::endl;
		}
		else
		{
			std::cout<<"SUCCESS::SHADER::LINKING_SUCCESS"<<std::endl;
		}
		glDeleteShader(vs);
	    	glDeleteShader(fs);
	}

int main()
{
	if(!glfwInit())
	{
		LOG("Failed to initialize GLFW");
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,TITLE,NULL,NULL);
	if(window==NULL)
	{
		LOG("Window creation failed");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		LOG("Failed to initialize GLEW");
		return -1;
	}

	glfwSwapInterval(1);
	glViewport(0,0,WIDTH,HEIGHT);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	const char* vertexShaderSource="#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"out vec3 vertexColor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"vertexColor = color;\n"
	"}\n";

	const char* fragmentShaderSource="#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 vertexColor;\n"
	"void main()\n"
	"{\n"
	"FragColor=vec4(vertexColor, 1.0);\n"
	"}\n";

	unsigned int program=0;
	CreateProgram(vertexShaderSource,fragmentShaderSource, &program);

	float vertices[] = {
              	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left  //0
         	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right //1
         	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top right  //2
        	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left    //3
    	}; 
    	unsigned int indices[] = {
    		0, 1, 2,
    		0, 2, 3
    	};

    	unsigned int vao = 0;
    	unsigned int vbo = 0;
    	unsigned int ibo = 0;
    	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // dont unbound ibo before vao
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &vao);
    	glDeleteBuffers(1, &vbo);
    	glDeleteBuffers(1, &ibo);
	glfwTerminate();
	return 0;
}


