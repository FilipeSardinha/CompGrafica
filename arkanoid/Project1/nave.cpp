#include "nave.h"
#include <stdio.h>

using namespace arkanoid;

extern bool hitbox;
extern bool perspective;

nave::nave(float x, float y, float z){
	raio = 2;
	px = x;
	py = y;
	pz = z;
	_color[0] = 1.0;
	_color[1] = 0.0;
	_color[2] = 0.0;
	_color[3] = 0.0;
	_color1[0] = 1.0;
	_color1[1] = 1.0;
	_color1[2] = 1.0;
	_color1[3] = 0.0;
	desenha(px, py, pz);
}

nave::~nave(){
	
}

void nave::desenha(float x, float y, float z){
	if (perspective){
		GLfloat scolor[] = { 1, 0, 0, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, scolor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 29);
	}
	glPushMatrix();
	
		glPushMatrix();
			glColor4fv(_color);
			glTranslatef(px-1, py, pz);
			drawCil2(8, 1);
		glPopMatrix();
		glPushMatrix();
			glColor4fv(_color);
			glTranslatef(px+1, py, pz);
			drawCil1(8, 1);
		glPopMatrix();
		glPushMatrix();
			glColor4fv(_color);
			glTranslatef(px-1.5, py, pz);
			drawCil1(8, 1);
		glPopMatrix();
		glPushMatrix();
		if (hitbox){
			glPushMatrix();
				glTranslatef(x, y, z);
				glColor4fv(_color);
				glutWireSphere(raio + 0.001, 20, 20);
			glPopMatrix();
			
		}
	glPopMatrix();
}

void nave::actualiza(){
	this->getX();
	this->getY();
	this->getZ();
	this->desenha(px, py, pz);
}

bool nave::naveEsquerda(){
	if (px + (-0.5) < -17.5)
		return false;
	else{
		this->px = px - 0.5;
		return true;
	}
}

bool nave::naveDireita(){
	if ((px + 0.5)>  17.5)
		return false;
	else{
		this->px = px + 0.5;
		return true;
	}
}




float nave::getX(){
	return this->px;
}

float nave::getY(){
	return this->py;
}

float nave::getZ(){
	return this->pz;
}

float * nave::getPosicao(){
	float * toreturn = (float*)malloc(3 * sizeof(float));
	toreturn[0] = px;
	toreturn[1] = py;
	toreturn[2] = pz;
	return toreturn;
}

float nave::getRaio(){
	return this->raio;
}

void nave::drawCil2(float n, float z)
{
	float DOISPI = 2.0f * 3.14159f;
	float angle = 360.0f / n;

	glScaled(2, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += (360 / n))
	{
		float a = i * 3.14159f / 180;
		glNormal3f(cos(a), sin(a), z);
		glVertex3f(cos(a), sin(a), z);
	}

	for (int i = 0; i < 480; i += (360 / n))
	{
		float a = i * 3.14159f / 180;
		glNormal3f(cos(a), sin(a), 0.0f);
		glVertex3f(cos(a), sin(a), 0.0);
		glNormal3f(cos(a), sin(a), z);
		glVertex3f(cos(a), sin(a), z);
		glNormal3f(cos(a), sin(a), 0);
		glVertex3f(cos(a), sin(a), 0);
	}
	glEnd();
}

void nave::drawCil1(float n, float z)
{
	float DOISPI = 2.0f * 3.14159f;
	float angle = 360.0f / n;


	glScaled(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += (360 / n))
	{
		float a = i * 3.14159f / 180;
		glNormal3f(cos(a), sin(a), z-0.5);
		glVertex3f(cos(a), sin(a), z-0.5);
	}

	for (int i = 0; i < 480; i += (360 / n))
	{
		float a = i * 3.14159f / 180;
		glNormal3f(cos(a), sin(a), 0.0f);
		glVertex3f(cos(a), sin(a), 0.0);
		glNormal3f(cos(a), sin(a) , z-0.5);
		glVertex3f(cos(a), sin(a) , z-0.5);
		glNormal3f(cos(a), sin(a), 0);
		glVertex3f(cos(a), sin(a), 0);
	}
	glEnd();
}
/*
void nave::montaFragmento(float px, float py, float pz){
	glPushMatrix();
		glPushMatrix();
			glRotatef(45, 0, 1, 1);
			//glRotatef(cos(45), 0, 1, 0);
			glColor4fv(_color1);
			glTranslatef(px + 2, py, pz);
			desenhaFragmento();
		glPopMatrix();
		glPushMatrix();
			glRotatef(cos(45), 1, 1, 0);
			//glRotatef(cos(45), 0, 1, 0);
			glColor4fv(_color1);
			glTranslatef(px + 2, py, pz);
			desenhaFragmento();
		glPopMatrix();
	glPopMatrix();


}

void nave::desenhaFragmento(){
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 1);
	glVertex3f(0.5, -0.25, 0.75);
	glVertex3f(0.5, -0.25, 0.25);
	glVertex3f(0, 0, 0);
	glEnd();
	
}*/