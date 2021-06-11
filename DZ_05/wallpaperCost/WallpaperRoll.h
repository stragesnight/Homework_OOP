// заголовочный файл, содержащий объявление и реализацию класса РулонОбоев.

#include <string>
#include <cmath>
#include <iostream>

struct Size
{
    float width;
    float length;
};

class WallpaperRoll
{
private:
    std::string name;
    Size size;
    float cost;

    const Size validateSize(const Size& size)
    {
        return { fabsf(size.width), fabsf(size.length) };
    }

public:
    WallpaperRoll()
    {
        name = "default wallpaper roll name";
        size = { 1, 1 };
        cost = 0;
    }

    WallpaperRoll(const std::string& name, const Size& size, float cost)
    {
        this->name = name;
        this->size = validateSize(size);
        this->cost = fabs(cost);
    }

    WallpaperRoll(const std::string& name, float width, float length, float cost)
    {
        this->name = name;
        this->size = { width, length };
        this->cost = fabs(cost);
    }

    ~WallpaperRoll()
    {
        this->name.clear();
        this->size = {};
        this->cost = 0;
    }

    const std::string& getName() { return name; }
    const Size& getSize() { return size; }
    float getCost() { return cost; }

    void setName(const std::string& name) { this->name = name; }
    void setSize(const Size& size) { this->size = validateSize(size); }
    void setSize(float width, float length) { this->size = { fabsf(width), fabsf(length) }; }
    void setCost(float cost) { this->cost = fabs(cost); }

    float calculateArea()
    {
        return size.width * size.length;
    }
};

