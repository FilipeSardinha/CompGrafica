#ifndef _CHAO_H
#define _CHAO_H

#include "Header.h"
#include "BMPReader.h"

namespace arkanoid{
	class chao{
	private:
		GLuint _texture;
	public:
		chao::chao();
		chao::~chao();
		void chao::desenha();
		void chao::moveChao();
	};
}
#endif