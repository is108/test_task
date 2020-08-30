#include <catch.hpp>

#include "ObjectsManager.h"

TEST_CASE("checking object creation", "[simple object]") {
    std::unique_ptr<SimpleObj> simple_object(new SimpleObj);

    simple_object->setColor(RED);
    REQUIRE( simple_object->getColor() == RED );
}

TEST_CASE("checking create objects using thread", "[objects manager]") {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);
    objects_manager->startGenerateObjects();

    //Ожидание пока объекты сгенерируются
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));    

    std::queue<std::shared_ptr<SimpleObj> > objects = objects_manager->getObjects();

    //Проверка что объекты создались
    REQUIRE(objects.empty() == 0);
}

TEST_CASE("checking set objects in queue", "[objects manager]") {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);
    std::vector<std::shared_ptr<SimpleObj> > objects;

    objects_manager->setCounterGeneratedObjects(0);

    //Создание новых объектов
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<SimpleObj> object = std::make_shared<SimpleObj>();
        objects.push_back(object);
    }

    //Добавление объектов (не используя поток)
    objects_manager->addToObjects(objects);

    REQUIRE(objects_manager->getCounterGeneratedObjects() == 4);
}

TEST_CASE("checking sort objects", "[object manager]") {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);

    //Зеленый объект
    std::shared_ptr<SimpleObj> green_object(new SimpleObj);
    green_object->setColor(GREEN);
    //Красный объект 1
    std::shared_ptr<SimpleObj> red1_object(new SimpleObj);
    red1_object->setColor(RED);
    //Синий объект
    std::shared_ptr<SimpleObj> blue_object(new SimpleObj);
    blue_object->setColor(BLUE);
    //Красный объект 2
    std::shared_ptr<SimpleObj> red2_object(new SimpleObj);
    red2_object->setColor(RED);

    std::vector<std::shared_ptr<SimpleObj> > objects;
    objects.push_back(green_object);
    objects.push_back(red1_object);
    objects.push_back(blue_object);
    objects.push_back(red2_object);

    //Добавление объектов (не используя поток)
    objects_manager->addToObjects(objects);
    //Начать сортировку объектов
    objects_manager->startSortObjects();
    //Ожидание пока объекты отсортируются
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    
    //Получить словарь отсортированных значений
    auto sorted_objects = objects_manager->getSortedObjects();

    REQUIRE(sorted_objects[0].size() == 1);
    REQUIRE(sorted_objects[1].size() == 1);
    REQUIRE(sorted_objects[2].size() == 2);
}

TEST_CASE("checking return array sorted objects ", "[object manager]") {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);

    //Зеленый объект
    std::shared_ptr<SimpleObj> green_object(new SimpleObj);
    green_object->setColor(GREEN);
    //Красный объект 1
    std::shared_ptr<SimpleObj> red1_object(new SimpleObj);
    red1_object->setColor(RED);
    //Синий объект
    std::shared_ptr<SimpleObj> blue_object(new SimpleObj);
    blue_object->setColor(BLUE);
    //Красный объект 2
    std::shared_ptr<SimpleObj> red2_object(new SimpleObj);
    red2_object->setColor(RED);

    std::vector<std::shared_ptr<SimpleObj> > objects;
    objects.push_back(green_object);
    objects.push_back(red1_object);
    objects.push_back(blue_object);
    objects.push_back(red2_object);

    //Добавление объектов (не используя поток)
    objects_manager->addToObjects(objects);
    //Начать сортировку объектов
    objects_manager->startSortObjects();
    //Ожидание пока объекты отсортируются
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    
    //Получить массив отсортированных значений
    auto array_sorted_objects = objects_manager->getArraySortedObjects();

    REQUIRE(array_sorted_objects.size() == 4);
    REQUIRE(array_sorted_objects[0]->getColor() == GREEN);
    REQUIRE(array_sorted_objects[1]->getColor() == BLUE);
    REQUIRE(array_sorted_objects[2]->getColor() == RED);
    REQUIRE(array_sorted_objects[3]->getColor() == RED);
}

TEST_CASE("checking work of objects counters ", "[object manager]") {
    std::unique_ptr<ObjectsManager> objects_manager(new ObjectsManager);

    objects_manager->setCounterGreenObjects(0);
    objects_manager->setCounterBlueObjects(0);
    objects_manager->setCounterRedObjects(0);

    //Зеленый объект 1
    std::shared_ptr<SimpleObj> green1_object(new SimpleObj);
    green1_object->setColor(GREEN);
    //Красный объект 
    std::shared_ptr<SimpleObj> red_object(new SimpleObj);
    red_object->setColor(RED);
    //Синий объект
    std::shared_ptr<SimpleObj> blue_object(new SimpleObj);
    blue_object->setColor(BLUE);
    //Зеленый объект 2
    std::shared_ptr<SimpleObj> green2_object(new SimpleObj);
    green2_object->setColor(GREEN);

    std::vector<std::shared_ptr<SimpleObj> > objects;
    objects.push_back(green1_object);
    objects.push_back(red_object);
    objects.push_back(blue_object);
    objects.push_back(green2_object);

    //Добавление объектов (не используя поток)
    objects_manager->addToObjects(objects);
    //Начать сортировку объектов
    objects_manager->startSortObjects();
    //Ожидание пока объекты отсортируются
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    

    REQUIRE(objects_manager->getCounterGreenObjects() == 2);
    REQUIRE(objects_manager->getCounterBlueObjects() == 1);
    REQUIRE(objects_manager->getCounterRedObjects() == 1);
}