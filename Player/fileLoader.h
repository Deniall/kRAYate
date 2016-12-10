#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "quickcg.h"
#include "iniRead.h"
#include "csvReader.h"
#include "gameobject.h"
#include "vector2D.h"

using namespace std;
using namespace QuickCG;

struct Sprite
        {
          double x;
          double y;
          int texture;
        };

class fileLoader
{
    public:

        static vector<Sprite> getSprites(int level){
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            string levelpath = iniRead::getField("gameData.ini","Level"+numStr,"sprites");
            vector< vector<double> > dSprites = CSVReader::readLines(levelpath);
            vector<Sprite> r(dSprites.size());
            for(int i = 0;i < dSprites.size();i++){
                r[i].x = dSprites[i][0];
                r[i].y = dSprites[i][1];
                r[i].texture = (int)dSprites[i][2];
            }
            return r;
        }

        static vector<GameObject> getGameObjectsFromPrefabs(int level){
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            string levelpath = iniRead::getField("gameData.ini","Level"+numStr,"sprites");
            vector< vector<string> > d = CSVReader::readLinesString(levelpath);
            vector<GameObject> r = vector<GameObject>();
            for(int i = 0;i < d.size();i++){
                Vector2D pos(strtod(d[i][0].c_str(), NULL),strtod(d[i][1].c_str(), NULL));
                string name = d[i][2];
                string prefab = d[i][3];
                int tex = atoi(iniRead::getField("gameData.ini","Prefab"+prefab,"tex").c_str());
                bool solid = false;
                if(iniRead::getField("gameData.ini","Prefab"+prefab,"solid") == "true"){
                    solid = true;
                }
                double radius = strtod(iniRead::getField("gameData.ini","Prefab"+prefab,"radius").c_str(), NULL);
                bool animated = false;
                if(iniRead::getField("gameData.ini","Prefab"+prefab,"animated") == "true"){
                    animated = true;
                }
                int loadlev = 0;
                bool portal = false;
                if(iniRead::getField("gameData.ini","Prefab"+prefab,"loadLevel") != "none"){
                    loadlev = atoi(iniRead::getField("gameData.ini","Prefab"+prefab,"loadLevel").c_str());
                    portal = true;
                }
                string script = iniRead::getField("gameData.ini","Prefab"+prefab,"script");
                if(animated){
                    vector<int> frames = CSVReader::readString(iniRead::getField("gameData.ini","Prefab"+prefab,"animation"));
                    int fps = atoi(iniRead::getField("gameData.ini","Prefab"+prefab,"fps").c_str());
                    GameObject g(tex,pos,name,animated,frames,fps,solid,radius,script,portal,loadlev);
                    r.push_back(g);
                }else{
                    GameObject g(tex,pos,name,solid,radius,script,portal,loadlev);
                    r.push_back(g);
                }

            }
            return r;
        }

        static vector<GameObject> getGameObjects(int level){
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            string levelpath = iniRead::getField("gameData.ini","Level"+numStr,"sprites");
            vector< vector<string> > d = CSVReader::readLinesString(levelpath);
            vector<GameObject> r = vector<GameObject>();
            for(int i = 0;i < d.size();i++){
                Vector2D pos(strtod(d[i][0].c_str(), NULL),strtod(d[i][1].c_str(), NULL));
                int tex = atoi(d[i][2].c_str());
                string name = d[i][3];
                GameObject g(tex,pos,name,false,0.0,"none",false,0);
                r.push_back(g);
            }
            return r;
        }

        static int getPlayerX(int level){
        stringstream ss;
            ss << (level);
            	string numStr = ss.str();

            return atoi(iniRead::getField("gameData.ini","Level"+numStr,"playerX").c_str());
        }

        static int getLevels(){
            return atoi(iniRead::getField("gameData.ini","Game","noOfLevels").c_str());
        }

        static int getScreenHeight(){
            return atoi(iniRead::getField("gameData.ini","Game","screenHeight").c_str());
        }



        static int getScreenWidth(){
            return atoi(iniRead::getField("gameData.ini","Game","screenWidth").c_str());
        }

        static int spritesUsed(int level){
            stringstream ss;
            ss << (level);
            	string numStr = ss.str();
            return atoi(iniRead::getField("gameData.ini","Level"+numStr,"spritesUsed").c_str());
        }

