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

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

const int BLOCK_SIZE = 100;
//!!WARNING image size should set
const int IMG_FLOOR_SIZE = 100;
const float FLOOR_SCALE = BLOCK_SIZE * 1.0 / IMG_FLOOR_SIZE;

const string FLOOR_MAP_SYMBOLE = "#";

const string ADDR_ASSSETS = "./assets/";
const string ADDR_LEVELS = ADDR_ASSSETS + "levels/";
const string ADDR_IMG = ADDR_ASSSETS + "img/";
const string ADDR_LEVEL_1 = ADDR_LEVELS + "level1.map";
const string ADDR_FLOOR = ADDR_IMG + "floor.png";