#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

class Sorting {

    private:

        // Class object members + member variables
        Allegro &allegro;
        apvector <int> data;
        apvector <int> originalData;
        TRACKERS trackers;

    public:

        // Constructor
        Sorting(Allegro &allegro);
        void initializedRandomData();

        // Destructor
        ~Sorting(){};

        // Accessors
        int getArrayLength() { return data.length(); }
        apvector <int> getAllValues() { return data; }
        TRACKERS getTrackers() { return trackers; }

        // Modifiers
        void setDataToOriginal() { data = originalData; }
        void resetTrackers();
        void setTimeDuration(double time) { trackers.timeDuration = time; }
        void setSortedTracker(bool sorted) { trackers.sorted = sorted; }

        // Basic Sorts
        void bubbleSort();
        void selectionSort();

        // Merge Sort
        void mergeMain();
        void mergeData(int firstIndex, int midIndex, int lastIndex);
        void mergeSort(int firstIndex, int lastIndex);

        // Binary Search
        void binarySearchMain();
        void binarySearch(int leftIndex, int rightIndex, int target);

        // Untilities
        void resetDrawingIndex();
        void drawFinishedSort();
        void swapData(int &left, int &right);
};

#endif // SORTING_H_INCLUDED
