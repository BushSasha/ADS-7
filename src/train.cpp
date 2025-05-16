// Copyright 2021 NNTU-CS
#include "train.h"
int Train::getLength() {
    countOp = 0;
    if (!first) return 0;
    if (!first->light) {
        first->light = true;
    }
    Car* start = first;
    int max_steps = 1;
    while (true) {
        int steps = 0;
        Car* current = start;
        bool found = false;
        while (steps < max_steps) {
            current = current->next;
            steps++;
            countOp++;
            if (current->light) {
                found = true;
                break;
            }
        }

        if (found) {
            if (current == start) {
                return steps;
            }
            current->light = false;
            for (int i = 0; i < steps; ++i) {
                current = current->prev;
                countOp++;
            }
        } else {
            max_steps++;
        }
    }
}
