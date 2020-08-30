#include "Menu.h"

Menu::Menu() {
    objects_manager = std::make_unique<ObjectsManager>();

    isRun = true;
    //Создание потока вывода меню
    print_menu = std::thread(&Menu::printMenu, this);
}

Menu::~Menu() {
    isRun = false;
    //Присоединение потока вывода меню
    if (print_menu.joinable()){
        print_menu.join();
    }
}

void Menu::printCounters() {
    //Вывод счетчиков
    std::cout << "| Сгенерировано объектов: " << objects_manager->getCounterGeneratedObjects() << "                                  |" << std::endl \
              << "| Отсортировано объектов: " << objects_manager->getCounterSortedObjects() << "                                  |" << std::endl \
              << "|       1) Зеленых: " << objects_manager->getCounterGreenObjects() << "                                        |" << std::endl \
              << "|       2) Синих: " << objects_manager->getCounterBlueObjects() << "                                          |" << std::endl \
              << "|       3) Красных: " << objects_manager->getCounterRedObjects() << "                                        |" << std::endl \
              << "+------------------------------------------------------------+" << std::endl;
}


void Menu::printMenu() {
    //Постоянное обновление меню
    while (isRun){
        std::cout << table;
        printCounters();
        //Очистка консоли
        std::cout << "\x1B[2J\x1B[H";
        //Засыпание потока
        std::this_thread::sleep_for(std::chrono::milliseconds(50));    
    }
}
