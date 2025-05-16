// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

Train::Train() : countOp(0), first(nullptr) {}
Train::~Train() {
    if (first) {
        Car* current = first->next;
        while (current != first) {
            Car* temp = current;
            current = current->next;
            delete temp;
        }
        delete first;
    }
}

void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;
    if (!first) {
        newCar->next = newCar;
        newCar->prev = newCar;
        first = newCar;
    } else {
        newCar->prev = first->prev;
        newCar->next = first;
        first->prev->next = newCar;
        first->prev = newCar;
    }
}

int Train::getLength() {
    countOp = 0;
    if (!first) return 0;
    if (!first->light) {
        first->light = true;
        countOp++;
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
            } else {
                current->light = false;
                countOp++; 
                for (int i = 0; i < steps; ++i) {
                    current = current->prev;
                    countOp++;
                }
            }
        } else {
            max_steps++;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
