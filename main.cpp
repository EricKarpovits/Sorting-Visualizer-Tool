/***********************************************************************************
 * Eric Karpovits - Graphical Sorting - Mr. Kronberg                               *
 * Fully functioning sorting program that sorts an unsorted vector of 150 elements.*
 * Everything is visualized and binary search is implemented.                      *
 *                                                                                 *
 * Last Modified: November 15, 2020                                                *
 ***********************************************************************************/

#include "declarations.h"

int main() {

    // Seed random timer
    srand (time(NULL));

    // Create allegro object
    Allegro allegro;
    // Create sorting class object with the allegro class as a member
    Sorting sorting(allegro);
    // Create app object that has the other two objects as members
    AppManagement app(allegro, sorting);

    /******* Initialize allegro *************/
    int errorCode = allegro.initializeAllegro();
    if (errorCode != 0) {
        return errorCode;
    }

    // Setup buttons
    allegro.buttonSetup();

    /******* Main loop ********/
    while (app.isContinuePlaying()) {
        app.play();
    }

    return 0;
}
