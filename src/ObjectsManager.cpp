#include "ObjectsManager.h"

//Инициализация статических счетчиков
int ObjectsManager::counter_generated_objects = 0;
int ObjectsManager::counter_sorted_objects = 0;
int ObjectsManager::counter_red_objects = 0;
int ObjectsManager::counter_green_objects = 0;
int ObjectsManager::counter_blue_objects = 0;


ObjectsManager::ObjectsManager() {
    isRunGeneration = false;
    isRunSorting = false;
}

ObjectsManager::~ObjectsManager() {
    isRunGeneration = false;
    isRunSorting = false;

    //Завершение потока генерации
    if (generate.joinable()){
        generate.join();
    }
    //Завершение потока сортировки
    if (sort.joinable()){
        sort.join();
    }
}

void ObjectsManager::startGenerateObjects() {
    isRunGeneration = true;
    //Создание потока генерации
    if (!generate.joinable())
        generate = std::thread(&ObjectsManager::generateObjects, this);
}

void ObjectsManager::stopGenerateObjects() {
    isRunGeneration = false;
    //Завершение потока генерации
    if (generate.joinable()){
        generate.join();
    }
}

void ObjectsManager::startSortObjects() {
    isRunSorting = true;
    //Создание потока сортировки
    if (!sort.joinable())
        sort = std::thread(&ObjectsManager::sortObjects, this);
}

void ObjectsManager::stopSortObjects() {
    isRunSorting = false;
    //Завершение потока сортировки
    if (sort.joinable()){
        sort.join();
    }
}

//Геттеры
int ObjectsManager::getCounterGeneratedObjects() const {
    return counter_generated_objects;
}

int ObjectsManager::getCounterSortedObjects() const {
    return counter_sorted_objects;
}

int ObjectsManager::getCounterRedObjects() const {
    return counter_red_objects;
}

int ObjectsManager::getCounterGreenObjects() const {
    return counter_green_objects;
}

int ObjectsManager::getCounterBlueObjects() const {
    return counter_blue_objects;
}

std::queue<std::shared_ptr<SimpleObj> >  ObjectsManager::getObjects() const {
    return objects;
}

std::map<int, std::vector<std::shared_ptr<SimpleObj> > >  ObjectsManager::getSortedObjects() const {
    return sorted_objects;
}

//Получение отсортированных объектов в виде массива
std::vector<std::shared_ptr<SimpleObj> > ObjectsManager::getArraySortedObjects() const {
    //Массив, в котором будут храниться отсортированные объекты
    std::vector<std::shared_ptr<SimpleObj> > array_sorted_objects;
    
    //Перенос объектов из map в массив
    for (auto& object : sorted_objects) {
        array_sorted_objects.insert(std::end(array_sorted_objects), 
                                        std::begin(object.second), std::end(object.second));
    }

    return array_sorted_objects;
}
//Сеттеры
void ObjectsManager::setCounterGeneratedObjects(int counter) noexcept {
    counter_generated_objects = counter;
}

void ObjectsManager::setCounterSortedObjects(int counter) noexcept {
    counter_sorted_objects = counter;
}

void ObjectsManager::setCounterRedObjects(int counter) noexcept {
    counter_red_objects = counter;
}

void ObjectsManager::setCounterGreenObjects(int counter) noexcept {
    counter_green_objects = counter;
}

void ObjectsManager::setCounterBlueObjects(int counter) noexcept {
    counter_blue_objects = counter;
}

void ObjectsManager::addToObjects(std::vector<std::shared_ptr<SimpleObj> > objects) {
    //Добавление объектов в массив сгенерированных объектов
    for (auto object : objects) {
        this->objects.push(object);
    }
    counter_generated_objects += objects.size();
}

void ObjectsManager::generateObjects() {
    while (isRunGeneration) {
        //Создание объекта
        std::shared_ptr<SimpleObj> object = std::make_shared<SimpleObj>();
        //Добавление сгенерированного объекта в очередь
        objects.push(object);
        //Инкрементировать счетчик сгенерированных объектов
        counter_generated_objects += 1;
        //Остановка потока, для более наглядного создания объектов(можно убрать)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));    
    }
}

void ObjectsManager::sortObjects() {
    while (isRunSorting) {
        //Если есть сгенерированные объекты
        if (!objects.empty()) {
            //Получить цвет объекта
            Colors color = objects.front()->getColor();
            //Добавление объекта в map в зависимости от его цвета
            sorted_objects[color].push_back(objects.front());
            //Удалить объект из сгенерированных объектов
            objects.pop(); 
            counter_sorted_objects += 1;

            //В зависимости от цвета объекта, инкрементировать нужный счетчик
            if (color == GREEN)
                counter_green_objects += 1;
            else if (color == BLUE)
                counter_blue_objects += 1;
            else if (color == RED)
                counter_red_objects += 1;

        }
    }
}