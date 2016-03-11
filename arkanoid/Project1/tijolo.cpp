#include "tijolo.h"

using namespace arkanoid;
	
extern bool hitbox;
extern bool perspective;

tijolo::tijolo(float x, float y, float z){
	raio = 1.25;
	this->x = x;
	this->y = y;
	this->z = z;
	this->status = true;
	_color[0] = r/100;
	_color[1] = g/100;
	_color[2] = b/100;
	_color[3] = 0.0;
	this->desenha(x, y, z);

}

tijolo::~tijolo(){
	this->status = false;
}

void tijolo::desenha(float x, float y, float z){
	
	if (perspective){
		GLfloat scolor[] = { r/100, g/100, b/100, 0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, scolor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	}
	glPushMatrix();
		glPushMatrix();
			glTranslatef(x, y, z);
			glScalef(2.0, 1.0, 1.0); 
			glColor4fv(_color);
			glutSolidCube(1);
		glPopMatrix();
		if (hitbox){
			glPushMatrix();
				glTranslatef(x, y , z);
				glColor4fv(_color);
				glutWireSphere(raio, 20, 20);
			glPopMatrix();
		}
	glPopMatrix();
}

void tijolo::actualiza(float x, float y, float z){
	desenha(x , y, z);
}

void tijolo::setStatus(){
	this->status = false;
}

float tijolo::getRaio(){
	return this->raio;
}

bool tijolo::getStatus(){
	return this->status; 
}

float tijolo::getX(){
	return this->x;
}

float tijolo::getY(){
	return this->y;
}

float tijolo::getZ(){
	return this->z;
}

float * tijolo::getPosicao(){
	float * toreturn = (float*)malloc(3 * sizeof(float));
	toreturn[0] = x;
	toreturn[1] = y;
	toreturn[2] = z;
	return toreturn;
}