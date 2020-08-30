#include "SimpleObj.h"

SimpleObj::SimpleObj() {
    //Генерация значения от 0 до 2
    srand(time(NULL));    
    int value = 0 + rand() % (3 - 0);

    // В зависимости от того, какое значение было сгенерировано, для объекта устанавливается его цвет
    switch(value) {
        case 0:
            color = GREEN;
            break;
        case 1:
            color = BLUE;
            break;
        case 2:
            color = RED;
            break;
        default:
            break;
    }
}

SimpleObj::~SimpleObj() {

}

Colors SimpleObj::getColor() const {
    return color;
}

void SimpleObj::setColor(Colors color) noexcept {
    this->color = color;
}
