/* INCLUDES */
#include <cmath>
#include <vector>
#include <iostream>
#include "quickcg.h"
#include "fileLoader.h"
#include <sstream>
#include <string>
#include "vector2D.h"
#include "gameobject.h"


using namespace QuickCG;

/* CONSTANTS */
#define mapWidth 64
#define mapHeight 64

/*! \mainpage kRAYate: A raycasting, retro game-making tool.
 *
 * \section intro_sec The kRAYate Team
 *
 * \subsection intro_team There are five of us working on this project:
 * \subsection breogan Breogan Hackett - Project founder, working on assests, packaging and a GameObject system.
 * \subsection niall Niall Walsh - Player Developer: Rendering engine.
 * \subsection marcin Marcin Gardas - Player Developer: Player scripting.
 * \subsection james James Storey - Sound and music.
 * \subsection jay James Toolen - Editor development.
 *
 * \section install_sec Installation
 *
 * \subsection step1 We are still working on this!
 *
 * this page is still in progress.
 */



int worldMap[mapWidth][mapHeight];     /**< This initialises a map of 64x64. */

int screenWidth = fileLoader::getScreenWidth();     /**< Gets the screen width from the .ini */
int screenHeight = fileLoader::getScreenHeight();     /**< Gets the screen height from the .ini */

string gameName = fileLoader::gameName();     /**< Gets the window(game) name from the .ini */
int noOfLevels = fileLoader::getLevels();     /**< Gets the number of levels from the .ini */
int levelNo = 1;     /**< Default level value is 1. */
int cielingTex = fileLoader::getCielingTex(levelNo);/**<Gets the texture index of the cieling texture */
int floorTex = fileLoader::getFloorTex(levelNo);/**<Gets the texture index of the floor texture */
int nogameObjects = fileLoader::spritesUsed(levelNo);     /**< Gets the number of gameObjects used from the .ini */

double moveSpeed = fileLoader::playerMoveSpeed();     /**< A variable used to increase or decrease the movement speed of the player. */
double moveSideSpeed = moveSpeed/2;     /**< A variable used to increase or decrease the sidewards movement speed of the player. */
double rotSpeed = fileLoader::playerRotSpeed();     /**< Used to inc/dec speed of rotation. */
double oldMoveSpeed = moveSpeed;     /**< Used to make sprinting work. */

double startPosX = fileLoader::getPlayerX(levelNo);     /**< Gets the initial player X coordinate of the level from the .ini */
double startPosY = fileLoader::getPlayerY(levelNo);     /**< Gets the initial player Y coordinate of the level from the .ini */
double startCameraPlaneX = 0;     /**< Initialiser variable to make the 'fake' 3D camera plane work. */
double startCameraPlaneY = 0.66;     /**< See startCameraPlaneX. */
double startDirX = -1.0;     /**< Start direction value. TO DO: CHANGE SO IT GETS FROM .INI FILE. */
double startDirY = 0.0;     /**< See startDirX */


double oldMoveSideSpeed = moveSideSpeed;     /**< Used to make side-sprinting work. */
int texturesUsed = fileLoader::texturesUsed();     /**< Gets the amount of textures used from the .ini file. */

//function used to sort the gameObjects
void gameObjectSort(int* order, double* dist, int amount);     /**< Function that sorts the gameObjects so that they dont overlap. */
void changeLevel(int dir, double posX, double posY);

Vector2D changeLevel(int level)
{
    fileLoader::clearLevel(worldMap, levelNo);
    /*if (dir == 1){
        levelNo+=1;
    }
    else{
        levelNo-=1;
    }*/
    levelNo=level;
    stringstream ss;
    ss << levelNo;
    string levelStr = ss.str();
    redraw();
    cls();
    fileLoader::loadLevel(worldMap,levelNo);
    print("Level "+levelStr+" loaded successfully.", 0, 10, RGB_White, 0, RGB_White, 5000);
    redraw();
    cls();
    int posX = fileLoader::getPlayerX(levelNo);
    print("Level "+levelStr+" loaded successfully.", 0, 10, RGB_White, 0, RGB_White, 5000);
    redraw();
    cls();
    int posY = fileLoader::getPlayerY(levelNo);
    print("Level "+levelStr+" loaded successfully.", 0, 10, RGB_White, 0, RGB_White, 5000);
    redraw();
    cls();
    Vector2D r(posX,posY);
    return r;
}

