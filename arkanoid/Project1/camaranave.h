#ifndef _CAMARANAVE_H
#define _CAMARANAVE_H

#include "Header.h"

namespace arkanoid{

	class camaranave{
	private:
		float x;
		int status;
	public:
		camaranave(float x);
		~camaranave();
		void desenha();
		void actualiza();
		float camaranave::getX();
		float camaranave::getY();
		float camaranave::getZ();
		int camaranave::getStatus();
		void camaranave::setStatus();

	};
}
#endif 
