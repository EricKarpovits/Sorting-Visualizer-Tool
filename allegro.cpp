#include "declarations.h"

// A method that releases the memory that was allocated for allegro
// This function exits everything for no memory loss
void Allegro::releaseMemory() {

    //Release the bitmap data and exit with no errors
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(arial);
	al_destroy_font(smallArial);
	al_destroy_sample(gameMusic);
	al_destroy_sample(buttonClick);
	al_destroy_bitmap(background);
}

// Constant passed by reference for maximum efficienty
void Allegro::drawMain(const apvector <int> &currentRectangleValues, const TRACKERS &trackers) {

    prepareForDrawing();

    printAllText(trackers);
    drawButtons();

    if (gameMode != MAIN_MENU && gameMode != CREDITS && gameMode != INSTRUCTIONS) {
        displayRectangles(currentRectangleValues, trackers);
    }
    al_flip_display();
}

// This is the main method to display the rectangles
void Allegro::displayRectangles(const apvector <int> &currentRectangleValues, const TRACKERS &trackers) {

    // Declare the ap vectors for screen positions and the current rectangle values
    apvector <SCREEN_POSITIONS> screenPositions = calculateScreenPositionsForRectangles(currentRectangleValues);

    // Gets the rectangles colour
    apvector <ALLEGRO_COLOR> rectangleColours = getRectangleColours(currentRectangleValues, trackers);

    // Draws all the rectangles
    drawRectangles(screenPositions, currentRectangleValues, rectangleColours);
}

apvector <ALLEGRO_COLOR> Allegro::getRectangleColours(const apvector <int> &currentRectangleValues, const TRACKERS &trackers) {

    int arrayLength = currentRectangleValues.length();
    apvector <ALLEGRO_COLOR> rectangleColours(arrayLength);

    for (int i = 0; i < arrayLength; i++) {
        if (i == trackers.redIndex) {
            rectangleColours[i] = RED;
        } else if (i == trackers.leftBlackIndex || i == trackers.rightBlackIndex) {
            rectangleColours[i] = BLACK;
        } else if (i == trackers.middleGreenIndex || i == trackers.greenIndex[i]) {
            rectangleColours[i] = GREEN;
        } else if ((i < trackers.leftBlackIndex || (i > trackers.rightBlackIndex && trackers.rightBlackIndex != -1)) &&
                   (gameMode == BINARY_SEARCH || gameMode == START)) {
            rectangleColours[i] = LIGHT_BLACK;
        } else {
            rectangleColours[i] = WHITE;
        }
    }
    return rectangleColours;
}

// This method prepares the background
void Allegro::prepareForDrawing() {

    al_clear_to_color(LIGHT_BLUE);

    if (gameMode == MAIN_MENU) {
        al_draw_bitmap(background, 0, 0, 0);
    }
}

// This method calculates the screen positions
apvector<SCREEN_POSITIONS> Allegro::calculateScreenPositionsForRectangles(const apvector<int> &currentRectangleValues) {

    // Declare + initialize variables
    int arrayLength = currentRectangleValues.length();
    int rectangleWidth = (SCREEN_WIDTH - 100) / arrayLength;
    int rectangleHeight = 0;
    // An apvector of a struct for screen coordinates
    apvector<SCREEN_POSITIONS> screenPositions(arrayLength);

    // Iterate through each value
    for (int i = 0; i < arrayLength; i++) {

        rectangleHeight = currentRectangleValues[i] * ((double)(SCREEN_HEIGHT - 200) / arrayLength);

        screenPositions[i].yBottomRightCorner = SCREEN_HEIGHT - 50;
        screenPositions[i].yTopLeftCorner = screenPositions[i].yBottomRightCorner - rectangleHeight;

        screenPositions[i].xTopLeftCorner = 50 + (rectangleWidth * i);
        screenPositions[i].xBottonRightCorner = screenPositions[i].xTopLeftCorner + rectangleWidth;

    }

    return screenPositions;
}

void Allegro::drawRectangles(const apvector<SCREEN_POSITIONS> &screenPositions, const apvector<int> &currentRectangleValues,
                             const apvector <ALLEGRO_COLOR> rectangleColours) {

    for (int i = 0; i < currentRectangleValues.length(); i++) {
        al_draw_filled_rectangle(screenPositions[i].xTopLeftCorner, screenPositions[i].yTopLeftCorner,
                                 screenPositions[i].xBottonRightCorner, screenPositions[i].yBottomRightCorner, rectangleColours[i]);
        // Draw rectangle border
        al_draw_rectangle(screenPositions[i].xTopLeftCorner, screenPositions[i].yTopLeftCorner,
                                 screenPositions[i].xBottonRightCorner, screenPositions[i].yBottomRightCorner, BLACK, 1.0);
    }
}

/********************* Buttons ********************************************/