int main(int /*argc*/, char */*argv*/[])
{
    //std::cout<<"Hello Worldddd!"<<endl;

    vector<GameObject> gameObject = fileLoader::getGameObjectsFromPrefabs(levelNo);
    int numGameObjects = gameObject.size();
        /*{
            {33, 35, 2},
            {32, 30, 6},
            {25, 37, 2}
        };*/     /**< Initialises the gameObjects X, Y and texture index, using the gameObject struct. */
    int gameObjectOrder[numGameObjects];     /**< Array used to get the order of gameObjects right, used in the gameObjectSort function. */
    double gameObjectDistance[numGameObjects];     /**< Array of all gameObject distances. Used in the gameObjectSort function. */
    // screen buffer and depth buffer for gameObjects
    Uint32 buffer[screenWidth][screenHeight];     /**< The buffer that is used to draw all graphics. It draws everything Y-stripe by Y-stripe instead of pset, which does it pixel by pixel. */
    double ZBuffer[screenWidth];     /**< A ZBuffer, otherwise known as a depth buffer. This buffers gameObjects in the right order. */

    // load map index 1
    fileLoader::loadLevel(worldMap,levelNo);     /**< Loads the first level and puts it into the 64x64 map. */

    double posX = startPosX;
    double posY = startPosY;
    double dirX = startDirX;
    double dirY = startDirY;
    double cameraPlaneX = startCameraPlaneX;
    double cameraPlaneY = startCameraPlaneY;

    // create player script object
    Script script("player.krayate");

    std::vector<Uint32> crosshairTexture;
    long unsigned int ctw = 15;
    long unsigned int cth = 15;
    loadImage(crosshairTexture, ctw, cth, "Data/Textures/crosshair.png");     /**< Loads crosshair .png file. */

    double time = 0;     /**< Used for FPS counter. */
    double oldTime = 0;     /**< Used for FPS counter. */

    std::vector<Uint32> texture[texturesUsed];     /**< Initialises the texture vector. */
    for(int i = 0; i < 11; i++) texture[i].resize(mapWidth * mapHeight);     /**< In case someone uses a texture that is greater than 64x64, this will resize it. Hooray for stupidity handling! */

    screen(fileLoader::getScreenWidth(),fileLoader::getScreenHeight(), 0, gameName);     /**< Initialises the game window, using the screen height and width from the .ini, as well as the game name. */
    unsigned long tw, th;
    for( int i = 0; i < texturesUsed; i++) {
        std::stringstream ss;
        ss << i+ 1;
        loadImage(texture[i], tw, th, "Data/Textures/" + ss.str() + ".png");
    }
    while(!done())
    {
        //timing for input and FPS counter
        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
        Vector2D playerPos(posX,posY);
        //update gameObjects before rendering to counter collision issues
        for(int i = 0; i < numGameObjects; i++)
        {
            vector<double> n = gameObject[i].update(frameTime,playerPos);
            playerPos.x = n[0];
            playerPos.y = n[1];
            posX = playerPos.x;
            posY = playerPos.y;
            if(n[2] > 0){
                Vector2D p = changeLevel(gameObject[i].loadLevel);
                posX = p.x;
                posY = p.y;
                cout<<"levelLoaded"<<endl;
                gameObject = fileLoader::getGameObjectsFromPrefabs(levelNo);
                numGameObjects = gameObject.size();
                cout<<"gameObjects"<<endl;
                break;
            }
        }
        for(int x = 0; x < w; x++) // w is the screen width, this is the merhod that scans the screen and sends out rays
        {
          //calculate ray position and direction
          double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
          double rayPosX = posX;
          double rayPosY = posY;
          double rayDirX = dirX + cameraPlaneX * cameraX;
          double rayDirY = dirY + cameraPlaneY * cameraX;

          //which box of the map we're in
          int mapSquareX = int(rayPosX);
          int mapSquareY = int(rayPosY);

          //length of ray from current position to next x or y-side
          double sideDistFromOriginX;
          double sideDistFromOriginY;

          //length of ray from one x or y-side to next x or y-side
          double nextDistanceX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
          double nextDistanceY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
          double totalRayDist;

          //what direction to step in x or y-direction (either +1 or -1)
          int stepX;
          int stepY;

          int hit = 0; //was there a wall hit?
          int side; //was a NS or a EW wall hit?

          //calculate step and initial sideDist
          if (rayDirX < 0)
          {
            stepX = -1;
            sideDistFromOriginX = (rayPosX - mapSquareX) * nextDistanceX;
          }
          else
          {
            stepX = 1;
            sideDistFromOriginX = (mapSquareX + 1.0 - rayPosX) * nextDistanceX;
          }
          if (rayDirY < 0)
          {
            stepY = -1;
            sideDistFromOriginY = (rayPosY - mapSquareY) * nextDistanceY;
          }
          else
          {
            stepY = 1;
            sideDistFromOriginY = (mapSquareY + 1.0 - rayPosY) * nextDistanceY;
          }
          //perform DDA
          while (hit == 0)
          {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistFromOriginX < sideDistFromOriginY)
            {
              sideDistFromOriginX += nextDistanceX;
              mapSquareX += stepX;
              side = 0;
            }
            else
            {
              sideDistFromOriginY += nextDistanceY;
              mapSquareY += stepY;
              side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapSquareX][mapSquareY] > 0) hit = 1;
          }

          //Calculate distance of perpendicular ray (oblique distance will give fisheye effect!)
          if (side == 0) totalRayDist = fabs((mapSquareX - rayPosX + (1 - stepX) / 2) / rayDirX);
          else       totalRayDist = fabs((mapSquareY - rayPosY + (1 - stepY) / 2) / rayDirY);

          //Calculate height of line to draw on screen
          int lineHeight = abs(int(h / totalRayDist));

          //calculate lowest and highest pixel to fill in current stripe
          int drawStart = -lineHeight / 2 + h / 2;
          if(drawStart < 0) drawStart = 0;
          int drawEnd = lineHeight / 2 + h / 2;
          if(drawEnd >= h) drawEnd = h - 1;
          //texturing calculations
          int texNum = worldMap[mapSquareX][mapSquareY] - 1; //1 subtracted from it so that texture 0 can be used!

          //calculate value of wallX
          double wallX; //where exactly the wall was hit
          if (side == 1) wallX = rayPosX + ((mapSquareY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
          else       wallX = rayPosY + ((mapSquareX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
          wallX -= floor((wallX));

          //x coordinate on the texture
          int texX = int(wallX * double(mapWidth));
          if(side == 0 && rayDirX > 0) texX = mapWidth - texX - 1;
          if(side == 1 && rayDirY < 0) texX = mapWidth - texX - 1;
          for(int y = drawStart; y < drawEnd; y++)
          {
            int d = y * 256 - h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
            int texY = ((d * mapWidth) / lineHeight) / 256;
            int colour = texture[texNum][mapWidth * texY + texX];
            //make colour darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1) colour = (colour >> 1) & 8355711;
            buffer[x][y] = colour;
          }

          //SET THE ZBUFFER FOR THE gameObject CASTING
          ZBuffer[x] = totalRayDist; //perpendicular distance is used

          //FLOOR CASTING
          double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

          //4 different wall directions possible
          if(side == 0 && rayDirX > 0)
          {
            floorXWall = mapSquareX;
            floorYWall = mapSquareY + wallX;
          }
          else if(side == 0 && rayDirX < 0)
          {
            floorXWall = mapSquareX + 1.0;
            floorYWall = mapSquareY + wallX;
          }
          else if(side == 1 && rayDirY > 0)
          {
            floorXWall = mapSquareX + wallX;
            floorYWall = mapSquareY;
          }
          else/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */
          {
            floorXWall = mapSquareX + wallX;
            floorYWall = mapSquareY + 1.0;
          }

          double distWall, distPlayer, currentDist;

          distWall = totalRayDist;
          distPlayer = 0.0;
          if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows
          //draw the floor from drawEnd to the bottom of the screen
          for(int y = drawEnd; y < h; y++)
          {
            currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead

            double weight = (currentDist - distPlayer) / (distWall - distPlayer);

            double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
            double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

            int floorTexX, floorTexY;
            floorTexX = int(currentFloorX * mapWidth) % mapWidth;
            floorTexY = int(currentFloorY * mapWidth) % mapWidth;

            //floor
            buffer[x][y] = (texture[floorTex][mapWidth * floorTexY + floorTexX]);// >> 1) & 8355711;
            //ceiling (symmetrical!)
            buffer[x][h - y] = (texture[cielingTex][mapWidth * floorTexY + floorTexX] >> 1) & 8355711;
          }
        }
        //gameObject CASTING

        //sort sprites from far to close
        for(int i = 0; i < numGameObjects; i++)
        {
          gameObjectOrder[i] = i;
          gameObjectDistance[i] = ((posX - gameObject[i].position.x) * (posX - gameObject[i].position.x) + (posY - gameObject[i].position.y) * (posY - gameObject[i].position.y)); //sqrt not taken, unneeded
        }
        gameObjectSort(gameObjectOrder, gameObjectDistance, numGameObjects);

        //after sorting the gameObjects, do the projection and draw them
        for(int i = 0; i < numGameObjects; i++)
        {
          //translate gameObject position to relative to camera
          double gameObjectX = gameObject[gameObjectOrder[i]].position.x - posX;
          double gameObjectY = gameObject[gameObjectOrder[i]].position.y - posY;

          //transform gameObject with the inverse camera matrix
          // [ cameraPlaneX   dirX ] -1                                       [ dirY      -dirX ]
          // [               ]       =  1/(cameraPlaneX*dirY-dirX*cameraPlaneY) *   [                 ]
          // [ cameraPlaneY   dirY ]                                          [ -cameraPlaneY  cameraPlaneX ]

          double invDet = 1.0 / (cameraPlaneX * dirY - dirX * cameraPlaneY); //required for correct matrix multiplication

          double transformX = invDet * (dirY * gameObjectX - dirX * gameObjectY);
          double transformY = invDet * (-cameraPlaneY * gameObjectX + cameraPlaneX * gameObjectY); //this is actually the depth inside the screen, that what Z is in 3D

          int gameObjectScreenX = int((w / 2) * (1 + transformX / transformY));

          //parameters for scaling and moving the gameObjects
          #define uDiv 1
          #define vDiv 1
          #define vMove 10
          int vMoveScreen = int(vMove / transformY);

          //calculate height of the gameObject on screen
          int gameObjectHeight = abs(int(h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
          //calculate lowest and highest pixel to fill in current stripe
          int drawStartY = -gameObjectHeight / 2 + h / 2 + vMoveScreen;
          if(drawStartY < 0) drawStartY = 0;
          int drawEndY = gameObjectHeight / 2 + h / 2 + vMoveScreen;
          if(drawEndY >= h) drawEndY = h - 1;

          //calculate width of the gameObject
          int gameObjectWidth = abs( int (h / (transformY))) / uDiv;
          int drawStartX = -gameObjectWidth / 2 + gameObjectScreenX;
          if(drawStartX < 0) drawStartX = 0;
          int drawEndX = gameObjectWidth / 2 + gameObjectScreenX;
          if(drawEndX >= w) drawEndX = w - 1;

          //loop through every vertical stripe of the gameObject on screen
          for(int stripe = drawStartX; stripe < drawEndX; stripe++)
          {
            int texX = int(256 * (stripe - (-gameObjectWidth / 2 + gameObjectScreenX)) * mapWidth / gameObjectWidth) / 256;

            if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
            for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
            {
              int d = (y-vMoveScreen) * 256 - h * 128 + gameObjectHeight * 128; //256 and 128 factors to avoid floats
              int texY = ((d * mapWidth) / gameObjectHeight) / 256;
              Uint32 colour = texture[gameObject[gameObjectOrder[i]].sprite][mapWidth * texY + texX]; //get current colour from the texture
              if((colour & 0x00FFFFFF) != 0)buffer[stripe][y] = colour; //paint pixel if it isn't black, black is the invisible colour
            }
          }
        }
        for(int x = 0; x < 15; x++)
                {
                    for(int y = 0; y < 15; y++)
                    {
                        int colour = crosshairTexture[15 * y + x];
                        if(colour != 0)
                        {
                            buffer[(screenWidth/2 - 8 ) + x][(screenHeight/2 - 8 ) + y] = colour;

                        }
                    }
                }
        drawBuffer(buffer[0]);
        for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) buffer[x][y] = 0; //clear the buffer instead of cls()
        print(1.0 / frameTime); //FPS counter

        if (keyDown(SDLK_END)){
            print(playerPos.x, 0, 20);
            print(playerPos.y, 0, 30);
        }


        redraw();
        readKeys();

        //move forward if no wall in front of you
        if (keyDown(SDLK_w))
        {
            if( worldMap[int(posX + dirX * moveSpeed * frameTime)][int(posY)] == false )
            {
                posX += dirX * moveSpeed * frameTime;
            }
            if( worldMap[int(posX)][int(posY + dirY * moveSpeed * frameTime)] == false )
            {
                posY += dirY * moveSpeed * frameTime;
            }
        }
        //move backwards if no wall behind you
        if (keyDown(SDLK_s))
    {
            if( worldMap[int(posX - dirX * moveSpeed * frameTime)][int(posY)] == false )
            {
                posX -= dirX * moveSpeed * frameTime;
            }
            if( worldMap[int(posX)][int(posY - dirY * moveSpeed * frameTime)] == false )
            {
                posY -= dirY * moveSpeed * frameTime;
            }
        }
        //rotate to the right
        if (keyDown(SDLK_d))
        {
          //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed * frameTime) - dirY * sin(-rotSpeed * frameTime);
            dirY = oldDirX * sin(-rotSpeed * frameTime) + dirY * cos(-rotSpeed * frameTime);
            double oldPlaneX = cameraPlaneX;
            cameraPlaneX = cameraPlaneX * cos(-rotSpeed * frameTime) - cameraPlaneY * sin(-rotSpeed * frameTime);
            cameraPlaneY = oldPlaneX * sin(-rotSpeed * frameTime) + cameraPlaneY * cos(-rotSpeed * frameTime);
        }
        //rotate to the left
        if (keyDown(SDLK_a))
        {
          //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed * frameTime) - dirY * sin(rotSpeed * frameTime);
            dirY = oldDirX * sin(rotSpeed * frameTime) + dirY * cos(rotSpeed * frameTime);
            double oldPlaneX = cameraPlaneX;
            cameraPlaneX = cameraPlaneX * cos(rotSpeed * frameTime) - cameraPlaneY * sin(rotSpeed * frameTime);
            cameraPlaneY = oldPlaneX * sin(rotSpeed * frameTime) + cameraPlaneY * cos(rotSpeed * frameTime);
        }
        if (keyDown(SDLK_q))
        {
            double leftDirX = dirX;
            double leftDirY = dirY;
            double leftRot = 1.571;
            leftDirX = leftDirX * cos(leftRot) - leftDirY * sin(leftRot);
            leftDirY = dirX * sin(leftRot) + leftDirY * cos(leftRot);
            if ( worldMap[int(posX + leftDirX * moveSideSpeed * frameTime)][int(posY)] == false )
            {
                    posX += leftDirX * moveSideSpeed * frameTime;
            }
            if ( worldMap[int(posX)][int(posY + leftDirY * moveSideSpeed * frameTime)] == false )
            {
                    posY += leftDirY * moveSideSpeed * frameTime;
            }
        }
            // strafe right if no block to the right
        if (keyDown(SDLK_e))
        {
            double rightDirX = dirX;
            double rightDirY = dirY;
            double rightRot = 1.571;
            rightDirX = rightDirX * cos(rightRot) - rightDirY * sin(rightRot);
            rightDirY = dirX * sin(rightRot) + rightDirY * cos(rightRot);
            if ( worldMap[int(posX - rightDirX * moveSideSpeed * frameTime)][int(posY)] == false )
            {
                posX -= rightDirX * moveSideSpeed * frameTime;
            }
            if ( worldMap[int(posX)][int(posY - rightDirY * moveSideSpeed * frameTime)] == false )
            {
                posY -= rightDirY * moveSideSpeed * frameTime;
            }
        }

        if (keyDown(SDLK_LSHIFT))
        {
            moveSpeed = oldMoveSpeed * 2;
            moveSideSpeed = oldMoveSideSpeed * 2;
        }
        else
        {
            moveSpeed = oldMoveSpeed;
            moveSideSpeed = oldMoveSideSpeed;
        }

        if (keyPressed(SDLK_KP_MINUS) && (levelNo > 1))
        {
            Vector2D p = changeLevel(levelNo-1);
            posX = p.x;
            posY = p.y;
            gameObject = fileLoader::getGameObjectsFromPrefabs(levelNo);
            numGameObjects = gameObject.size();
        }

        if (keyPressed(SDLK_KP_PLUS) && (levelNo <= noOfLevels))
        {
            Vector2D p = changeLevel(levelNo+1);
            posX = p.x;
            posY = p.y;
            gameObject = fileLoader::getGameObjectsFromPrefabs(levelNo);
            numGameObjects = gameObject.size();
        }

        // run player script
        script.x = posX;
        script.y = posY;
        script.parse();
        posX = script.x;
        posY = script.y;
      }
    }
void gameObjectSort(int* order, double* dist, int amount)
    {
        int gap = amount;
        bool swapped = false;
        while(gap > 1 || swapped)
        {
            //shrink factor 1.3
            gap = (gap * 10) / 13;
            if(gap == 9 || gap == 10) gap = 11;
            if (gap < 1) gap = 1;
            swapped = false;
            for (int i = 0; i < amount - gap; i++)
            {
                int j = i + gap;
                if (dist[i] < dist[j])
                {
                std::swap(dist[i], dist[j]);
                std::swap(order[i], order[j]);
                swapped = true;
                }
            }
        }
    }


