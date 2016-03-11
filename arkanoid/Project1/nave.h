#ifndef _nave_h
#define _nave_h

#include "Header.h"


namespace arkanoid {
	
	class nave{
	private:
		float raio;
		float px;
		float py;
		float pz;
		GLfloat _color[4];
		GLfloat _color1[4];
	public:
		nave(float x, float y, float z);
		~nave();
		void nave::desenha(float x, float y, float z);
		void nave::actualiza();
		bool nave::naveDireita();
		bool nave::naveEsquerda();
		float nave::getX();
		float nave::getY();
		float nave::getZ();
		float nave::getRaio();
		float *nave::getPosicao();
		void nave::montaFragmento(float px, float py, float pz);
		void nave::desenhaFragmento();
		void nave::drawCil2(float n, float z);
		void nave::drawCil1(float n, float z);
	};
}

#endif // !_nave_h
