#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

// Libraries
#include <iostream>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;
// For the high precison timer
using namespace std::chrono;

#include "string.h"
#include "apvector.h"

// Structs for buttons and screen positions for disks
struct SCREEN_POSITIONS {

    int xTopLeftCorner;
    int yTopLeftCorner;
    int xBottonRightCorner;
    int yBottomRightCorner;
};

struct BUTTON {

    int upperLeftXCoordinate, upperLeftYCoordinate, lowerRightXCoordinate, lowerRightYCoordinate;
    bool clicked;
    bool filled;
    string buttonTitle;
    bool largeText;
    ALLEGRO_COLOR colour;
};

struct TRACKERS {

    int numberOfComparisons;
    int numberOfMoves;
    double timeDuration;
    int redIndex;
    int rightBlackIndex;
    int leftBlackIndex;
    int middleGreenIndex;
    int numberOfRests;
    bool sorted;
    apvector <int> greenIndex;
};

// All the gamemodes in one nice enclosure
enum GAMEMODE {

    MAIN_MENU,
    INSTRUCTIONS,
    CREDITS,
    START,
    RESET,
    BUBBLE_SORT,
    SELECTION_SORT,
    MERGE_SORT,
    BINARY_SEARCH
};

// Colours
#define BLUE        al_map_rgb(51, 51, 255)
#define WHITE       al_map_rgb(255, 255, 255)
#define BLACK       al_map_rgb(0, 0, 0)
#define LIGHT_BLACK al_map_rgb(105, 105, 105)
#define ORANGE      al_map_rgb(255, 128, 0)
#define LIGHT_BLUE  al_map_rgb(153, 187, 255)
#define RED         al_map_rgb(255, 51, 51)
#define GREEN       al_map_rgb(51, 255, 51)
#define YELLOW      al_map_rgb(255, 255, 0)

/******** Constants *************/

// Allegro constants
const int NUMBER_OF_MUSIC_SAMPLES = 2;
const int SCREEN_WIDTH = 1150;
const int SCREEN_HEIGHT = 700;
const int FPS = 60;
const int LARGE_FONT_SIZE = 25;
const int SMALL_FONT_SIZE = 18;

// Sorting constants
const int ARRAY_SIZE = 150;
const int INDEX_ZERO = 0;
const double SELECTION_SORT_DELAY = 0.05;
const double MERGE_SORT_DELAY = 0.025;
const double BINARY_SEARCH_DELAY = 1.25;
const double BINARY_SEARCH_NOT_FOUND_DELAY = 3.0;
const double DRAW_FINISHED_SORT_DELAY = 0.01;

/// Button type - This was very crutial and I am glad I did it as it allowed me to keep track of what each button does
/// and so that I did not have remember what each button does
// In game buttons
const int BUTTON_BUBBLE = 0;
const int BUTTON_SELECTION = 1;
const int BUTTON_MERGE = 2;
const int BUTTON_RESET = 3;
const int BUTTON_MAIN_MENU = 4;
const int BUTTON_IN_GAME_QUIT = 5;
const int BUTTON_PLUS_ONE = 6;
const int BUTTON_MINUS_ONE = 7;
const int BUTTON_PLUS_TEN = 8;
const int BUTTON_MINUS_TEN = 9;
const int BUTTON_BINARY_SEARCH = 10;

// Main menu buttons
const int BUTTON_START = 0;
const int BUTTON_INSTRUCTIONS = 1;
const int BUTTON_CREDITS = 2;
const int BUTTON_MAIN_MENU_QUIT = 3;

// Credits and instructions buttons
const int BUTTON_CREDITS_MAIN_MENU = 0;
const int BUTTON_CREDITS_START = 1;
const int BUTTON_CREDITS_QUIT = 2;

/// Error code constants - allows for easier debugging and keeps program professional and allows the user to
/// to know what went wrong
const int ERROR_DISPLAY = -1;
const int ERROR_LOAD_BITMAP = -2;
const int ERROR_IMG_ADDON = -3;
const int ERROR_PRIMATIVE_ADDON = -4;
const int ERROR_MOUSE_ADDON = -5;
const int ERROR_FPSTIMER = -6;
const int ERROR_SOLVER_TIMER = -7;
const int ERROR_EVENT_QUEUE = -8;
const int ERROR_ARIAL_FONT = -9;
const int ERROR_SMALL_ARIAL_FONT = -10;
const int ERROR_FONT_ADDON = -11;
const int ERROR_TTF_ADDON = -12;
const int ERROR_ALLEGRO = -13;
const int ERROR_IMAGE_ADDON = -14;
const int ERROR_INSTALL_AUDIO = -15;
const int ERROR_ACODEC_ADDON = -16;
const int ERROR_MUSIC_FILE_GAMEMUSIC = -17;
const int ERROR_MUSIC_FILE_BUTTONCLICK = -18;

/** Class header files **/
#include "allegro.h"
#include "sorting.h"
#include "appManagement.h"

#endif // DECLARATIONS_H_INCLUDED
