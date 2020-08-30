#include <iostream>

#include "Menu.h"

int main() {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);
    std::unique_ptr<Menu> menu(new Menu);

    char user_answer; //Ответ пользователя, для управления потоками
    bool isStart = true;

    //Пока работает программа, получать ответ пользователя и выполнять необходимые действия
    while (isStart) {
        std::cin >> user_answer;

        switch(user_answer) {
            case '1':
                objects_manager->startGenerateObjects();
                break;
            case '2':
                objects_manager->stopGenerateObjects();
                break;
            case '3':
                objects_manager->startSortObjects();
                break;
            case '4':
                objects_manager->stopSortObjects();
                break;
            case '5':
                isStart = false;
                break;
            default:
                break;
        }
    } 

}
