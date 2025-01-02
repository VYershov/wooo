#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Класс одной задачи
class Task {
private:
    string title;
    string description;
    bool isCompleted;
    string dateAdded;

public:
    // Конструктор
    Task(string t, string d, bool c = false) : title(t), description(d), isCompleted(c) {
        // Получение текущей даты
        time_t now = time(0);
        tm* ltm = localtime(&now);
        dateAdded = to_string(ltm->tm_mday) + "." +
                    to_string(1 + ltm->tm_mon) + "." +
                    to_string(1900 + ltm->tm_year);
    }

    // Методы доступа
    string getTitle() { return title; }
    string getDescription() { return description; }
    bool getStatus() { return isCompleted; }
    string getDateAdded() { return dateAdded; }

    // Редактирование задачи
    void editTask(string t, string d) {
        title = t;
        description = d;
    }

    // Изменение статуса задачи
    void markCompleted() { isCompleted = true; }
    void markUncompleted() { isCompleted = false; }

    // Печать задачи
    void printTask() {
        cout << "Задача: " << title << endl;
        cout << "Описание: " << description << endl;
        cout << "Статус: " << (isCompleted ? "Выполнено" : "Не выполнено") << endl;
        cout << "Дата добавления: " << dateAdded << endl;
    }
};

// Класс менеджера задач
class ToDoManager {
private:
    vector<Task> tasks;

public:
    // Добавление задачи
    void addTask(string title, string description) {
        tasks.push_back(Task(title, description));
        cout << "Задача добавлена!" << endl;
    }

    // Удаление задачи
    void deleteTask(int index) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Неверный индекс!" << endl;
            return;
        }
        tasks.erase(tasks.begin() + index);
        cout << "Задача удалена!" << endl;
    }

    // Печать всех задач
    void showTasks() {
        if (tasks.empty()) {
            cout << "Список задач пуст!" << endl;
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << "[" << i + 1 << "]" << endl;
            tasks[i].printTask();
            cout << "--------------------" << endl;
        }
    }

    // Редактирование задачи

    void editTask(int index, string title, string description) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Неверный индекс!" << endl;
            return;
        }
        tasks[index].editTask(title, description);
        cout << "Задача успешно изменена!" << endl;
    }

    // Сохранение списка в файл
    void saveToFile(string fileName) {
        ofstream file(fileName);
        if (!file) {
            cout << "Ошибка сохранения файла!" << endl;
            return;
        }
        for (auto& task : tasks) {
            file << task.getTitle() << ";" << task.getDescription() << ";"
                 << task.getStatus() << ";" << task.getDateAdded() << "\n";
        }
        file.close();
        cout << "Список задач сохранён в файл: " << fileName << endl;
    }

    // Загрузка списка из файла
    void loadFromFile(string fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "Ошибка загрузки файла!" << endl;
            return;
        }
        tasks.clear();
        string title, description, status, date;
        while (getline(file, title, ';') &&
               getline(file, description, ';') &&
               getline(file, status, ';') &&
               getline(file, date)) {
            bool isCompleted = (status == "1");
            Task task(title, description, isCompleted);
            tasks.push_back(task);
        }
        file.close();
        cout << "Список задач загружен из файла: " << fileName << endl;
    }
};

// Главная функция
int main() {
    ToDoManager manager;
    int choice;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Показать все задачи\n";
        cout << "2. Добавить задачу\n";
        cout << "3. Редактировать задачу\n";
        cout << "4. Удалить задачу\n";
        cout << "5. Сохранить задачи\n";
        cout << "6. Загрузить задачи\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            manager.showTasks();
        } else if (choice == 2) {
            string title, description;
            cout << "Введите название задачи: ";
            cin.ignore();
            getline(cin, title);
            cout << "Введите описание задачи: ";
            getline(cin, description);
            manager.addTask(title, description);
        } else if (choice == 3) {
            int index;
            string title, description;
            cout << "Введите номер задачи для редактирования: ";
            cin >> index;
            cout << "Введите новое название задачи: ";
            cin.ignore();
            getline(cin, title);
            cout << "Введите новое описание задачи: ";
            getline(cin, description);
            manager.editTask(index - 1, title, description);
        } else if (choice == 4) {
            int index;
            cout << "Введите номер задачи для удаления: ";
            cin >> index;
            manager.deleteTask(index - 1);
        } else if (choice == 5) {
            string fileName;
            cout << "Введите имя файла: ";
            cin >> fileName;
            manager.saveToFile(fileName);
        } else if (choice == 6) {
            string fileName;
            cout << "Введите имя файла: ";
            cin >> fileName;
            manager.loadFromFile(fileName);
        } else if (choice == 0) {
            break;
        } else {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    return 0;
}
