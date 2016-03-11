#include "parede.h"
#include "Header.h"

using namespace arkanoid;

extern bool perspective;

parede::parede(){
	_color[0] = 0.8;
	_color[1] = 0.5;
	_color[2] = 0.0;
	_color[3] = 0.1;
	_color1[0] = 1.0;
	_color1[1] = 1.0;
	_color1[2] = 1.0;
	_color1[3] = 0.0;
	desenha();
}

parede::~parede(){

}

void parede::desenha(){
	if (perspective){
		GLfloat scolor[] = { 0.7, 0.5, 0.0, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, scolor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
	}
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glScalef(1,1,3);
		glPushMatrix();
			glTranslatef(-19.5, 0, 0);
			glScalef(1.0, 40.0, 1.0);
			glColor4fv(_color);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(19.5, 0, 0);
			glScalef(1.0, 40.0, 1.0);
			glColor4fv(_color);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 19.5, 0);
			glScalef(40.0, 1.0, 1.0);
			glColor4fv(_color);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(19.5, 0, 0);
			glScalef(0.2, 39.0, 1.02);
			glColor4fv(_color1);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-19.5, 0, 0);
			glScalef(0.2, 39.0, 1.02);
			glColor4fv(_color1);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 19.5, 0);
			glScalef(39.0, 0.2, 1.02);
			glColor4fv(_color1);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

void parede::actualiza(){
	parede();
}