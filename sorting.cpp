#include "declarations.h"

// Constructor that initializes and randomizes the array of numbers and sets counters to 0
Sorting::Sorting(Allegro &allegro) : allegro(allegro) {

    initializedRandomData();
    trackers.greenIndex.resize(data.length());
    resetTrackers();
}

// A method to reset all the trackers
void Sorting::resetTrackers() {

    trackers.timeDuration = 0;
    trackers.numberOfComparisons = 0;
    trackers.numberOfMoves = 0;
    trackers.redIndex = -1;
    trackers.rightBlackIndex = -1;
    trackers.leftBlackIndex = -1;
    trackers.middleGreenIndex = -1;
    trackers.numberOfRests = 0;
    trackers.sorted = false;
    for (int i = 0; i < data.length(); i++) {
        trackers.greenIndex[i] = -1;
    }
}

// This constructor method essentially shuffles consecutive numbers so that there is a smooth slope
void Sorting::initializedRandomData() {

    originalData.resize(ARRAY_SIZE);

    apvector <int> tempArray(ARRAY_SIZE);
    apvector <bool> randomized(ARRAY_SIZE, false);
    int rndIndex;

    // Initialize array with consective numbers so that the slope will be smooth
    for(int i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = i + 1;
    }

    for(int i = 0; i < ARRAY_SIZE; i++) {

        // This loop finds another random consecutive number but makes sure that the same one is not repeated
        do {
          rndIndex = rand() % ARRAY_SIZE;
        }
        while (randomized[rndIndex]);

        originalData[i] = tempArray[rndIndex];
        randomized[rndIndex] = true;
    }
    data = originalData;
}

// Swap method
void Sorting::swapData(int &left, int &right) {

    int temp = left;
    left = right;
    right = temp;
}

