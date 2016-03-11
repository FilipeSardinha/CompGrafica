#include <stdlib.h>
#include <GL/glut.h>
#include "nave.h"
#include "gestorJogo.h"
#include <time.h>
#include <math.h>



using namespace arkanoid;

extern int h = 600;
extern int w = 600;
int ratio = w / h;
extern float aspect = 1;
extern bool perspective = true;
bool hitbox = false;
bool luzspot ;
bool luzbola ;
int t = 0;
int fundo = 4;
bool help = false;
int dificuldade = 2;



bool useLights = true;

gestorJogo * novoJogo = new gestorJogo(3);
bool teclado[256] = { false };

void setLuz();
void lightBallOn();
void setLuzes();
void setCameraAndLight(int i, int l);

bool getHit(){
	return hitbox;
}

void KeyboardFunc(unsigned char c, int x, int y){
	teclado[c] = true;
}




void KeyboardHandler(){
	if ((teclado['a']) || (teclado['A'])){
		novoJogo->moveEsquerda();
		teclado['a'] = false;
		teclado['A'] = false;
	}
	if ((teclado['d']) || (teclado['D'])){
		novoJogo->moveDireita();
		teclado['d'] = false;
		teclado['D'] = false;
	}
	if ((teclado['f']) || (teclado['F'])){
		novoJogo->moveBola();
		novoJogo->fire();
		teclado['f'] = false;
		teclado['F'] = false;
	}
	if (teclado['1']){
		novoJogo->_camera = 0;
		teclado['1'] = false;
	}
	if (teclado['2']){
		novoJogo->_camera = 1;
		teclado['2'] = false;
	}
	if (teclado['3']){
		novoJogo->_camera = 2;
		teclado['3'] = false;
	}
	if (teclado['4']){
		novoJogo->_camera = 3;
		teclado['4'] = false;
	}
	if (teclado['5']){
		novoJogo->_camera = 4;
		teclado['5'] = false;
	}
	if (teclado['6']){
		novoJogo->_camera = 5;
		teclado['6'] = false;
	}
	if (teclado['c']){
		hitbox = !hitbox;
		teclado['c'] = false;
	}
	if (teclado['e']){
		exit(0);
	}
	if (teclado['z']){
		if (fundo < 5)
			fundo += 1;
		else fundo = 1;
		teclado['z'] = false;
	}
	if (teclado['h']){
		help = !help;
		teclado['h'] = false;
	}
	if (teclado['x']){
		if (dificuldade < 3)
			dificuldade += 1;
		else dificuldade = 1;
		teclado['x'] = false;
	}

	if (teclado['l']){
		useLights = !useLights;
		teclado['l'] = false;
	}
	if (teclado['n']){
		luzbola = !luzbola;
		useLights = true;
		teclado['n'] = false;
	}
	if (teclado['m']){
		luzspot = !luzspot;
		useLights = true;
		teclado['m'] = false;
	}
	if (teclado['i']){
		if (teclado['k']){
			if (teclado['u']){
				if (teclado['p']){
					novoJogo->INSTA();
					teclado['p'] = false;
				}
				teclado['u'] = false;
			}
			teclado['k'] = false;
		}
		teclado['i'] = false;
	}


	if (novoJogo != NULL && !novoJogo->decorrer()){
		if (teclado['r'] || teclado['R']){
			novoJogo = new gestorJogo(3);
			teclado['r'] = false;
			teclado['R'] = false;
		}
	}
	
}



void DisplayFunc(void){
	printf("luz bola = %d luz spot = %d\n", luzbola, luzspot);
	KeyboardHandler();
	novoJogo->iniciaChao();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (novoJogo != NULL){
			novoJogo->desenha();
			setCameraAndLight(novoJogo->_camera, novoJogo->_light);
			if (luzbola){
				glEnable(GL_LIGHT0);
				lightBallOn();
			}
			else{
				glDisable(GL_LIGHT0);
			}
			if (luzspot){
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT3);
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT4);
				setLuz();
			}
			else{
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHT4);
				glDisable(GL_LIGHT2);
			}
			//novoJogo->iniciaChao();
				novoJogo->actualizaJogador();
			
			//novoJogo->HUD();
		
	}
	glutSwapBuffers();
	//glFlush();
}

