#ifndef APP_MANAGEMEN_H_INCLUDED
#define APP_MANAGEMENT_H_INCLUDED

// My game class which has the Allegro class object and Stack class object as a members
// allowed me not to have to pass as many arguments into hanoi algorithm
class AppManagement {

    private:

        // Class object members + member variable
        Allegro &allegro;
        Sorting &sorting;
        bool continuePlaying;

    public:

        // Constructor - as you can see it is different as I am making the objects as members in this class
        AppManagement(Allegro &allegro, Sorting &sorting);
        // Destructor
        ~AppManagement(){;}

        // Main play game loop
        void play();
        // A getter method which gets the continue playing variable
        bool isContinuePlaying() { return continuePlaying; }
        // This method resets everything
        void resetEverything();
};

#endif // APP_MANAGEMEN_H_INCLUDED
