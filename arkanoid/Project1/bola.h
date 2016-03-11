#ifndef _bola_h
#define _bola_h

#include "Header.h"

namespace arkanoid{

	class bola{
	private:
		float raio;
		float px;
		float py;
		float pz;
		float diry;
		float dirx;
		bool status;
		bool init;
		GLfloat _color[4];
	public:
		bola(float x, float y, float z);
		~bola();
		void desenha(float x, float y, float z);
		void actualiza();
		bool bola::bolaDireita();
		bool bola::bolaEsquerda();
		bool bola::getInit();
		void bola::setInit();
		bool bola::bolaMove();
		float bola::getX();
		float bola::getDir();
		float bola::getY();
		float bola::getZ();
		float bola::getRaio();
		void bola::inverte();
		void bola::inverteX();
		float *bola::getPosicao();
	};
}
#endif 
