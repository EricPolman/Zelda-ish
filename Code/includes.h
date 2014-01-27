#pragma once
#define MAP_WIDTH 4096
#define MAP_HEIGHT 3072
#define ROOM_WIDTH 512
#define ROOM_HEIGHT 512
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define ROWS_OF_ROOMS MAP_HEIGHT / ROOM_HEIGHT
#define COLS_OF_ROOMS MAP_WIDTH / ROOM_WIDTH
#define ROWS_OF_TILES ROOM_HEIGHT / TILE_HEIGHT
#define COLS_OF_TILES ROOM_WIDTH / TILE_WIDTH
#define SCROLL_SPEED 1.5f
#define FRAMES_PER_SECOND 0.016667

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "SDL.h"
#include "sdl_mixer.h"
#include <random>
#include <map>
#include <queue>
#include <sstream>
#include "Vector2.h"
#include "Stats.h"
#include "SoundManager.h"
#include "InputManager.h"
