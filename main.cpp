#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

Game game;


void reshape(int width,int height);
void render();
void keyboard(unsigned char key,int x,int y);
void idle();


int main(int argc, char** argv){

int res_x,res_y,pos_x,pos_y;
glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

//create centered window
res_x=glutGet (GLUT_SCREEN_WIDTH);
res_y= glutGet (GLUT_SCREEN_HEIGHT);
pos_x=(res_x/2)-(WINDOW_WIDTH/2);
pos_y=(res_y/2)-(WINDOW_HEIGHT/2);

glutInitWindowPosition (pos_x,pos_y);
glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
glutCreateWindow("My First OpenGl program");


glutReshapeFunc(reshape);
glutDisplayFunc(render);
glutKeyboardFunc(keyboard);
//Set the function for the animation.
glutIdleFunc(idle);

GLint GlewInitResult = glewInit();
if(GLEW_OK != GlewInitResult)
{
	exit(EXIT_FAILURE);
}

game.init();
glutMainLoop();
return 0;
}

void reshape(int width, int height)
{
  game.reshape(width,height);
}

void render()
{
	game.render();
}


void keyboard(unsigned char key,int x,int y)
{
	game.readKeyboard(key,x,y,false);
}


void idle()
{
	if(!game.loop())exit(0);
}