#ifndef ALLEGRO_H_INCLUDED
#define ALLEGRO_H_INCLUDED

class Allegro {

    private:

        // Member variables - mainly all pointers for allegro
        ALLEGRO_DISPLAY *display;
        ALLEGRO_FONT *arial, *smallArial;
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *eventQueue;
        ALLEGRO_EVENT event;
        ALLEGRO_SAMPLE *gameMusic, *buttonClick;
        ALLEGRO_BITMAP *background;

        // Button properties vector struct
        apvector<BUTTON> button;

        // An enum of all game modes
        GAMEMODE gameMode;

        int searchTarget;

    public:

        // Inline constructor & destructor
        Allegro() { gameMode = MAIN_MENU, resetSearchTarget(); }
        ~Allegro() { releaseMemory(); }

        // Untilities
        int initializeAllegro();
        void releaseMemory();
        void drawMain(const apvector<int> &currentRectangleValues, const TRACKERS &trackers);
        void printAllText(const TRACKERS &trackers);

        // Acessors
        ALLEGRO_EVENT_QUEUE *getEventQueue() { return eventQueue; }
        GAMEMODE getGameMode() { return gameMode; }
        ALLEGRO_FONT *getArialFont() { return arial; }
        ALLEGRO_FONT *getSmallArialFont() { return smallArial; }
        ALLEGRO_EVENT &getEvent() { return event; }
        ALLEGRO_DISPLAY *getDisplay() { return display; }
        int getSearchTarget() { return searchTarget; }

        // Modifiers
        void setGameMode(GAMEMODE newGameMode) { gameMode = newGameMode; }
        void resetSearchTarget() { searchTarget = 0; }

        // Display rectangle methods
        void drawRectangles(const apvector<SCREEN_POSITIONS> &screenPositions, const apvector<int> &currentRectangleValues,
                            const apvector <ALLEGRO_COLOR> rectangleColours);
        apvector<SCREEN_POSITIONS> calculateScreenPositionsForRectangles(const apvector<int> &currentRectangleValues);
        void prepareForDrawing();
        void displayRectangles(const apvector<int> &currentRectangleValues, const TRACKERS &trackers);
        apvector <ALLEGRO_COLOR> getRectangleColours(const apvector <int> &currentRectangleValues, const TRACKERS &trackers);

        // Buttons
        void buttonSetup();
        void setButtonProperties(int buttonNumber, int upperLeftX, int upperLeftY, int lowerRightX,
                                 int lowerRightY, bool largeText, string buttonTitle, ALLEGRO_COLOR buttonColour);
        void drawButtons();
        void checkButtonState(bool &continuePlaying);
        void checkButtonAction();
        void playButtonClickSound() { al_play_sample(buttonClick, 10.0, 0, 30.0, ALLEGRO_PLAYMODE_ONCE, 0); }
};

#endif // ALLEGRO_H_INCLUDED
