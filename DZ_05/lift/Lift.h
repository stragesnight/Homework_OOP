// файл, содержащий объявление класса Лифт


enum LiftState { NOT_WORKING = 0, WORKING = 1};

// Лифт
class Lift
{
private:
    int minFloor;       // минимальный этаж
    int maxFloor;       // максимальный этаж
    int currentFloor;   // текущее положение лифта
    bool state;         // состояние лифта

    // обновить состояние лифта
    void update();

    // проверить этаж на корректность
    bool validFloor(int floor);

    // обработать поездку на лифте
    void handleRide(int dst);

    // проверить текущий этоаж на корректность
    void clampCurrentFloor();
public:
    // конструктор
    Lift(int minFloor = 0, int maxFloor = 10);
    // деструктор
    ~Lift();

// геттеры

    // получить минимальный этаж
    int getMinFloor();
    // получить максимальный этаж
    int getMaxFloor();

    // получить текущий этаж
    int getCurrentFloor();

    // получить текущее состояние
    bool getState();

// сеттеры

    // установить минимальный этаж
    void setMinFloor(int minFloor);
    // установить максимальный этаж
    void setMaxFloor(int maxFloor);

// методы для взаимодействия с лифтом

    // запросить лифт
    void requestLift(int dst);
};