// This function setups the buttons properies based on the game mode the user is in
void Allegro::buttonSetup() {

    // Switch the game mode so that the buttons are set up in the appropriate game mode
    switch (gameMode) {

        case RESET:
        case START:
        case MERGE_SORT:
        case BUBBLE_SORT:
        case SELECTION_SORT:
        case BINARY_SEARCH:

            // Set the vector size
            button.resize(11);
            // This modular method allows me to set all the button properties in 1 line for all types of button
            /// Being able to reuse for multiple projects, saving me a lot of time
            setButtonProperties(BUTTON_BUBBLE, 25, 25, 175, 70, false, "Bubble Sort", WHITE);
            setButtonProperties(BUTTON_SELECTION, 25, 95, 175, 140, false, "Selection Sort", WHITE);
            setButtonProperties(BUTTON_MERGE, 200, 25, 350, 70, false, "Merge Sort", WHITE);
            setButtonProperties(BUTTON_MAIN_MENU, SCREEN_WIDTH - 350, 25, SCREEN_WIDTH - 200, 70, false, "Main Menu", ORANGE);
            setButtonProperties(BUTTON_IN_GAME_QUIT, SCREEN_WIDTH - 175, 95, SCREEN_WIDTH - 25, 140, false, "Quit", RED);
            setButtonProperties(BUTTON_RESET, SCREEN_WIDTH - 175, 25, SCREEN_WIDTH - 25, 70, false, "Reset", YELLOW);
            setButtonProperties(BUTTON_PLUS_ONE, SCREEN_WIDTH / 2 + 135, 95, SCREEN_WIDTH / 2 + 185, 140, false, "+1", GREEN);
            setButtonProperties(BUTTON_PLUS_TEN, SCREEN_WIDTH / 2 + 80, 95, SCREEN_WIDTH / 2 + 130, 140, false, "+10", GREEN);
            setButtonProperties(BUTTON_MINUS_ONE, SCREEN_WIDTH / 2 - 185, 95, SCREEN_WIDTH / 2 - 135, 140, false, "-1", RED);
            setButtonProperties(BUTTON_MINUS_TEN, SCREEN_WIDTH / 2 - 130, 95, SCREEN_WIDTH / 2 - 80, 140, false, "-10", RED);
            setButtonProperties(BUTTON_BINARY_SEARCH, SCREEN_WIDTH / 2 - 75, 25, SCREEN_WIDTH / 2 + 75, 70, false, "Search", WHITE);

            break;

        case MAIN_MENU:

            button.resize(4);
            setButtonProperties(BUTTON_START, SCREEN_WIDTH / 3, 150,
                                SCREEN_WIDTH / 3 * 2, 250, true, "START", GREEN);
            setButtonProperties(BUTTON_INSTRUCTIONS, SCREEN_WIDTH / 3, 285,
                                SCREEN_WIDTH / 3 * 2, 385, true, "INSTRUCTIONS", ORANGE);
            setButtonProperties(BUTTON_CREDITS, SCREEN_WIDTH / 3, 420,
                                SCREEN_WIDTH / 3 * 2, 520, true, "CREDITS", ORANGE);
            setButtonProperties(BUTTON_MAIN_MENU_QUIT, SCREEN_WIDTH / 3, 555,
                                SCREEN_WIDTH / 3 * 2, 655, true, "QUIT", RED);
            break;

        case INSTRUCTIONS:
        case CREDITS:

            button.resize(3);
            setButtonProperties(BUTTON_CREDITS_MAIN_MENU, SCREEN_WIDTH / 10 + 25, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 25, SCREEN_HEIGHT - 25, true, "MAIN MENU", YELLOW);

            setButtonProperties(BUTTON_CREDITS_START, SCREEN_WIDTH / 10 + 325, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 325, SCREEN_HEIGHT - 25, true, "START", GREEN);

            setButtonProperties(BUTTON_CREDITS_QUIT, SCREEN_WIDTH / 10 + 625, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 625, SCREEN_HEIGHT - 25, true, "QUIT", RED);
            break;
    }

    // Reset the button booleans
    for (int i = 0; i < button.length(); i++) {
        button[i].clicked = false;
        button[i].filled = false;
    }
}

// This reusable function takes the properties from the button setup and allocates them to each specific button
// essentially a modifier method
void Allegro::setButtonProperties(int buttonNumber, int upperLeftX, int upperLeftY, int lowerRightX,
                                  int lowerRightY, bool largeText, string buttonTitle, ALLEGRO_COLOR buttonColour) {

	button[buttonNumber].upperLeftXCoordinate = upperLeftX;
	button[buttonNumber].upperLeftYCoordinate = upperLeftY;
	button[buttonNumber].lowerRightYCoordinate = lowerRightY;
	button[buttonNumber].lowerRightXCoordinate = lowerRightX;
	button[buttonNumber].largeText = largeText;
	button[buttonNumber].buttonTitle = buttonTitle;
	button[buttonNumber].colour = buttonColour;

}

