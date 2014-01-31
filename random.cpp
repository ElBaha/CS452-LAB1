#include "initShaders.h"
using namespace std;

int counter = 0;
GLuint vaoID[0], vboID[0]; //create ID for VertexArrayObject, VertexBufferObject
GLfloat vertexarray[]={0.2f,-0.2f,0.0f,0.0f,0.2f,0.0f,-0.2f,-0.2f,0.0f};//create 3 vertexes, XYZ - XYZ - XYZ
GLfloat vertexarray2[]={0.5f,-0.5f,0.0f,0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
GLfloat vertexarray3[]={-0.5f, -0.5f, 0.0f,
						0.5f, -0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f,
						-0.5f, -0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						0.5f, -0.5f, 0.0f,
						-0.5f, -0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f,
						0.5f, -0.5f, 0.0f};
GLubyte indices[3]={0,1,2};//create 3 indices to refer to vertexes

void triangle(){
	glClear(GL_COLOR_BUFFER_BIT);//Clean all residual elements from screen
	glGenVertexArrays(1, &vaoID[0]);//Returns n vertex array object names in &vaoID
	glBindVertexArray(vaoID[0]);//binds elements of vaoID to a vertex array object
	glGenBuffers(1, &vboID[0]);//returns n vertex buffer object names in &vboID
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);//bind the object to the array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates memory for the vertices
	ShaderInfo shaders[]={//create a shader specified by initshaders
		{ GL_VERTEX_SHADER, "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER, "fragmentshader.glsl"},
		{ GL_NONE, NULL}
	};
	initShaders(shaders);//actually create the shaders
	glEnableVertexAttribArray(0);//enables vertex attribute index for glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//(INDEX, #VERTICES(X,Y,Z,W), TYPE OF VERTICE, NORMALIZED OR NOT, ?, OFFSET) specify the start of the vertice array used to draw
	glDrawArrays(GL_TRIANGLES, 0, 3);//draws the array
	glFlush();//finish the process, flush prior instructions
}

 void square(){
	glClear(GL_COLOR_BUFFER_BIT);//Clean all residual elements from screen
	glGenVertexArrays(1, &vaoID[0]);//Returns n vertex array object names in &vaoID
	glBindVertexArray(vaoID[0]);//binds elements of vaoID to a vertex array object
	glGenBuffers(1, &vboID[0]);//returns n vertex buffer object names in &vboID
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);//bind the object to the array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray2), vertexarray2, GL_STATIC_DRAW);//allocates memory for the vertices
	ShaderInfo shaders[]={//create a shader specified by initshaders
		{ GL_VERTEX_SHADER, "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER, "fragmentshader.glsl"},
		{ GL_NONE, NULL}
	};
	initShaders(shaders);//actually create the shaders
	glEnableVertexAttribArray(0);//enables vertex attribute index for glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//(INDEX, #VERTICES(X,Y,Z,W), TYPE OF VERTICE, NORMALIZED OR NOT, ?, OFFSET) specify the start of the vertice array used to draw
	glDrawArrays(GL_QUADS, 0, 4);//draws the array
	glFlush();//finish the process, flush prior instructions
}

void envelope(){
	glClear(GL_COLOR_BUFFER_BIT);//Clean all residual elements from screen
	glGenVertexArrays(1, &vaoID[0]);//Returns n vertex array object names in &vaoID
	glBindVertexArray(vaoID[0]);//binds elements of vaoID to a vertex array object
	glGenBuffers(1, &vboID[0]);//returns n vertex buffer object names in &vboID
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);//bind the object to the array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray3), vertexarray3, GL_STATIC_DRAW);//allocates memory for the vertices
	ShaderInfo shaders[]={//create a shader specified by initshaders
		{ GL_VERTEX_SHADER, "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER, "fragmentshader.glsl"},
		{ GL_NONE, NULL}
	};
	initShaders(shaders);//actually create the shaders
	glEnableVertexAttribArray(0);//enables vertex attribute index for glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//(INDEX, #VERTICES(X,Y,Z,W), TYPE OF VERTICE, NORMALIZED OR NOT, ?, OFFSET) specify the start of the vertice array used to draw
	glDrawArrays(GL_LINES, 0, 12);//draws the array
	glFlush();//finish the process, flush prior instructions
}

void drawscene(){
	switch(counter%3){//?
		case 0:
			glutDisplayFunc(triangle);
			glutPostRedisplay();//set flag for opengl to redraw the display
			break;
		case 1:
			glutDisplayFunc(square);
			glutPostRedisplay();
			break;
		case 2:
			glutDisplayFunc(envelope);
			glutPostRedisplay();
	}
}

//user interaction function. Right click exits, left click cycles drawscene cases.
void mousepress(int button, int state, int x, int y){
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		exit(0);
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		counter++;
		drawscene();
	}
}

void idle(){
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutCreateWindow("Assignment 1");
	glewExperimental=GL_TRUE;//initializes glew
	if(glewInit()){
		fprintf(stderr, "Unable to Initialize GLEW");
		exit(EXIT_FAILURE);
	}
	glutInitContextVersion(4, 3);//Specify OpenGL Version
    glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//Specifies GLUT profile
    const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);//get supported version of Shading Language
	fprintf(stderr, "Opengl glsl version %s\n", version);
	version=glGetString(GL_VERSION);//get supported version of OpenGL
	fprintf(stderr, "Opengl version %s\n", version);
    glutDisplayFunc(drawscene);//displays callback draws for shapes
	glutMouseFunc(mousepress);//control callback specifies mouse controls
	glutMainLoop();//sets opengl state in a loop
	return 0;
}


