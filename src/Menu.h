#include <iostream>
#include <string>
#include <thread>

#include "ObjectsManager.h"

class Menu {
public:
    Menu();
    ~Menu();
private:
    void printCounters(); //Вывести счетчики
    void printMenu(); //Вывести меню
public:
    //Меню для пользователя, с указаниями как управлять приложением
    const std::string table =                                        \
"+------------------------------------------------------------+\n\
|                                                            |\n\
| 1) Включить генерацию объектов                             |\n\
| 2) Отключить генерацию объектов                            |\n\ 
| 3) Включить сортировку объектов                            |\n\
| 4) Отключить сортировку объектов                           |\n\
| 5) Выйти                                                   |\n\
|                                                            |\n\
| Введите пункт в меню и нажмите Enter.                      |\n\
|                                                            |\n\
+------------------------------------------------------------+\n";
                          
private:
    std::thread print_menu; //Поток для вывода меню
    bool isRun;

    std::unique_ptr<ObjectsManager> objects_manager; 
};