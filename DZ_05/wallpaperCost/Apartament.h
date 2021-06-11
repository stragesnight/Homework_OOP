// заголовочный файл, содержащий объявление и реализацию класса Квартира

#include <vector>
#include <iostream>
#include "Room.h"


class Apartament
{
private:
    std::vector<Room*> rooms;

public:
    Apartament()
    {
        rooms.resize(0);
    }

    Apartament(const std::vector<Room*>& rooms)
    {
        this->rooms.clear();
        this->rooms = rooms;
    }

    ~Apartament()
    {
        rooms.clear();
    }

    void addRoom(const Room& room)
    {
        rooms.push_back(new Room(room));
    }

    unsigned calculateRollCount()
    {
        unsigned count = 0;

        for (int r = 0, size = rooms.size(); r < size; r++)
            count += rooms[r]->calculateRollCost();

        return count;
    }

    float calculateRollCost()
    {
        float cost = 0;

        for (int r = 0, size = rooms.size(); r < size; r++)
            cost += rooms[r]->calculateRollCost();

        return cost;
    }

    void displayInfo()
    {
        for (int r = 0, size = rooms.size(); r < size; r++)
            rooms[r]->displayInfo();
    }
};
