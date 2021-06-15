// файл, содержащий объявление класса Human

// Человек
class Human
{
private:
    char* name;         // имя
    char* surname;      // фамилия
    char* fathers;      // отчество
    int age;            // возраст

    // скопировать строку src в field
    void generateString(char*& field, const char* src);

public:
    // конструктор
    Human(const char* name = "", const char* surname = "", 
            const char* fathers = "", int age = -1);
    // конструктор копирования
    Human(const Human& other);
    // деструктор
    ~Human();

    // геттеры

    const char* getName() { return name; }
    const char* getSurname() { return surname; }
    const char* getFathers() { return fathers; }
    const int getAge() { return age; }

    // сеттеры

    void setName(const char* name);
    void setSurname(const char* surname);
    void setFathers(const char* fathers);
    void setAge(const int age);

    // вывести на экран информацию о человеке
    void displayInfo();
};

