#include "colisao.h"

using namespace arkanoid;

colisao::colisao(){

}

colisao::~colisao(){

}

bool colisao::verificaColisao(tijolo* _list, bola* _bola){
	if (_list->getStatus()){
		float * firstposition = _list->getPosicao();
	float * secondposition = _bola->getPosicao();
	float firstradius = _list->getRaio();
	float secondradius = _bola->getRaio();
	float thirdradius = _list->getRaio() + 1;
	float d = sqrt(((firstposition[0] - secondposition[0]) * (firstposition[0] - secondposition[0])) 
		+ ((firstposition[1] - secondposition[1]) * (firstposition[1] - secondposition[1])) 
		+ ((firstposition[2] - secondposition[2]) * (firstposition[2] - secondposition[2])));

	if ((d <= firstradius + secondradius) && (abs(acos(d)) <= thirdradius + firstradius))
		return true;
	return false;}
}

bool colisao::verificaColisaoNave(nave* _nave, bola* _bola){
	float * firstposition = _nave->getPosicao();
	float * secondposition = _bola->getPosicao();
	float firstradius = _nave->getRaio();
	float secondradius = _bola->getRaio();
	float thirdradius = _nave->getRaio() + 2.5;
	float d = sqrt(((firstposition[0] - secondposition[0]) * (firstposition[0] - secondposition[0])) 
		+ ((firstposition[1] - secondposition[1]) * (firstposition[1] - secondposition[1])) 
		+ ((firstposition[2] - secondposition[2]) * (firstposition[2] - secondposition[2])));

	if ((d <= firstradius + secondradius) && (abs(acos(d)) <= thirdradius + firstradius))
		return true;
	return false;
}
