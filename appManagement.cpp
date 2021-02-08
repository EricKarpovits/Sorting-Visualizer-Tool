#include "declarations.h"

/// Constructor
AppManagement::AppManagement(Allegro &allegro, Sorting &sorting) : allegro(allegro), sorting(sorting) {

    continuePlaying = true;
}

/**
* Main function of the game which loops
* It allows every game mode to run and the user to play the game
**/
void AppManagement::play() {

    // Declare variables and create an event
    GAMEMODE gameMode = allegro.getGameMode();

    ALLEGRO_EVENT &event = allegro.getEvent();
    ALLEGRO_EVENT_QUEUE *evQueue = allegro.getEventQueue();
    al_wait_for_event(evQueue, &event);

    // Where all the game modes are performed
    switch (gameMode) {

        case BUBBLE_SORT:

            sorting.bubbleSort();
            break;

        case SELECTION_SORT:

            sorting.selectionSort();
            break;

        case MERGE_SORT:

            sorting.mergeMain();
            break;

        case BINARY_SEARCH:

            sorting.binarySearchMain();
            break;

        // These cases have nothing special, they just print out text and have buttons.
        // Included so that there would be no warnings
        case START:
        case RESET:
        case CREDITS:
        case INSTRUCTIONS:
        case MAIN_MENU:
            break;
    }
    // Resets key properties after one of these gamemodes were chosen
    if (gameMode == BINARY_SEARCH || gameMode == RESET || gameMode == MERGE_SORT || gameMode == SELECTION_SORT || gameMode == BUBBLE_SORT) {
        resetEverything();
        al_flush_event_queue(evQueue);
    }

    // A method which draws all the buttons for the specific gamemodes
    allegro.drawMain(sorting.getAllValues(), sorting.getTrackers());

    // Checks if the user closed the display
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

        continuePlaying = false;

    // Check mouse down events
    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

        // Check which buttons was clicked
        allegro.playButtonClickSound();
        // Checks which button if any if the mouse was clicked
        allegro.checkButtonAction();
        allegro.checkButtonState(continuePlaying);

    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

        allegro.checkButtonAction();

    // Check mouse movement event
    } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

        // Check if the button needs to be filled in if the mouse is hovering over it
        allegro.checkButtonAction();
    }
}

// A method that resets everything
void AppManagement::resetEverything() {

    GAMEMODE gameMode = allegro.getGameMode();

    // Sets game mode to START, button setup for game mode START and reset everything else
    if (gameMode == RESET) {
        sorting.setDataToOriginal();
        sorting.resetTrackers();
        allegro.resetSearchTarget();
    }
    allegro.setGameMode(START);
    allegro.buttonSetup();
}

