// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : opCount(0), headCar(nullptr) {}

Train::~Train() {
  if (headCar) {
    Car* currentCar = headCar;
    do {
      Car* tempCar = currentCar->next;
      delete currentCar;
      currentCar = tempCar;
    } while (currentCar != headCar);
  }
}

void Train::addCar(bool hasLight) {
  Car* newCar = new Car{hasLight, nullptr, nullptr};
  if (!headCar) {
    headCar = newCar;
    headCar->next = headCar;
    headCar->prev = headCar;
  } else {
    Car* lastCar = headCar->prev;
    lastCar->next = newCar;
    newCar->prev = lastCar;
    newCar->next = headCar;
    headCar->prev = newCar;
  }
}

int Train::getLength() {
  opCount = 0;
  Car* currentCar;
  while (true) {
    currentCar = headCar;
    int countedCars = 0;
    if (!currentCar->light) {
      currentCar->light = true;
    }
    currentCar = currentCar->next;
    opCount += 2;
    while (!currentCar->light) {
      currentCar = currentCar->next;
      opCount += 2;
      countedCars++;
    }
    currentCar->light = false;
    if (!headCar->light) {
      return countedCars + 1;
    }
  }
}

int Train::getOpCount() {
  return opCount;
}
