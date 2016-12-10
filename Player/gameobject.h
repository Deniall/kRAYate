#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector2D.h"
#include "script.h"
#include <vector>
#include <string>

using namespace std;

class GameObject{
	public:

    bool scripted;
	Script script;
	int sprite;
	Vector2D position;
	string name;
	bool animate;
	vector<int> animation;
	int fps;
	int currentFrame;
	double time;
	bool solid;
	double radius;
	bool portal;
	int loadLevel;
    GameObject(int sp, Vector2D pos, string nm,bool sol,double rad,string scr,bool port, int lev);
	GameObject(int sp,Vector2D pos,string nm,bool anim,vector<int> frames,int framerate,bool sol,double rad,string scr,bool port, int lev);

	//GameObject(int sp,int x,int y,string nm);

	//void addScript(Script sc);

	//void removeScript(string scriptName);

	void changeSprite(int sp);

	void rename(string nm);

	vector<double> update(double deltaTime, Vector2D playerPos);

};

#endif
