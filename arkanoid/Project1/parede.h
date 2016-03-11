#ifndef _parede_h
#define _parede_h

#include "Header.h"

namespace arkanoid{

	class parede{
	private:
		GLfloat _color[4];
		GLfloat _color1[4];
	public:
		parede();
		~parede();
		void desenha();
		void actualiza();

	};
}
#endif 
