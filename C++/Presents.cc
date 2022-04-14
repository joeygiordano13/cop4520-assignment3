#include "FineList.cc"
#include "SafeVector.cc"
#include <random>
#include <thread>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

#define NUM_PRESENTS 500000
#define NUM_SERVANTS 4

void performServantTask(FineList *list, SafeVector *remainingGifts, SafeVector *processedGifts) {
    while (processedGifts->size() < NUM_PRESENTS) {
        // Randomly select task
        unsigned int taskSelection = std::rand() % 3;
        switch(taskSelection) {
            // Minotaur wants to add a new present
            // to linked list
            case 0: {
                //std::cout << "task 1" << std::endl;
                if (remainingGifts->size() <= 0) {
                    continue;
                }

                // Remove gift from remaining gifts
                // and place it into linked list
                unsigned int tag = remainingGifts->pop();
                list->insert(tag);
                // Add gift to vector of processed gifts
                processedGifts->push(tag);
                break; // task complete
            }
            // Minotaur wants servants to write 
            // a thank you card
            case 1: {
                //std::cout << "task 2" << std::endl;
                // Thank you card cannot be written
                if (list->isEmpty() || processedGifts->size() <= 0) {
                    continue;
                }

                // Remove a tag from the ones that
                // have already been added to the list.
                // TODO: randomize this later, instead
                // of just popping from vector
                unsigned int tag = processedGifts->pop();
                list->remove(tag); // remove gift

                // Print a thank you
                std::cout << "Thank you guest ID #" << tag << "!" << std::endl;
                break; // task complete
            }
            // Minotaur wants to check if present
            // is in linked list
            case 2: {
                //std::cout << "task 3" << std::endl;
                unsigned int minotaurRequestedTag = std::rand() % NUM_PRESENTS;
                bool inList = list->contains(minotaurRequestedTag);
                // Print result for minotaur
                std::cout << "Guest tag #" << minotaurRequestedTag 
                            << (inList ? " is" : " is not")
                            << " in the list." << std::endl;
                break; // task complete
            }
        }
    }
}


int main() {
    int tStart, tEnd;
    std::ofstream opfile;
    // Initialize parallel data structures & threads
    FineList *list = new FineList();
    SafeVector *remaining = new SafeVector(NUM_PRESENTS);
    SafeVector *processed = new SafeVector(0);
    std::thread threads[NUM_SERVANTS];

    // Start timer on tasks
    std::cout << "Timer start" << std::endl;
    tStart = clock();
    // Concurrently call tasks for each thread
    for (unsigned int i = 0; i < NUM_SERVANTS; i++) {
        threads[i] = std::thread(performServantTask, list, remaining, processed);
    }

    // Await threads to finish and join them
    for (unsigned int i = 0; i < NUM_SERVANTS; i++) {
        threads[i].join();
    }
    // End timer
    tEnd = clock();
    std::cout << "Timer end" << std::endl;

    // Results
    opfile.open("result.txt");
    std::cout << "Execution time: " << (tEnd - tStart)/double(CLOCKS_PER_SEC) << std::endl;
    opfile << "Execution Time: " << 
            (tEnd - tStart)/double(CLOCKS_PER_SEC) 
            << std::endl;
}


