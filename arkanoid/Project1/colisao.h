#ifndef _COLISAO_H
#define _COLISAO_

#include "Header.h"
#include "tijolo.h"
#include "bola.h"
#include "nave.h"
#include <math.h>


namespace arkanoid{

	class colisao{		
	public:
		colisao::colisao();
		colisao::~colisao();
		bool colisao::verificaColisao(tijolo* _tijolo, bola* _bola);
		bool colisao::verificaColisaoNave(nave* _nave, bola* _bola);
	};
}
#endif 
