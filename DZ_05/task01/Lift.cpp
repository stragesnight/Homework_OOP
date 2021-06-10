// файл, содержащий реализации методов класса Лифт

#include <algorithm>        // std::swap()
#ifdef _WIN32
    #include <Windows.h>    // Sleep()
#else
    #include <unistd.h>     // sleep()
#endif
#include <iostream>
#include "Lift.h"

// сообщения для дебага программы
// если ключевое слово _DBG_LOG было объявлено,
// то на консоль будут выводиться сообщения о работе программы
#define _DBG_LOG
#ifdef _DBG_LOG
    #define dbgmsg(msg) std::cout << msg << '\n'
#else
    #define dbgmsg(msg)
#endif

#ifdef _WIN32
    #define wait_for(amonut) Sleep(amonut)
#else
    #define wait_for(amount) sleep((float)amount / 1000.)
#endif

bool Lift::validFloor(int floor)
{
    dbgmsg("validFloor(" << floor << ")");
    return (floor >= minFloor && floor <= maxFloor);
}

void Lift::handleRide(int dst)
{
    dbgmsg("handleRide(" << dst << ")");

    state = WORKING;

    int diff = dst - currentFloor;
    int delta = dst > currentFloor ? 1 : -1;

    dbgmsg("\tlift is heading to floor №" << dst);
    for (; currentFloor != dst; currentFloor += delta)
    {
        dbgmsg("\t\t" << currentFloor << "...");
        wait_for(1000);
    }

    wait_for(2000);

    dbgmsg("\t\tDone.");
    dbgmsg("\t\tcurrentFloor - " << currentFloor);

    state = NOT_WORKING;
}

void Lift::clampCurrentFloor()
{
    dbgmsg("clampCurrentFloor()");

    if (currentFloor < minFloor)
        currentFloor = minFloor;
    else if (currentFloor > maxFloor)
        currentFloor = maxFloor;

    dbgmsg("\tcurrentFloor - " << currentFloor);
}

Lift::Lift(int minFloor, int maxFloor)
{
    dbgmsg("Lift(" << minFloor << ", " << maxFloor << ")");
    dbgmsg("\tthis - " << this);

    this->minFloor = minFloor;
    setMaxFloor(maxFloor);

    this->currentFloor = minFloor;

    this->state = NOT_WORKING;
}

Lift::~Lift()
{
    dbgmsg("~Lift()");
    dbgmsg("\tthis - " << this);

    minFloor = 0;
    maxFloor = 0;
    
    currentFloor = 0;

    state = NOT_WORKING;
}

int Lift::getMinFloor() { return minFloor; }
int Lift::getMaxFloor() { return maxFloor; }

int Lift::getCurrentFloor() { return currentFloor; }

bool Lift::getState() { return state; }


void Lift::setMinFloor(int minFloor)
{
    dbgmsg("setMinFloor(" << minFloor << ")");

    if (minFloor == this->maxFloor)
    {
        dbgmsg("\tminFloor == this->maxFloor, skipping.");
        return;
    }

    dbgmsg("\tminFloor != this->maxFloor, setting.");

    this->minFloor = minFloor;

    if (this->maxFloor < this->minFloor)
    {
        dbgmsg("\t\tthis->maxFloor < this->minFloor, swapping.");
        std::swap(this->minFloor, this->maxFloor);
    }

    clampCurrentFloor();
}

void Lift::setMaxFloor(int maxFloor)
{
    dbgmsg("setMaxFloor(" << maxFloor << ")");

    if (maxFloor == this->minFloor)
    {
        dbgmsg("\tmaxFloor == this->minFloor, skipping.");
        return;
    }

    dbgmsg("\tmaxFloor != this->minFloor, setting.");

    this->maxFloor = maxFloor;

    if (this->maxFloor < this->minFloor)
    {
        dbgmsg("\t\tthis->maxFloor < this->minFloor, swapping.");
        std::swap(this->minFloor, this->maxFloor);
    }

    clampCurrentFloor();
}

void Lift::requestLift(int dst)
{
    dbgmsg("requestLift(" << dst << ")");

    if (state != NOT_WORKING)
    {
        dbgmsg("\tstate != NOT_WORKING, skipping.");
        return;
    }

    if (!validFloor(dst))
    {
        dbgmsg("\t!validFloor(dst), skipping.");
        return;
    }

    handleRide(dst);
}

