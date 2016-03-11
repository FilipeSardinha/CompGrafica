#ifndef _tijolo_h
#define _tijolo_h

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

namespace arkanoid{

	class tijolo{
	private:
		float raio;
		float r = rand() % 100 + 1;
		float b = rand() % 100 + 1;
		float g = rand() % 100 + 1;
		float x;
		float y;
		float z;
		GLfloat _color[4];
		bool status;
	public: 
		tijolo(float x, float y, float z);
		~tijolo();
		void desenha(float x, float y, float z);
		void actualiza(float x, float y, float z);
		float tijolo::getX();
		float tijolo::getY();
		float tijolo::getZ();
		bool tijolo::getStatus();
		void tijolo::setStatus();
		float tijolo::getRaio();
		float *tijolo::getPosicao();
	};
}
#endif 
