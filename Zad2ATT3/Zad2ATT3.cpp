#include <iostream>
#include <string>
#include <locale>

// Структура для представления автомобиля
struct Car {
    std::string brand;
    std::string model;
    int year;

    union CarInfo {
        int doorCount;       // Количество дверей (для хэтчей)
        int seatCount;       // Количество мест (для внедорожников)
        int maxSpeed;        // Максимальная скорость (для спортивных автомобилей)
    } info;

    Car* next; // Указатель на следующий автомобиль в списке
};

// Класс базы данных
class Database {
private:
    Car* head; // Указатель на начало списка

public:
    Database() : head(nullptr) {} // Конструктор

    // Добавление нового автомобиля в базу данных
    void addCar(const std::string& brand, const std::string& model, int year, int type) {
        Car* newCar = new Car;
        newCar->brand = brand;
        newCar->model = model;
        newCar->year = year;
        newCar->next = nullptr;

        switch (type) {
        case 1:
            std::cout << "Введите количество дверей: ";
            std::cin >> newCar->info.doorCount;
            break;
        case 2:
            std::cout << "Введите количество мест: ";
            std::cin >> newCar->info.seatCount;
            break;
        case 3:
            std::cout << "Введите максимальную скорость: ";
            std::cin >> newCar->info.maxSpeed;
            break;
        default:
            std::cout << "Некорректный тип автомобиля.\n";
            delete newCar;
            return;
        }

        if (head == nullptr) {
            // Если список пустой, новый автомобиль становится началом списка
            head = newCar;
        }
        else {
            // Иначе, добавляем новый автомобиль в конец списка
            Car* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newCar;
        }

        std::cout << "Автомобиль успешно добавлен в базу данных.\n";
    }

    // Удаление автомобиля из базы данных
    void removeCar(const std::string& brand, const std::string& model, int year) {
        if (head == nullptr) {
            std::cout << "База данных пуста.\n";
            return;
        }

        if (head->brand == brand && head->model == model && head->year == year) {
            // Если удаляемый автомобиль находится в начале списка
            Car* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Автомобиль успешно удален из базы данных.\n";
            return;
        }

        Car* current = head;
        while (current->next != nullptr && (current->next->brand != brand || current->next->model != model || current->next->year != year)) {
            current = current->next;
        }

        if (current->next == nullptr) {
            // Автомобиль не найден в базе данных
            std::cout << "Автомобиль с указанными параметрами не найден.\n";
            return;
        }

        // Автомобиль найден и находится в середине или в конце списка
        Car* temp = current->next;
        current->next = current->next->next;
        delete temp;
        std::cout << "Автомобиль успешно удален из базы данных.\n";
    }

    // Вывод всех автомобилей в базе данных
    void displayCars() {
        if (head == nullptr) {
            std::cout << "База данных пуста.\n";
            return;
        }

        std::cout << "Список автомобилей в базе данных:\n";
        Car* current = head;
        while (current != nullptr) {
            std::cout << "Марка: " << current->brand << ", Модель: " << current->model << ", Год: " << current->year;

            if (current->info.doorCount) {
                std::cout << ", Количество дверей: " << current->info.doorCount;
            }
            else if (current->info.seatCount) {
                std::cout << ", Количество мест: " << current->info.seatCount;
            }
            else if (current->info.maxSpeed) {
                std::cout << ", Максимальная скорость: " << current->info.maxSpeed;
            }

            std::cout << "\n";
            current = current->next;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    Database database;

    while (true) {
        std::cout << "Выберите операцию:\n";
        std::cout << "1. Добавить автомобиль\n";
        std::cout << "2. Удалить автомобиль\n";
        std::cout << "3. Вывести все автомобили\n";
        std::cout << "4. Выйти\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Введите марку автомобиля: ";
            std::string brand;
            std::cin.ignore();
            std::getline(std::cin, brand);

            std::cout << "Введите модель автомобиля: ";
            std::string model;
            std::getline(std::cin, model);

            std::cout << "Введите год выпуска автомобиля: ";
            int year;
            std::cin >> year;

            std::cout << "Выберите тип автомобиля:\n";
            std::cout << "1. Хэтчбек\n";
            std::cout << "2. Внедорожник\n";
            std::cout << "3. Спортивный автомобиль\n";

            int type;
            std::cin >> type;

            database.addCar(brand, model, year, type);
        }
        else if (choice == 2) {
            std::cout << "Введите марку автомобиля для удаления: ";
            std::string brand;
            std::cin.ignore();
            std::getline(std::cin, brand);

            std::cout << "Введите модель автомобиля для удаления: ";
            std::string model;
            std::getline(std::cin, model);

            std::cout << "Введите год выпуска автомобиля для удаления: ";
            int year;
            std::cin >> year;

            database.removeCar(brand, model, year);
        }
        else if (choice == 3) {
            database.displayCars();
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Некорректный выбор операции. Попробуйте снова.\n";
        }

        std::cout << "\n";
    }

    return 0;
}


