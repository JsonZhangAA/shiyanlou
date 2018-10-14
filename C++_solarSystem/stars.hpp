#include <GL/glut.h>
class Star{
public:
	GLfloat radius,selfSpeed,speed,distance;
	Star * parentStar;
	GLfloat alphaSelf,alpha;
//	GLfloat color[4];
	
	Star(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_);
	void drawStar();
	virtual void update(long timeRefresh);
	virtual	void draw(){
		drawStar();
	}
};

class Planet:public Star{
public:
	GLfloat color[4];
	
	Planet(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_,GLfloat color_[4]);
	void drawPlanet();
	virtual void draw(){
		drawStar();
		drawPlanet();
	}	
};

class LightPlanet:public Planet{
public:
	LightPlanet(GLfloat radius_,GLfloat selfSpeed_,GLfloat speed_,GLfloat distance_,Star * parentStar_,GLfloat alphaSelf_,GLfloat alpha_,GLfloat color_[4]);
	void drawLightPlanet();
	virtual void draw(){
		drawStar();
		drawPlanet();
		drawLightPlanet();
	}
};