void ReshapeFunc(GLsizei gamewidth, GLsizei gameheight){
	aspect = (float)gamewidth / (float)gameheight;
	w = gamewidth;
	h = gameheight;
}

void redesenha(int value){
	glutPostRedisplay();
	glutTimerFunc(15, redesenha, 1);

}

void bolas(int v){
	novoJogo->moveBola();
		if (dificuldade == 1)
			glutTimerFunc(15, bolas, 1);
		else if (dificuldade == 2)
			glutTimerFunc(25, bolas, 1);
		else if (dificuldade == 3)
			glutTimerFunc(35, bolas, 1);
	
}


void main(int argc, char** argv) {
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow("Arkanoid");
	glutKeyboardFunc(KeyboardFunc);
	glutReshapeFunc(ReshapeFunc);
	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(20, bolas, 0);
	glutTimerFunc(20, redesenha, 0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glutMainLoop();
}

void setCameraAndLight(int i, int l)
{
	if (!useLights)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT2);
	}
	else
	{
		glEnable(GL_LIGHTING);
		

		switch (l)
		{
		case 1:
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			break;
		}
	}
	switch (i)
	{
	case 0:
		novoJogo->mode2d = true;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (ratio > 1)
			glOrtho(-20.0f*ratio, 20.0f*ratio, -20.0f, 20.0f, -20.0f, 20.0f);
		else
			glOrtho(-20.0f, 20.0f, -20.0f / ratio, 20.0f / ratio, -20.0f, 20.0f);

		break;
	case 1:
		novoJogo->mode2d = false;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(80, 1.0f, 0.1f, 100.0f);
		gluLookAt(novoJogo->_jogador->getX(), novoJogo->_jogador->getY() - 20, 5,
			novoJogo->_jogador->getX(), 20, 0, 0, 0, 1);
		break;
	case 2:
		novoJogo->mode2d = false;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(60, ratio, 0.1, 100);
		gluLookAt(novoJogo->_jogador->getX(), novoJogo->_jogador->getY() - 5, 3,
			novoJogo->_jogador->getX(), novoJogo->_jogador->getY(), 0, 0, 0, 1);
		break;
	case 3:
		novoJogo->mode2d = false;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(60, ratio, 0.1, 100);
		gluLookAt(novoJogo->_jogador->getX(), novoJogo->_jogador->getY() - 0.25,1,
			novoJogo->getBola()->getX(), novoJogo->getBola()->getY() + 2.5, 0,
			0, 0, 1);
		break;
	case 4:
		novoJogo->mode2d = false;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(60, ratio, 0.1, 100);
		gluLookAt(15, 15, 31, 15, 15, 0, 0, 1, 0);
		break;
	case 5:
		novoJogo->mode2d = false;
		gluPerspective(60, ratio, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(novoJogo->_jogador->getX(), novoJogo->_jogador->getY() - 2, 2,
			novoJogo->_jogador->getX(), novoJogo->_jogador->getY(), 1,
			0, 1, 0);
		break;
	}
}

void lightBallOn(){
	if (novoJogo->getBolaDir() < 0){
		GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 0.5 };
		GLfloat light_difuse[] = { 0.2, 0.2, 0.2, 0 };
		GLfloat light_specular[] = { 0.2, 0.2, 0.2, 0 };
		GLfloat lightpos[] = { novoJogo->getBola()->getX(), novoJogo->getBola()->getY(), novoJogo->getBola()->getZ(), 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.5);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.5);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	}
	else glDisable(GL_LIGHT0);
}

void setLuz()
{
	GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_difuse[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat	light_position[] = {20, -20, 1, 1 };
	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat spot_direction[] = { 0, 1 , 0 };
	GLfloat spot_direction2[] = { 0, -1, 0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);


	GLfloat	light_position2[] = { -19, 19, 1, 1 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);



	GLfloat	light_position3[] = { 19, 19, 1, 1 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction2);



	GLfloat	light_position4[] = { -20, -20, 1, 1 };
	

	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);

	novoJogo->actualizaChao();


	
}