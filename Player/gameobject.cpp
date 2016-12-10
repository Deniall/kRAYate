#include "gameobject.h"
#include <iostream>

GameObject::GameObject(int sp, Vector2D pos, string nm, bool sol, double rad,string scr,bool port, int lev){
    sprite = sp;
    position = pos;
    name = nm;
    animate = false;
	animation = vector<int>();
	fps = 0;
	solid = sol;
	radius = rad;
	currentFrame = 0;
	time = 0.0;
	scripted = true;
	if(scr == "none"){
        scripted = false;
	}
	script = Script(scr);
	portal = port;
	loadLevel = lev;
}
GameObject::GameObject(int sp,Vector2D pos,string nm,bool anim,vector<int> frames,int framerate, bool sol, double rad,string scr,bool port, int lev){
    sprite = sp;
    position = pos;
    name = nm;
    animate = true;
	animation = frames;
	fps = framerate;
	solid = sol;
	radius = rad;
	currentFrame = 0;
	time = 0.0;
	scripted = true;
	if(scr == "none"){
        scripted = false;
	}
	script = Script(scr);
	portal = port;
	loadLevel = lev;
}

void GameObject::changeSprite(int sp){
    sprite = sp;
}

void GameObject::rename(string nm){
    name = nm;
}

vector<double> GameObject::update(double deltaTime, Vector2D playerPos){
    if(scripted){
    // pass the current gameobject variables to the script
        script.x = position.x;
        script.y = position.y;
        script.px = playerPos.x;
        script.py = playerPos.y;
        script.sprite = sprite;

        // parse the script
        script.parse();

        // set the variables of the gameobject
        position.x = script.x;
        position.y = script.y;
        sprite = script.sprite;
    }
    //cout<<"updating "<<name<<" - Animated "<<animate<<endl;
    if(animate){

        time += deltaTime;
        //cout<<time<<endl;
        //cout<<"1000/"<<fps<<" = "<<1000.00/fps<<endl;
        if(time >= 1.0/fps){
            time = 0.0;
            currentFrame = (currentFrame+1)%animation.size();
            sprite = animation[currentFrame];
            //cout<<"changing frame to: "<<sprite<<endl;
        }
    }
    double load = 0;
    if(portal){
        if(playerPos.distance(position) < radius){
            load = 1;
        }
    }
    if(solid){
        if(playerPos.distance(position) < radius){
            Vector2D diff(playerPos.x-position.x,playerPos.y-position.y);
            diff = diff.clampMagnitude(radius);
            playerPos.x = position.x + diff.x;
            playerPos.y = position.y + diff.y;
        }
    }
    vector<double> r = {playerPos.x,playerPos.y,load};
    return r;
}
