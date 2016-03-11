#include "gestorJogo.h"

using namespace arkanoid;
#include <stdio.h>
#include <GL\GLU.h>

extern bool perspective;
extern bool useLights;
extern bool help;

gestorJogo::gestorJogo(int vidas)
{
	iniciaChao();
	_vidas = vidas;
	_pontos = 0;
	_camera = 1;
	_light = 1;
	_fim = false;
	useLights = false;
	_vitoria = false;
	mode2d = true;
	iniciaTijolos();
	criaParede();
	novoJogador();
	novaBola();
	this->HUD();
	
}

bool gestorJogo::temVidas(){
	if (_vidas > 0)
		return true;
	return false;
}
void gestorJogo::novaBola(){
	_bola = new bola(0, -16.0, 0);
}

void gestorJogo::iniciaChao(){
	_chao = new chao();
}

bool gestorJogo::decorrer(){
	return !(_vitoria || _fim);
}

void gestorJogo::novoJogador(){
	_jogador = new nave(0,-17.5, 0);
}

void gestorJogo::actualizaChao(){
	glTranslated(0, 0, 0);
	_chao->desenha();
}

int gestorJogo::getLight(){
	return _light;
}


void gestorJogo::actualizaJogador(){
	_jogador->actualiza();
	_bola->actualiza();
	_parededeJogo->actualiza();
	
	int i;
	for (i = 0; i < 96; i++){
		if (this->_list[i]->getStatus() == true)
			this->_list[i]->actualiza(this->_list[i]->getX(), this->_list[i]->getY(), this->_list[i]->getZ());
	}actualizaChao();
}

void gestorJogo::fire(){
	_bola->setInit();
}

float gestorJogo::getNaveX(){
	return this->_jogador->getX();
}


void gestorJogo::iniciaTijolos(){
	int i, t;
	srand(time(NULL));
	for (i = 0; i <= 5; i++){
		for (t = 0; t <= 15; t++){
			switch (i){
			case (0) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 17.0, 0.0));
			case(1) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 15.75, 0.0));
			case(2) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 14.50, 0.0));
			case(3) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 13.25, 0.0));
			case(4) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 12.0, 0.0));
			case(5) :
				this->_list.insert(_list.end(), new tijolo(-16.5 + t*2.20, 10.75, 0.0));
			}
		}

	}
};


void gestorJogo::criaParede(){
	new parede();
};
bool gestorJogo::moveDireita(){
	_jogador->naveDireita();
	_bola->bolaDireita();
	return false;
}

bool gestorJogo::moveEsquerda(){
	_jogador->naveEsquerda();
	_bola->bolaEsquerda();
	return false;
}

bola* gestorJogo::getBola(){
	return _bola;
}

tijolo* gestorJogo::getTijolo(int i){
	return _list[i];
}


void gestorJogo::colisaoTijolo(){
	int i;
	for (i = 0; i < 96; i++){
		if (_colisao->verificaColisao(this->_list[i], this->_bola)){
			this->_list[i]->setStatus();
			if (this->_list[i]->getY() - 0.5 > this->_bola->getY()){
				this->_bola->inverte();
				_pontos += 5;
			}
			else if (this->_list[i]->getY() + 0.5 < this->_bola->getY()){
				this->_bola->inverteX();
				_pontos += 5;
			}
		}
	}	
}

void gestorJogo::colisaoNave(){
	if (_colisao->verificaColisaoNave(this->_jogador, this->getBola()))
		this->_bola->inverte();
}

bool gestorJogo::moveBola(){
	this->colisaoTijolo();
	this->colisaoNave();
	_bola->bolaMove();
	if (_bola->getY() < -19.5){
		_bola = NULL;
		delete _bola;
		_jogador = NULL;
		delete _jogador;
		_jogador = new nave(0, -17.5, 0);
		_bola = new bola(0, -16.0, 0);
		--_vidas;
	}
	return false;
}

float gestorJogo::getBolaDir(){
	return this->getBola()->getDir();
}