/// This method draws the buttons
// The button is either drawn with just the outline or filled in, based on the users mouses position
void Allegro::drawButtons() {

    for (int i = 0; i < button.length(); i++) {

        // Based on if the bool is true or not either it draws the box filled or just the outline
        if (!button[i].filled) {

            al_draw_rectangle(button[i].upperLeftXCoordinate, button[i].upperLeftYCoordinate,
                              button[i].lowerRightXCoordinate, button[i].lowerRightYCoordinate, button[i].colour, 3);

        } else {

            al_draw_filled_rectangle(button[i].upperLeftXCoordinate, button[i].upperLeftYCoordinate,
                                    button[i].lowerRightXCoordinate, button[i].lowerRightYCoordinate, button[i].colour);
        }

        // Initialize the text font and size based on the buttons properties
        ALLEGRO_FONT *tempFont = NULL;
        int tempFontSize = 0;

        if (button[i].largeText) {
             tempFont = arial;
             tempFontSize = LARGE_FONT_SIZE;
        } else {
            tempFont = smallArial;
            tempFontSize = SMALL_FONT_SIZE;
        }

        // Draw out the button text - 1 line that does it for all buttons
        al_draw_text(tempFont, BLACK, (button[i].upperLeftXCoordinate + button[i].lowerRightXCoordinate) / 2,
                    (button[i].upperLeftYCoordinate + button[i].lowerRightYCoordinate) / 2 - (tempFontSize / 2),
                    ALLEGRO_ALIGN_CENTER, button[i].buttonTitle.c_str());
    }
}

// This function checks if the users mouse is hovering over the button and if the button was clicked
// Need to pass the button, the mouse coordinates, game mode, and the event type (as a bool clicked or not)
void Allegro::checkButtonAction() {

    int mouseXCoordinate = event.mouse.x;
    int mouseYCoordinate = event.mouse.y;
    int eventType = event.type;

    for (int i = 0; i < button.length(); i++) {

        // Check the mouse is hovering over the button
        if (mouseXCoordinate >= button[i].upperLeftXCoordinate &&
            mouseXCoordinate <= button[i].lowerRightXCoordinate &&
            mouseYCoordinate >= button[i].upperLeftYCoordinate &&
            mouseYCoordinate <= button[i].lowerRightYCoordinate) {

            if (eventType == ALLEGRO_EVENT_MOUSE_AXES || eventType == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                button[i].filled = true;
            }

            if (eventType == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                button[i].clicked = true;
                button[i].filled = false;
            }

        // If the mouse is not hovering over any buttons then the buttons will just be hallow
        } else if (eventType == ALLEGRO_EVENT_MOUSE_AXES) {

                button[i].filled = false;
        }
    }
}

/// This function converts which button was clicked to an the appropriate action (game mode or end the game)
void Allegro::checkButtonState(bool &continuePlaying) {

    GAMEMODE previousGamemode = gameMode;

    // Switch game mode
    switch (gameMode) {

        case MAIN_MENU:

            // Based on which button was clicked, the appropriate action is performed
            if (button[BUTTON_START].clicked) {
                gameMode = START;
            } else if (button[BUTTON_INSTRUCTIONS].clicked) {
                gameMode = INSTRUCTIONS;
            } else if (button[BUTTON_CREDITS].clicked) {
                gameMode = CREDITS;
            } else if (button[BUTTON_MAIN_MENU_QUIT].clicked) {
                // End the game
                continuePlaying = false;
            }
            break;

        case INSTRUCTIONS:
        case CREDITS:

            if (button[BUTTON_CREDITS_MAIN_MENU].clicked) {
                gameMode = MAIN_MENU;
            } else if (button[BUTTON_CREDITS_START].clicked) {
                gameMode = START;
            } else if (button[BUTTON_CREDITS_QUIT].clicked) {
                continuePlaying = false;
            }
            break;

        case START:

            if (button[BUTTON_MERGE].clicked) {
                gameMode = MERGE_SORT;
            } else if (button[BUTTON_BUBBLE].clicked) {
                gameMode = BUBBLE_SORT;
            } else if (button[BUTTON_SELECTION].clicked) {
                gameMode = SELECTION_SORT;
            } else if (button[BUTTON_PLUS_ONE].clicked) {
                searchTarget++;
            } else if (button[BUTTON_PLUS_TEN].clicked) {
                searchTarget += 10;
            } else if (button[BUTTON_MINUS_ONE].clicked) {
                searchTarget--;
            } else if (button[BUTTON_MINUS_TEN].clicked) {
                searchTarget -= 10;
            }

            // There is no break as for some of the modes the buttons are visually there but are disabled

        case BUBBLE_SORT:
        case SELECTION_SORT:
        case MERGE_SORT:
        case RESET:
        case BINARY_SEARCH:

            if (button[BUTTON_RESET].clicked) {
                gameMode = RESET;
            } else if (button[BUTTON_BINARY_SEARCH].clicked) {
                gameMode = BINARY_SEARCH;
            } else if (button[BUTTON_IN_GAME_QUIT].clicked) {
                continuePlaying = false;
            } else if (button[BUTTON_MAIN_MENU].clicked) {
                gameMode = MAIN_MENU;
            }
            break;
    }
    // Setting the bool of the button back to false
    for (int i = 0; i < button.length(); i++) {
        button[i].clicked = false;
    }

    // Set up the new button coordinates if the gamemode was changed
    if (previousGamemode != gameMode) {
        buttonSetup();
    }
}

