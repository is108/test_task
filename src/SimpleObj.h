#include <iostream>

enum Colors {
    GREEN = 0,
    BLUE,
    RED
};

class SimpleObj {
public:
    SimpleObj();
    ~SimpleObj();

    void setColor(Colors color) noexcept;
    Colors getColor() const;
private:

private:
    Colors color; //Цвет объекта
};
