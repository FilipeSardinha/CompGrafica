#include "chao.h"

using namespace arkanoid;

const bool LoadTexture(const string & textureFilename);
extern bool perspective;
extern bool useLights;
extern bool luzspot;
extern bool luzbola;
extern int fundo;

chao::chao(){
	glLoadIdentity();
	if (fundo == 1)
		LoadTexture("fundo1.bmp");
	else if (fundo == 2)
		LoadTexture("grid.bmp");
	else if (fundo == 3)
		LoadTexture("Background.bmp");
	else if (fundo == 4)
		LoadTexture("Background1.bmp");
	else if (fundo == 5)
		LoadTexture("Background2.bmp");
}

chao::~chao(){
}

void chao::desenha(){

	glEnable(GL_TEXTURE_2D);

	GLfloat color[] = { 1.0, 1., 1., 0 };
	GLfloat spec[] = { 0.5, 0.5, 0.5, 1 };
	if (((((luzspot || luzbola)) || (luzspot && luzbola)) && useLights)|| useLights){
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	}
	else
		glColor4fv(color);

	float s1, s2, t1, t2;
	t2 = 0.0;
	for (int i = 0; i < 40; i++){
		t1 = t2;
		s2 = 0;
		t2 = 1.0 *  (i + 1) / 40;
		for (int j = 0; j < 40; j++){
			s1 = s2;
			s2 = 1.0 * (j + 1) / 40;
			glPushMatrix();
				glNormal3f(0, 0, 1);
				glBegin(GL_POLYGON);
				glTexCoord2f(s1, t1);
				glVertex3f(-20 + 1 * j, -20 + 1 * i, -2);
				glTexCoord2f(s2, t1);
				glVertex3f(-20 + 1 + 1 * j, -20 + 1 * i, -2);
				glTexCoord2f(s2, t2);
				glVertex3f(-20 + 1 + 1 * j, -20 + 1 + 1 * i, -2);
				glTexCoord2f(s1, t2);
				glVertex3f(-20 + 1 * j, -20 + 1 + 1 * i, -2);
				glEnd();
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void chao::moveChao(){
}


const bool LoadTexture(const string & textureFilename)
{

	BMPloader * bitmap = new BMPloader(textureFilename);
	if (bitmap->Isvalid())
	{
		glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, bitmap->Image());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		delete bitmap;
		return true;
	}
	else
		delete bitmap;
	return false;
}