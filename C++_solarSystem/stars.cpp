#include "stars.hpp"
#define PI 3.1415926535
Star::Star(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_){

}

void Star::drawStar(){

}

void Star::update(long timeRefresh){

}


Planet::Planet(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_,GLfloat color_[4]):Star(radius_,selfSpeed_,speed_,distance_,parentStar_,alphaSelf_,alpha_){

}

void Planet::drawPlanet(){
	
}


LightPlanet::LightPlanet(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_,GLfloat color_[4]):Planet(radius_,selfSpeed_,speed_,distance_,parentStar_,alphaSelf_,alpha_,color_){

}

void LightPlanet::drawLightPlanet(){

}


