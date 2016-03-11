#ifndef _GESTOR_H
#define _GESTOR_H
#include <vector>
#include "Header.h"
#include "nave.h"
#include "tijolo.h"
#include "parede.h"
#include "bola.h"
#include "colisao.h"
#include <stdbool.h>
#include "chao.h"
#include <list>


namespace arkanoid {
	class gestorJogo{
	private :
		int _vidas;
		int _pontos;
		bool _fim;
		bool _vitoria;
		//nave* _jogador;
		parede* _parededeJogo;
		bola* _bola;
		colisao* _colisao;
		chao* _chao;
		//std::vector<tijolo*> _list;
	public :
		int _camera, _light;
		bool mode2d;
		nave* _jogador;
		std::vector <tijolo*> _list;
		gestorJogo::gestorJogo(int vidas);
		gestorJogo::~gestorJogo();
		void gestorJogo::novoJogador();
		void gestorJogo::novaBola();
		void gestorJogo::iniciaChao();
		void gestorJogo::iniciaTijolos();
		bool gestorJogo::temVidas();
		void gestorJogo::fire();
		void gestorJogo::criaParede();
		void gestorJogo::desenha();
		bool gestorJogo::moveDireita();
		bool gestorJogo::moveEsquerda();
		void gestorJogo::actualizaChao();
		void gestorJogo::actualizaJogador();
		bool gestorJogo::moveBola();
		float gestorJogo::getNaveX();
		void gestorJogo::colisaoTijolo();
		void gestorJogo::colisaoNave();
		bola* gestorJogo::getBola();
		tijolo* gestorJogo::getTijolo(int i);
		void gestorJogo::HUD();
		bool gestorJogo::decorrer();
		void gestorJogo::INSTA();
		int gestorJogo::getLight();
		int gestorJogo::pontos();
		float gestorJogo::getBolaDir();

	};
}
#endif;