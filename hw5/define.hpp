#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

#define BACKGROUND_COLOR 119, 181, 254, 255
#define MENU_BACKGRUND Color::White
#define BUTTON_COLOR Color::Cyan
#define BUTTON_TEXT_COLOR Color::Black

enum Collision
{
    up,
    down,
    right,
    left
};

struct Collision_report
{
    vector<Collision> floor;
    vector<Collision> enemy;
    vector<Collision> player;
    vector<Collision> baby;
    vector<Collision> coin;
};

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 25;
const int MENU_FONT_SIZE = 25;
const float VIEW_RATIO_WIDTH = (float)3 / 8;
const float VIEW_RATIO_HEIGHT = (float)2 / 3;

const int BLOCK_SIZE = 100;
//!!WARNING image size should set
const int IMG_FLOOR_SIZE = 100;
const int IMG_COIN_SIZE = 100;
const int IMG_DIMEND_SIZE = 100;
const int IMG_PLAYER_SIZE = 85;

const float FLOOR_SCALE = BLOCK_SIZE * 1.0 / IMG_FLOOR_SIZE;
const float COIN_SCALE = BLOCK_SIZE * 1.0 / IMG_COIN_SIZE;
const float DIMEND_SCALE = BLOCK_SIZE * 1.0 / IMG_DIMEND_SIZE;
const float PLAYER_SCALE = BLOCK_SIZE * 1.0 / IMG_PLAYER_SIZE;

const string FLOOR_MAP_SYMBOLE = "#";
const string PLAYER_MAP_SYMBOLE = "P";

const string ADDR_ASSSETS = "./assets/";
const string ADDR_FONT = ADDR_ASSSETS + "arial.ttf";
const string ADDR_LEVELS = ADDR_ASSSETS + "levels/";
const string ADDR_IMG = ADDR_ASSSETS + "img/";
const string ADDR_LEVEL_1 = ADDR_LEVELS + "level1.map";
const string ADDR_FLOOR = ADDR_IMG + "floor.png";
const string ADDR_PLAYER = ADDR_IMG + "player.png";
const string ADDR_PLAYER_FLIP=ADDR_IMG + "player_flip.png";
const int MOVE_RIGHT = 1;
const int MOVE_LEFT = 2;
const int MOVE_UP = 3;
const int GO_DOWN = 4;
const int JUMP_HIGH = 3;
const int TURTLE_HEALTH = 3;
const int ENEMY_HEALTH = 2;
const char FIRST_ENEMY_SYMBOL = 'e';
const char SECOND_ENEMY_SYMBOL = 'm';
const char TURTLE_SYMBOL = 'p';
const char SPACE_SYMBOL = ' ';
const char DIAMON_SYMBOL = '^';
const char STAR_SYMBOL = '*';
const int STAR_SCORE = 1;
const int DIAMOND_SCORE = 2;
const int WITHOUT_ENCOUNTER_FLOOR = 0;
const int FLIP_TO_RIGHT=-1;
const int FLIP_TO_LEFT=1;

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;
