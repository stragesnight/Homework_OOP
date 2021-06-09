#include "Student.h"

// реализаци€ метода вычислени€ среднего балла
double Student::getAver()
{
    double sum = 0;
    for (int i = 0; i < 3; i++)
        sum += marks[i];

    return sum / 3.;
}
