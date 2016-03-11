#include "bola.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace arkanoid;

extern bool hitbox;
extern bool perspective;

bola::bola(float x, float y, float z){
	raio = 1;
	int a = 0;
	this->status = true;
	this->init = false;
	srand(time(NULL));
	a = rand() % 40 + 80;
	float b = a * ( PI / 180 ) + 10;
	printf("a = %d\n", a);
	if (a < 90){
		dirx =  abs(sin(b));
		diry =  abs(cos(b));
		printf("sen = %f e cos = %f\n", dirx, diry);
	}
	else {
		dirx = sin(-b);
		diry = cos(-b);
		printf("sen = %f e cos = %f\n", dirx, diry);
	}
	_color[0] = 0.5;
	_color[1] = 0.5;
	_color[2] = 0.5;
	_color[3] = 0.1;
	px = x;
	py = y;
	pz = z;
	desenha(px, py, pz);
}

bola::~bola(){
	this->status = false;
}





void bola::desenha(float x, float y, float z){
	if (perspective){
		GLfloat scolor[] = { 0.5, 0.5, 0.5, 0.1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, scolor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	}
	glPushMatrix();
		glPushMatrix();
			glTranslatef(x, y,z);
			glColor4fv(_color);
			glutSolidSphere(0.5, 20, 100);
		glPopMatrix();
		if (hitbox){
			glPushMatrix();
				glColor4fv(_color);
				glTranslatef(x, y, z);
				glutWireSphere(raio + 0.01, 20, 20);
			glPopMatrix();
		}
	glPopMatrix();
}

void bola::actualiza(){
	this->desenha(this->getX(), this->getY(), this->getZ());
}

bool bola::bolaEsquerda(){
	if (this->init == false)
		if (px + (-MOV) < LIMITE_MIN)
			return false;
		else{
			this->px = px - MOV;
			return true;
		}	
}

void bola::inverte(){
	this->diry = -(this->diry);
}

void bola::inverteX(){
	this->dirx = -(this->dirx);
}

bool bola::bolaMove() {
	float pos = py + diry*MOV;
	float pox = px + dirx*MOV;
	if (this->init == true){
		if (((LIM_MAX_Y > pos) && (pos > LIM_MIN_Y))){
			this->py = py + diry*MOV;
			if (((LIM_MAX_Y > pox) && (pox > LIM_MIN_J))){
				printf("x = %f, y = %f\n", px, py);
				this->px = px + dirx*MOV;
				return true;
			}
			else{
				dirx = dirx * -1;
				this->px = px + dirx*MOV;
				return true;
			}
		}
		else{
			diry = diry*-1;
			this->py = py + diry*MOV;
			return true;
		}			
	}
}


float bola::getDir(){
	return diry;
}

bool bola::bolaDireita(){
	if (this->init == false)
		if ((px + MOV) > LIMITE_MAX)
			return false;
		else{
			this->px = px + MOV;
			return true;
		}
}

float bola::getRaio(){
	return this->raio;
}

bool bola::getInit(){
	return this->status;
}

void bola::setInit(){
	init = true;
}

float * bola::getPosicao(){
	float * toreturn = (float*)malloc(3 * sizeof(float));
	toreturn[0] = px;
	toreturn[1] = py;
	toreturn[2] = pz;
	return toreturn;
}

float bola::getX(){
	return px;
}

float bola::getY(){
	return py;
}

float bola::getZ(){
	return pz;
}



