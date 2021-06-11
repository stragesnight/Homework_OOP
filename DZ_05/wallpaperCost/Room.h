// заголовочный файл, содержащий объевление класса Комната

#include "WallpaperRoll.h"

#define cout_tabs(c) { for(int i=0;i<c;i++)std::cout<<'\t'; }

struct RoomSize
{
    float width;
    float length;
    float height;
};

class Room
{
private:
    std::string name;
    RoomSize size;
    WallpaperRoll* wallpaper;
    bool glueCeiling;

    const RoomSize validateSize(const RoomSize& size)
    {
        return { fabsf(size.width), fabsf(size.length), fabsf(size.height) };
    }

public:
    Room()
    {
        name = "defult room name";
        size = { 1, 1, 1 };
        wallpaper = new WallpaperRoll();
        glueCeiling = false;
    }

    Room(const std::string& name, const RoomSize& size, 
            const WallpaperRoll& wallpaper, bool glueCeiling)
    {
        this->name = name;
        this->size = validateSize(size);
        this->wallpaper = new WallpaperRoll(wallpaper);
        this->glueCeiling = glueCeiling;
    }

    ~Room()
    {
        this->name.clear();
        this->size = {};
        delete this->wallpaper;
        this->glueCeiling = false;
    }

    const std::string& getName() { return name; }
    const RoomSize& getSize() { return size; }
    const WallpaperRoll* getWallpaper() { return wallpaper; }
    bool isCeilingGlued() { return glueCeiling; }

    void setName(const std::string& name) { this->name = name; }
    void setSize(const RoomSize& size) { this->size = validateSize(size); }
    void setWallpaper(const WallpaperRoll& wallpaper) 
    {
        delete this->wallpaper;
        this->wallpaper = new WallpaperRoll(wallpaper); 
    }
    void setGlueCeiling(bool glueCeiling) { this->glueCeiling = glueCeiling; }


    float calculateGluedArea()
    {
        float area = size.width * size.length * size.height;
        area -= (size.width * size.length) * (2 - glueCeiling);
        return area;
    }

    unsigned calculateRollCount()
    {
        float rollArea = wallpaper->calculateArea();
        return int(calculateGluedArea() / rollArea);
    }

    float calculateRollCost()
    {
        return calculateRollCount() * wallpaper->getCost();
    }

    void displayInfo()
    {
        std::cout << "\n\tRoom \"" << name << "\": ";

        std::cout << "\t\tsize - " << size.width << 'x' 
            << size.length << 'x' << size.height << " cm\n";

        const Size rollSize = wallpaper->getSize();
        std::cout << "\t\twallpaper - \"" << wallpaper->getName() << '\n'
            << "\t\t\tsize - " << rollSize.width << 'x' << rollSize.length << " cm\n";
        std::cout << "\t\t\tcost - $" << wallpaper->getCost() << '\n'; 

        std::cout << "\t\tGlue ceiling? - ";
        if (glueCeiling)
            std::cout << "yes\n";
        else
            std::cout << "no\n";
    }
};

