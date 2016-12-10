#Instructions on how to use the Player:

####Controls:
W = Walk forward

S = Walk backwards

A = Rotate left

D = Rotate right

Q = Strafe left

E = Strafe right

LSHIFT = Sprint modifier (works with W, S, E and Q)

LCTRL = Crouch (Now broken)

END = Debug screen

Numpad+ = Change level +1 (So would change from level 1 to level 2)

Numpad- = Change level -1 (You get the idea.)




###TEXTURES

- Go into gameData.ini and change texturesUsed to however many you are using. WARNING: texturesUsed must always have a value equal to or above the number of files in data/Textures. The player will not work otherwise.
- Add textures to the Data/textures folder, named '1.png', '2.png', etc. Must be .png format and must be 64x64 pixels in size.
- When painting a level, the texture you use for the wall depends on the R value of the RGB of the colour you are using. 254 is texture 0, 253 is texture 1, so if you had seven textures and wanted to paint a wall that used the seventh texture, you'd use the pencil tool with a colour RGB value of (247,X,Y). The value of G and B in the RGB values do not matter.


###LEVELS

- To create a level, add a 64x64 .png file to Data/levels named 'level1.png', 'level2.png', whatever number level you are making.
- Open gameData.ini and change noOfLevels to however many desired.
- For every level you add, you must add (underneath screenHeight):

`
[LevelX]

texture=Data/Levels/levelX.png

playerX= __

playerY= __
`

where X corresponds to the level number you are dealing with. Then, player X and Y starting coordinates can be set to anything over 0 and less than 64. 

- Use the instructions above in the 'TEXTURES' section to draw walls using the certain textures.


### SPRITES

- Cannot be changed via a .ini right now. To add a new sprite, you must drop the 64x64 sprite .png image into the same folder as textures and the number you give it in the Textures folder you must also give it in the code, as well as its X and Y coordinates.


### POSITION, MOVEMENT SPEED, ROTATION SPEED, SCREEN RESOLUTION

- Go into gameData.ini and change values to desired values.
- 

Note: In order to access, change and compile the code, it is assumed the Tutorial.md in the project root is followed.
