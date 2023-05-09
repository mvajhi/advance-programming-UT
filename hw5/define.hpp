#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

// menu
const Color BUTTON_COLOR(Color(255, 255, 255, 150));
const Color BUTTON_HOVER_COLOR(Color(150, 10, 100, 150));
const Color BUTTON_TEXT_COLOR(Color::Black);
const float BUTTON_WIDTH = 200;
const float BUTTON_HEIGHT = 50;
const Vector2f FIRST_BUTTON_POSITION(0, 200);
const Vector2f BUTTON_SEPRATE(0, 30);
const int MENU_FONT_SIZE = 35;
const Vector2f MENU_POS(300.f, 200.f);

const int START_MENU = 0;
const int LEVEL_MENU = 1;
const int SHOW_GAME = 2;
const int PAUSE_MENU = 3;
const int WIN_MENU = 4;
const int DEFAULT_PAGE = START_MENU;

const int NO_INDEX = -1;
const int EMPTY = -1;
const int LEVEL_1 = 1;

// file address
const string ASSETS = "./assets";
const string IMG = ASSETS + "/img";
const string MAPS = ASSETS + "/levels";
const string MAP_L1 = MAPS + "/level1.map";
const string MAP_L2 = MAPS + "/level2.map";
const string PLAYER_IMG = IMG + "/player.png";
const string BOY_IMG = IMG + "/boy.png";
const string FLOOR_IMG = IMG + "/floor.png";
const string DIAMOND_IMG = IMG + "/diamond.png";
const string STAR_IMG = IMG + "/star.png";
const string PORTAL_IMG = IMG + "/portal.png";
const string PAUSE_IMG = IMG + "/pause.png";
const string BOY_TURTLE_IMG = IMG + "/boy_turtle.png";
const string BACKGROUND_IMG = IMG + "/back.jpg";
const string ADDR_FONT = ASSETS + "/font.ttf";
const string ADDR_FONT_2 = ASSETS + "/arial.ttf";

// map guide
const string FLOOR_MAP_SYMBOLE = "#";
const string PLAYER_MAP_SYMBOLE = "P";
const string DIAMOND_SYMBOL = "^";
const string STAR_SYMBOL = "*";
const string BOY_TURTLE_SYMBOL = "@";

// move direct
const int UP = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN = 3;
const int IDL = 4;
const int NO_COLLISION = -1;

// scale and size
const float BLOCK_SIZE = 50;
//!!WARNING image size should set
const int IMG_FLOOR_SIZE = 100;
const int IMG_PAUSE_SIZE = 390;
const int IMG_DIAMOND_SIZE = 95;
const int IMG_STAR_SIZE = 110;
const int IMG_PORTAL_SIZE = 134;
const int IMG_PLAYER_SIZE = 100;
const int IMG_PLAYER_SIZE_H = 100;
const int IMG_PLAYER_SIZE_W = 95;
const int IMG_BOY_SIZE_W = 102;
const int IMG_BOY_SIZE_H = 103;
const int IMG_BOY_TURTLE = 156;

const float PAUSE_SCALE = BLOCK_SIZE * 1.0 / IMG_PAUSE_SIZE;
const float FLOOR_SCALE = BLOCK_SIZE * 1.0 / IMG_FLOOR_SIZE;
const float STAR_SCALE = BLOCK_SIZE * 1.0 / IMG_STAR_SIZE;
const float DIAMOND_SCALE = BLOCK_SIZE * 1.0 / IMG_DIAMOND_SIZE;
const float PORTAL_SCALE = BLOCK_SIZE * 1.0 / IMG_PORTAL_SIZE;
const float PLAYER_SCALE_X = BLOCK_SIZE * 1.0 / IMG_PLAYER_SIZE_H;
const float PLAYER_SCALE_Y = BLOCK_SIZE * 1.0 / IMG_PLAYER_SIZE_W;
const float BOY_SCALE_X = BLOCK_SIZE * 1.0 / IMG_BOY_SIZE_W;
const float BOY_SCALE_Y = BLOCK_SIZE * 1.0 / IMG_BOY_SIZE_H;
const float BOY_TURTLE_SCALE = BLOCK_SIZE * 1.0 / IMG_BOY_TURTLE;

// animation
const float ANIME_PLAYER_SPEED = 0.02;
const int PLAYER_IDL_LEFT = IMG_PLAYER_SIZE_H * 3;
const int PLAYER_IDL_RIGHT = IMG_PLAYER_SIZE_H * 7;

// movement
const float DEFAULT_VELOCITY_MAX = 15 * BLOCK_SIZE / 100;
const float DEFAULT_VELOCITY_MIN = 1 * BLOCK_SIZE / 100;
const float DEFAULT_ACCELERATION = 5 * BLOCK_SIZE / 100;
const float DEFAULT_GRAVITY = 1 * BLOCK_SIZE / 100;
const float DEFAULT_DRAG = 0.7;
const float EPSILON = 0.009;

// scores
const int DEFAULT_HELTH = 3;
const int DEFAULT_SCORE = 0;
const int DIAMOND_SCORE = 2;
const int STAR_SCORE = 1;

// UI
const int FONT_SIZE = 35;
const Color FONT_COLOR(Color::White);
const Color GAME_BACK_COLOR(Color(119, 181, 254, 255));

// window
const int WINDOW_W = 900;
const int WINDOW_H = 600;
const int MAX_FRAME = 60;
const Vector2f SCORE_UI_POS(0, -WINDOW_H / 2 + BLOCK_SIZE / 2);
const Vector2f HEALTH_UI_POS(WINDOW_W / 2 - BLOCK_SIZE * 3 / 2, -WINDOW_H / 2 + BLOCK_SIZE / 2);
