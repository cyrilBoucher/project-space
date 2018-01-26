#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
using namespace std;

#include "project-space/shaders.h"

#include "project-space/Point3.h"
#include "project-space/Vec3.h"
#include "project-space/Object.h"
#include "project-space/Light.h"
#include "project-space/Camera.h"
#include "project-space/Renderer.h"
#include "project-space/Program.h"
#include "project-space/TwoPassRenderer.h"
#include "project-space/Billboard.h"
#include "project-space/CompositeObject.h"
#include "project-space/Spaceship.h"
#include "project-space/Sun.h"
#include "project-space/Skybox.h"

using namespace ps;

// width and height of the window.
int Glut_w = 600, Glut_h = 400; 

//Variables and their values for the camera setup.
Point3 camera_eye(0.0,10.0,100.0);
Vec3 camera_up(0.0,1.0,0.0);
Vec3 camera_forward (0.0,0.0,-1.0);

float fovy = 45.0f;
float zNear = 0.2f;
float zFar = 6000.0f;

int button_pressed = 0; // 1 if a button is currently being pressed.
int GLUTmouse[2] = { 0, 0 };

GLuint vertexshader, fragmentshader, shaderprogram1; // shaders
GLuint vertexshader2, fragmentshader2, shaderprogram2; // shaders

GLuint renderStyle = 0;			GLuint renderStyle_loc;
GLuint drawSilhouette = 0;		GLuint drawSilhouette_loc;
GLuint drawNormals = 0;
GLuint lightPosition_loc;
GLuint lightColor_loc;
GLuint lightDirection_loc;
GLuint lightType_loc;
GLuint projection_matrix_loc;
GLuint view_matrix_loc;
GLuint normal_matrix_loc;
GLuint buffers[6];

Object *obj1;
Spaceship *spaceship;
Plane plane;
Billboard billboard;
Sun *sun;
Skybox * skybox;
Light *lightSource;
Camera camera;
//Renderer * renderer;
TwoPassRenderer * renderer;

//This function is called when a mouse button is pressed.
void mouse(int button, int state, int x, int y)
{
  // Remember button state 
  button_pressed = (state == GLUT_DOWN) ? 1 : 0;

   // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = Glut_h - y;
}

//This function is called when the mouse is dragged.
void mousedrag(int x, int y)
{
  // Invert y coordinate
  y = Glut_h - y;

  //change in the mouse position since last time
  int dx = x - GLUTmouse[0];
  int dy = y - GLUTmouse[1];

  GLUTmouse[0] = x;
  GLUTmouse[1] = y;

  if (dx == 0 && dy == 0) return;
  if (button_pressed == 0) return;

  double vx = (double) dx / (double) Glut_w;
  double vy = (double) dy / (double) Glut_h;
  double theta = 4.0 * (fabs(vx) + fabs(vy));

  Vec3 tomovein_direction = -camera.getRight()*vx + -camera.getUp()*vy;

  Vec3 rotation_axis = tomovein_direction.crossproduct(camera.getForward());
  rotation_axis.normalize();

  camera.rotate(rotation_axis, theta);

  glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
		camera.move(0.02f,0.0f,0.0f);
	else
		camera.move(-0.02f,0.0f,0.0f);
	glutPostRedisplay();
}

//This function is called when a key is pressed.
void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:  // Escape to quit
		exit(0) ;
        break ;
	case 's':
		break;
	case 'l':
		break;
	case 'c' :
		break;
	case 'r': 
		camera_eye = Point3(0,0,2);
		camera_up = Vec3(0,1,0);
		camera_forward = Vec3(0,0,-1);
		camera.setLookAt(camera_eye, camera_eye+camera_forward, camera_up);
		break;
	case 'n':
		break;
	}
	glutPostRedisplay();
}

//This function is called when an arrow key is pressed.
void keyboard2(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP:
		camera.move(0.5f,0.0f,0.0f);
		break;
	case GLUT_KEY_DOWN:
		camera.move(-0.5f,0.0f,0.0);
		break;
	case GLUT_KEY_LEFT:
		//camera.rotate(camera.getUp(), 0.1f);
		camera.move(0.0f,-0.5f,0.0f);
		break;
	case GLUT_KEY_RIGHT:
		//camera.rotate(camera.getUp(), -0.1f);
		camera.move(0.0f,0.5f,0.0f);
		break;
	}
	glutPostRedisplay();
}

void reshape(int width, int height){
	Glut_w = width;
	Glut_h = height;
	camera.setViewport((unsigned int&)Glut_w, (unsigned int&)Glut_h);
	glm::mat4 projection_matrix = camera.getProjectionMatrix();
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, &projection_matrix[0][0]);
	glViewport(0, 0, Glut_w, Glut_h);

	TwoPassRenderer * current_renderer = dynamic_cast<TwoPassRenderer*>(renderer);

	if(current_renderer)
	{
		current_renderer->reshapeFramebuffer();
	}
}

//This function is called to display objects on screen.
void display() 
{
	sun->updatePosition(camera.getEye());

	std::vector<Object*> objects_to_render;

	objects_to_render.push_back(skybox);
	objects_to_render.push_back(sun);
	objects_to_render.push_back(spaceship);

	renderer->render(objects_to_render);
}

//This function is called from the main to initalize everything.
void init()
{
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sun = new Sun(Point3(0.0,0.0,0.0), 100.0f, 100.0f);
	sun->createObjectBuffers();

	Vec3 spaceship_direction = Vec3(0.0, -10.0, -90.0);
	spaceship_direction.normalize();

	spaceship = new Spaceship(Point3(0.0, 10.0, 90.0), 1.0, spaceship_direction);
	skybox = new Skybox(1000.0f);

	float ratio = Glut_w/(float)Glut_h;

	camera.setLookAt(camera_eye, camera_eye + camera_forward, camera_up);
	camera.setPerspective(fovy, ratio, zNear, zFar);
	camera.setViewport((unsigned int&)Glut_w, (unsigned int&)Glut_h);

	//renderer = new Renderer();
	renderer = new TwoPassRenderer();
	renderer->setCamera(&camera);
	renderer->addLight(sun->getLight());
	renderer->initPostProcessingProgram("shaders/screen.vert.glsl", "shaders/screen.frag.glsl");

	//glClearColor(0.4, 0.4, 0.4, 0);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow("My OpenGL Application");

	glewExperimental=TRUE;
	   
	glewInit() ; 
	glutReshapeWindow(Glut_w, Glut_h);
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard2);
	glutMotionFunc(mousedrag) ;
	glutMouseFunc(mouse) ;
	glutMouseWheelFunc(mouseWheel);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS) ;
	
	glEnable(GL_MULTISAMPLE);

	init();

	glutMainLoop();
	return 0;
}