/******* Bubble Sort ********/
// An optimized version of Bubble Sort
void Sorting::bubbleSort() {

    setDataToOriginal();
    resetTrackers();

    // Timer to keep track of running time
    /// So for this project I wanted to keep track of the time without the drawing part but
    /// this was impossible as there wasn't enough data to even get 1 tick on the clock.
    /// In other words the algoirthms are just too fast for the timer and it registers no time has passed unless I start drawing
    auto start = high_resolution_clock::now();

    for (int i = 0; i < data.length() - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < data.length() - i - 1; j++) {

            trackers.numberOfComparisons++;
            if (data[j] > data[j + 1]) {
                swapData(data[j], data[j + 1]);
                swapped = true;
                trackers.numberOfMoves++;
                trackers.redIndex = j + 1;
                // Essentially I am only keeping track of the timer while it processing and not the drawing time.
                // As drawing time between alogithms veries and it would not be a good comparison.
                allegro.drawMain(data, trackers);
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (swapped == false){
            break;
        }
    }
    // The time duration
    auto timeSpan = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    // Divide by 1000 to turn milliseconds to seconds
    trackers.timeDuration = ((double)timeSpan.count() / 1000);
    // Draw the cool green animation
    drawFinishedSort();
    trackers.sorted = true;

}

/******* Selection Sort ********/
void Sorting::selectionSort() {

    setDataToOriginal();
    resetTrackers();
    auto start = high_resolution_clock::now();

    // One by one move boundary of unsorted subarray
    for (int i = 0; i < data.length() - 1; i++) {

        // Find the minimum element in unsorted array
        int minIndex = i;
        for (int j = i + 1; j < data.length(); j++) {

            trackers.numberOfComparisons++;
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        // Draw the selection sort before and after the swap for a better visualization
        trackers.redIndex = i;
        trackers.greenIndex[minIndex] = minIndex;
        allegro.drawMain(data, trackers);
        al_rest(SELECTION_SORT_DELAY);

        // Swap the found minimum element with the first element
        swapData(data[minIndex], data[i]);
        trackers.numberOfMoves++;
        trackers.greenIndex[minIndex] = -1;
        trackers.redIndex = i;

        allegro.drawMain(data, trackers);
        al_rest(SELECTION_SORT_DELAY);
    }
    auto timeSpan = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    // Calculate time delayed by the sleep/rest period
    int totalTimeDelay = SELECTION_SORT_DELAY * 2 * trackers.numberOfMoves;
    trackers.timeDuration = ((double)timeSpan.count() / 1000) - totalTimeDelay;
    drawFinishedSort();
    trackers.sorted = true;
}

/******* Merge Sort Recursive Algorithm ********/
// The main for the merge sort allowed everything to be clean and not in the main loop
// also required as the merge sort is recursive so putting the timer in it would be a
// bad idea as it would always reset after each recursive sequence
void Sorting::mergeMain() {

    setDataToOriginal();
    resetTrackers();
    auto start = high_resolution_clock::now();

    mergeSort(INDEX_ZERO, data.length() - 1);

    auto timeSpan = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    int totalTimeDelay = MERGE_SORT_DELAY * trackers.numberOfComparisons;
    trackers.timeDuration = ((double)timeSpan.count() / 1000) - totalTimeDelay;

    drawFinishedSort();
    setSortedTracker(true);

}

// Divide the array into two subarrays, sort them and merge them
void Sorting::mergeSort(int firstIndex, int lastIndex) {

    if (firstIndex < lastIndex) {
        // midIndex is the point where the array is divided into two subarrays
        int midIndex = firstIndex + (lastIndex - firstIndex) / 2;

        // Split
        mergeSort(firstIndex, midIndex);
        mergeSort(midIndex + 1, lastIndex);
        // As discussed I count the number of moves as 1 move per split and 1 move per merge
        /// The number of elements that were split and merged does not matter as it is all counted as 1 per
        trackers.numberOfMoves++;

        // Merge the sorted subarrays
        mergeData(firstIndex, midIndex, lastIndex);
        trackers.numberOfMoves++;
    }
}

// Merge two subarrays left and right arrays
void Sorting::mergeData(int firstIndex, int midIndex, int lastIndex) {

    // Calculate left length and right Length and create temp arrays
    int leftLength = midIndex - firstIndex + 1;
    int rightLength = lastIndex - midIndex;

    int left[leftLength];
    int right[rightLength];

    for (int i = 0; i < leftLength; i++) {
        left[i] = data[firstIndex + i];
    }
    for (int j = 0; j < rightLength; j++) {
        right[j] = data[midIndex + 1 + j];
    }

    // Maintain current index of sub-arrays and main array
    int i = 0, j = 0, k = firstIndex;

    // Until reached either end of either leftLength or rightLength, pick larger among
    // elements left and right and place them in the correct position at data
    while (i < leftLength && j < rightLength) {

        // Comparison counter
        trackers.numberOfComparisons++;
        if (left[i] <= right[j]) {
            data[k] = left[i];
            i++;
        } else {
            data[k] = right[j];
            j++;
        }

        GAMEMODE gameMode = allegro.getGameMode();
        // This is an if statement to check if it needs to be drawn.
        // It does not perform the drawing if a binary search needs to be performed and the data is not sorted
        if (gameMode != BINARY_SEARCH) {
            trackers.redIndex = k;
            trackers.leftBlackIndex = firstIndex;
            trackers.rightBlackIndex = lastIndex;
            allegro.drawMain(data, trackers);
            al_rest(MERGE_SORT_DELAY);
            trackers.numberOfRests++;
        }
        resetDrawingIndex();
        k++;
    }

    // When we run out of elements in either left or right,
    // pick up the remaining elements and put in data
    while (i < leftLength) {
        data[k] = left[i];
        i++;
        k++;
    }

    while (j < rightLength) {
        data[k] = right[j];
        j++;
        k++;
    }
}

/******************** Binary Search **********************/
void Sorting::binarySearchMain() {

    resetTrackers();

    // This if statement is a flag that if the data is not sorted
    // to sort the data.
    if (!trackers.sorted) {
        mergeSort(0, data.length() - 1);
        trackers.sorted = true;
        trackers.numberOfMoves = 0;
        trackers.numberOfComparisons = 0;
    }

    // Start timer
    auto start = high_resolution_clock::now();

    binarySearch(INDEX_ZERO, data.length() - 1, allegro.getSearchTarget());

    auto timeSpan = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    int totalTimeDelay = (BINARY_SEARCH_DELAY * trackers.numberOfComparisons) + (trackers.numberOfRests * BINARY_SEARCH_NOT_FOUND_DELAY);
    trackers.timeDuration = ((double)timeSpan.count() / 1000) - totalTimeDelay;
}


// Performs binary search in the array data. Must be sorted in assending order.
// Sets the location of the found to the index otherwise -1 if not found
void Sorting::binarySearch(int leftIndex, int rightIndex, int target) {

    trackers.leftBlackIndex = leftIndex;
    trackers.rightBlackIndex = rightIndex;

    if (rightIndex >= leftIndex) {

        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

        // The visualization of the search
        trackers.middleGreenIndex = middleIndex;
        allegro.drawMain(data, trackers);
        al_rest(BINARY_SEARCH_DELAY);

        // The number of comparisons increment each time this function is called.
        // This is because 1 comparison always yeilds a result (up to 3) and
        // thus causing a move/split/change.
        trackers.numberOfMoves++;
        trackers.numberOfComparisons++;
        // If the target is present at the middle itself
        if (data[middleIndex] == target) {
            trackers.redIndex = trackers.middleGreenIndex;
            trackers.leftBlackIndex = trackers.middleGreenIndex;
            trackers.rightBlackIndex = trackers.middleGreenIndex;
            return;
        } else if (data[middleIndex] > target) {
            binarySearch(leftIndex, middleIndex - 1, target);
            return;
        // If target greater, ignore left half
        } else {
            binarySearch(middleIndex + 1, rightIndex, target);
            return;
        }
    }
    // It only gets here if the target is not found.
    trackers.leftBlackIndex = data.length();
    trackers.rightBlackIndex = data.length();
    trackers.middleGreenIndex = -1;
    allegro.drawMain(data, trackers);
    ALLEGRO_FONT *arial = allegro.getArialFont();
    al_draw_text(arial, RED, SCREEN_WIDTH / 2, 150, ALLEGRO_ALIGN_CENTER, "Element is not present in the vector");
    al_flip_display();
    al_rest(BINARY_SEARCH_NOT_FOUND_DELAY);
    trackers.numberOfRests++;
}

void Sorting::resetDrawingIndex() {

    trackers.leftBlackIndex = -1;
    trackers.rightBlackIndex = -1;
    trackers.middleGreenIndex = -1;
}

// This method draws the cool finishing animation
void Sorting::drawFinishedSort() {

    for (int i = 1; i < data.length(); i++) {
        trackers.greenIndex[i - 1] = i - 1;
        trackers.redIndex = i;
        allegro.drawMain(data, trackers);
        al_rest(DRAW_FINISHED_SORT_DELAY);
    }

    for (int i = 0; i < data.length(); i++) {
        trackers.greenIndex[i] = -1;
    }
    trackers.redIndex = -1;
}