        static int getCielingTex(int level){
            stringstream ss;
            ss << (level);
            	string numStr = ss.str();
            return atoi(iniRead::getField("gameData.ini","Level"+numStr,"cieling").c_str());
        }

        static int getFloorTex(int level){
            stringstream ss;
            ss << (level);
            	string numStr = ss.str();
            return atoi(iniRead::getField("gameData.ini","Level"+numStr,"floor").c_str());
        }

/*        static Sprite spriteList(int level){
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            for (int i = 0; i <= spritesUsed(); i++){
                stringstream ss;
                ss << (i);
                string spriteStr = ss.str();
                sprite[i] = (iniRead::getField("gameData.ini","Level"+numStr,"sprite"+spriteStr));
            }
            return sprite;

        }
*/


        static int getPlayerY(int level){
            stringstream ss;
            ss << (level);
            	string numStr = ss.str();
            return atoi(iniRead::getField("gameData.ini","Level"+numStr,"playerY").c_str());
        }

        static int texturesUsed(){
            return atoi(iniRead::getField("gameData.ini","Game","texturesUsed").c_str());
        }

        static int spritesUsed(){
            return atoi(iniRead::getField("gameData.ini","Game","spritesUsed").c_str());
        }

        static double playerMoveSpeed(){
            return atof(iniRead::getField("gameData.ini","Game","playerSpeed").c_str());
        }

        static double playerRotSpeed(){
            return atof(iniRead::getField("gameData.ini","Game","playerRotate").c_str());
        }

        static string gameName(){
            return iniRead::getField("gameData.ini","Game","name");
        }

        static ColorRGB getBackCol(int level,bool topbot){
        	stringstream ss;
            	ss << (level);
            	string numStr = ss.str();
            	string tb;
        	if(topbot){
        		tb = "top";
        	}else{
        		tb = "bot";
        	}
        	int red = atoi(iniRead::getField("gameData.ini","Level"+numStr,tb+"R").c_str());
            int green = atoi(iniRead::getField("gameData.ini","Level"+numStr,tb+"G").c_str());
            int blue = atoi(iniRead::getField("gameData.ini","Level"+numStr,tb+"B").c_str());
            ColorRGB r = ColorRGB(red,green,blue);
            return r;
        }

        static vector<ColorRGB> getGameTextures(){
            int len = texturesUsed();
            vector<ColorRGB> colours(len);
            for(int i = 0;i < len;i++){
                stringstream ss;
                ss << (i+1);
                string numStr = ss.str();
                int red = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"r").c_str());
                int green = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"g").c_str());
                int blue = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"b").c_str());
                colours[i] = ColorRGB(red,green,blue);
            }
            return colours;
        }

        static vector<ColorRGB> getMapColours(){
            int len = texturesUsed();
            vector<ColorRGB> colours(len);
            for(int i = 0;i < len;i++){
                stringstream ss;
                ss << (i+1);
                string numStr = ss.str();
                int red = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"r").c_str());
                int green = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"g").c_str());
                int blue = atoi(iniRead::getField("gameData.ini","Texture"+numStr,"b").c_str());
                colours[i] = ColorRGB(red,green,blue);
            }
            return colours;
        }

        static void loadLevel(int map[64][64],int level){
            vector<ColorRGB> colourList = getMapColours();
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            string levelpath = iniRead::getField("gameData.ini","Level"+numStr,"texture");
            vector<ColorRGB> levelImg;
            long unsigned int hw = 64;
            loadImage(levelImg,hw,hw,levelpath);
            for(int i = 0;i < 64;i++){
                for(int j = 0;j < 64;j++){
                    map[i][j] = 255 - levelImg[j*64+i].r;
                }
            }
        }

        static void clearLevel(int map[64][64], int level){

            vector<ColorRGB> colourList = getMapColours();
            stringstream ss;
            ss << (level);
            string numStr = ss.str();
            string levelpath = iniRead::getField("gameData.ini","Level"+numStr,"texture");
            vector<ColorRGB> levelImg;
            long unsigned int hw = 64;
            loadImage(levelImg,hw,hw,levelpath);
            for(int i = 0;i < colourList.size();i++){
                for(int j = 0;j < levelImg.size();j++){
                    if(levelImg[j] == colourList[i]){
                        int x = j%64;
                        int y = j/64;
                        map[x][y] = 0;
                    }


                }
            }

        }


    protected:

    private:
};

#endif // FILELOADER_H
