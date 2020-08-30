#include <iostream>
#include <thread>
#include <queue>
#include <map>
#include <vector>
#include <memory>

#include "SimpleObj.h"

class ObjectsManager {
public:
    ObjectsManager();
    ~ObjectsManager();

    //Создание потока генерации объектов
    void startGenerateObjects();
    //Создание потока сортировки объектов
    void startSortObjects();

    //Остановить поток генерации объектов
    void stopGenerateObjects();
    //Остановить поток сортировки объектов
    void stopSortObjects();
    
    //Геттеры для получения счетчиков 
    int getCounterGeneratedObjects() const;
    int getCounterSortedObjects() const;
    int getCounterRedObjects() const;
    int getCounterGreenObjects() const;
    int getCounterBlueObjects() const;

    //Сеттеры для изменения значений счетчиков
    void setCounterGeneratedObjects(int counter) noexcept;
    void setCounterSortedObjects(int counter) noexcept;
    void setCounterRedObjects(int counter) noexcept;
    void setCounterGreenObjects(int counter) noexcept;
    void setCounterBlueObjects(int counter) noexcept;

    //Получить сгенерированные объекты (еще не отсортированные)
    std::queue<std::shared_ptr<SimpleObj> >  getObjects() const; 
    //Получить отсортированные объекты
    std::map<int, std::vector<std::shared_ptr<SimpleObj> > >  getSortedObjects() const;
    //Получить отсортированные объекты в виде массива
    std::vector<std::shared_ptr<SimpleObj> > getArraySortedObjects() const;

    //Добавить новые элементы в очередь сгенерированных объектов (не используя поток для генерации)
    void addToObjects(std::vector<std::shared_ptr<SimpleObj> > objects);
private:
    //Генерация объектов
    void generateObjects();
    //Сортировка объектов
    void sortObjects();

private:
    std::queue<std::shared_ptr<SimpleObj> > objects; //Сгенерированные объекты
    std::map<int, std::vector<std::shared_ptr<SimpleObj> > > sorted_objects; //Отсортированные объекты

    bool isRunGeneration; //Запустить генерацию
    bool isRunSorting; //Запустить сортировку

    std::thread generate; //Поток для генерации
    std::thread sort; //Поток для сортировки

    static int counter_generated_objects; //Количество сгенерированных объектов
    static int counter_sorted_objects; //Количество отсортированных объектов
    static int counter_red_objects; //Количество красных объектов
    static int counter_green_objects; //Количество зеленых объектов
    static int counter_blue_objects; //Количество синих объектов

};