void gestorJogo::desenha(){
	if (decorrer()){
		float x = _jogador->getX();
		float y = _jogador->getY();
		float z = _jogador->getZ();
		criaParede();
		_jogador->desenha(x, y, z);
		size_t i;
		for (i = 0; i < 96; i++)
		if (this->_list[i]->getStatus())
			this->_list[i]->actualiza(this->_list[i]->getX(), this->_list[i]->getY(), this->_list[i]->getZ());
		
	}
	this->HUD();
}

void RenderString(char *str, void *font, int x, int y)
{
	glRasterPos2i(x, y);

	int i = 0;

	for (char *c = str; *c != '\0'; c++, i++)
		glutBitmapCharacter(font, *c);
}

void gestorJogo::HUD(){
	int width = glutGet(GLUT_SCREEN_WIDTH);
	int height = glutGet(GLUT_SCREEN_HEIGHT);
	char str[100];

	/*Preparar modo 2D*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if (perspective)
		glDisable(GL_LIGHTING);

	sprintf_s(str, "Vidas: %d", this->_vidas);
	if (!_fim){
		switch (_vidas){
		case 3:{
			glColor3f(0, 1, 0);
			if (_pontos == 480)
				_vitoria = true;
			   }break;
		case 2:{
			glColor3f(1, 1, 0);
			if (_pontos == 480)
				_vitoria = true;
			   }break;
		case 1:{
			glColor3f(1, 0, 0);
			if (_pontos == 480)
				_vitoria = true;
			   }break;
		case 0:{
			if (_pontos == 480)
				_vitoria = true;
			else {
				_fim = true;
				delete _bola;
			}
			   }
		default:break;
	
		}
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2)- 100, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 360);
	}
	else{
		glColor3f(1, 1, 1);
		sprintf_s(str, "GAME OVER :'(");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) /2 ) - 100 , (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 360);
	}
	glColor3f(1, 1, 1);
	sprintf_s(str, "PRESS 'h' ajuda");
	RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) + 300, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 360);
	glColor3f(1, 1, 1);
	sprintf_s(str, "Pontos: %d", this->_pontos);
	RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH)/2 )- 440, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 360);
	if (_vitoria){
		glColor3f(1, 1, 1);
		sprintf_s(str, " YEEEAAAH VICTORY!!!");
		RenderString(str, GLUT_BITMAP_9_BY_15, glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
	}
	if (!decorrer()){
		sprintf_s(str, "PRESS 'R' TO RESTART THE GAME");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 100);
	}
	if (help){
		glColor3f(1, 1, 1);
		sprintf_s(str, "PRESS 'a' mover esquerda");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 100);
		sprintf_s(str, "PRESS 'd' mover direita");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 80);
		sprintf_s(str, "PRESS 'f' disparar");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 60);
		sprintf_s(str, "PRESS '1' camara ortogonal");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 40);
		sprintf_s(str, "PRESS '2' camara perspectiva");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 20);
		sprintf_s(str, "PRESS '4' camara 1º pessoa");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) );
		sprintf_s(str, "PRESS 'z' mudar de fundo");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 120);
		sprintf_s(str, "PRESS 'l' acender/apagar as luzes");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 140);
		sprintf_s(str, "PRESS 'm' acender/apagar as spots");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 160);
		sprintf_s(str, "PRESS 'n' acender/apagar a luz da bola");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 180);
		sprintf_s(str, "PRESS 'h' ajuda");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 200);
		sprintf_s(str, "PRESS 'e' sair");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 220);
		sprintf_s(str, "PRESS 'x' definir a dificuldade");
		RenderString(str, GLUT_BITMAP_9_BY_15, (glutGet(GLUT_SCREEN_WIDTH) / 2) - 200, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 240);
	}
	/*Sair de modo 2D*/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	if (perspective)
		glEnable(GL_LIGHTING);

}

void gestorJogo::INSTA(){
	int i;
	_pontos = 480;
	for (i = 0; i < 96; i++){
		this->_list[i]->setStatus();
	}
}