// This method prints most of the text onto the screen for the user
void Allegro::printAllText(const TRACKERS &trackers) {

    switch (gameMode) {

        case MAIN_MENU:

            al_draw_text(arial, BLACK, 5, SCREEN_HEIGHT - 30, ALLEGRO_ALIGN_LEFT, "By Eric Karpovits");
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "Graphical Sorting Tool");
            break;

        case INSTRUCTIONS:

            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 40, ALLEGRO_ALIGN_CENTER, "INSTRUCTIONS");
            al_draw_text(smallArial, BLACK, 100, 100, ALLEGRO_ALIGN_LEFT,
                         "This program is a tool that aids the visualization of the algorithms associated with sorting.");
            al_draw_text(smallArial, BLACK, 100, 140, ALLEGRO_ALIGN_LEFT,
                         "In the program, users can pick three different sorting algorithms and one search algorithm such as:");
            al_draw_text(smallArial, BLACK, 150, 180, ALLEGRO_ALIGN_LEFT,
                         "1. Bubble Sort (Simple Sort) - Time Complexity: O(n^2)");
            al_draw_text(smallArial, BLACK, 150, 220, ALLEGRO_ALIGN_LEFT,
                         "2. Selection Sort (Simple Sort) - Time Complexity: O(n^2)");
            al_draw_text(smallArial, BLACK, 150, 260, ALLEGRO_ALIGN_LEFT,
                         "3. Merge Sort (Advanced Sort) - Time Complexity: O(n*log(n))");
            al_draw_text(smallArial, BLACK, 150, 300, ALLEGRO_ALIGN_LEFT,
                         "4. Binary Search (Advanced Search) - Time Complexity: O(log(n))");
            al_draw_text(smallArial, BLACK, 100, 340, ALLEGRO_ALIGN_LEFT,
                         "Clicking one of the sorts will visually sort the random vector in front of the user.");
            al_draw_text(smallArial, BLACK, 100, 380, ALLEGRO_ALIGN_LEFT,
                         "To use the search feature the user will need to pick their number first and then click search.");
            al_draw_text(smallArial, BLACK, 100, 420, ALLEGRO_ALIGN_LEFT,
                         "The array will be automatically sorted if it was not already done so.");
            al_draw_text(smallArial, BLACK, 100, 460, ALLEGRO_ALIGN_LEFT,
                         "Note that the vector size is 150 elements.");
            break;

        case CREDITS:

            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 40, ALLEGRO_ALIGN_CENTER, "CREDITS");
            al_draw_text(smallArial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER,
                         "Version 1.0 - Eric Karpovits - Copyright 2020 - All rights reserved");
            break;

        case START:

            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2 + 47, (SCREEN_HEIGHT - 50 + LARGE_FONT_SIZE / 2),
                          ALLEGRO_ALIGN_LEFT, "%.3fs", trackers.timeDuration);

        case BUBBLE_SORT:
        case SELECTION_SORT:
        case MERGE_SORT:
        case RESET:
        case BINARY_SEARCH:

            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 4 - 60, (SCREEN_HEIGHT - 50 + LARGE_FONT_SIZE / 2),
                          ALLEGRO_ALIGN_CENTER, "Comparisons: %d", trackers.numberOfComparisons);
            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 4 * 3 + 60, (SCREEN_HEIGHT - 50 + LARGE_FONT_SIZE / 2),
                          ALLEGRO_ALIGN_CENTER, "Moves / Splits: %d", trackers.numberOfMoves);
            al_draw_rectangle(SCREEN_WIDTH / 2 - 75, 95, SCREEN_WIDTH / 2 + 75, 140, WHITE, 3);
            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2, 117 - LARGE_FONT_SIZE / 2, ALLEGRO_ALIGN_CENTER, "%d", searchTarget);
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2 - 43, (SCREEN_HEIGHT - 50 + LARGE_FONT_SIZE / 2),
                          ALLEGRO_ALIGN_CENTER, "Running Time:");
            break;
    }
}

