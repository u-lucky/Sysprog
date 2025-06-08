#include <iostream>
#include <string>

using namespace std;

class Session {  // дополнительный класс "Сеанс"
private:
    string date;
    string time;
    string movieTitle;

public:
    // методы для получения данных
    string getDate() { return date; }
    string getTime() { return time; }
    string getMovieTitle() { return movieTitle; }

    // методы для установки данных (перегрузка методов)
    void setData() {
        cout << "Enter date (DD.MM.YYYY): ";
        getline(cin, date);
        cout << "Enter time (HH:MM): ";
        getline(cin, time);
        cout << "Enter movie title: ";
        getline(cin, movieTitle);
    }

    void setData(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
    }
};

class Cinema {  // основной класс "Кинотеатр"
private:
    string name;
    string address;
    Session sessions[10];  // массив объектов класса Session
    int sessionCount = 0;  // счетчик добавленных сеансов

public:
    // методы для получения данных
    string getName() { return name; }
    string getAddress() { return address; }

    // методы для установки данных
    void setName(string n) { name = n; }
    void setAddress(string a) { address = a; }

    // метод для добавления сеанса в массив
    void addSession(Session s) {
        if (sessionCount < 10) {
            sessions[sessionCount] = s;
            sessionCount++;
        } else {
            cout << "Maximum number of sessions reached!" << endl;
        }
    }

    // метод для получения информации о сеансе по индексу
    Session getSession(int index) {
        if (index >= 0 && index < sessionCount) {
            return sessions[index];
        } else {
            cout << "Invalid session index!" << endl;
            return Session();  // возвращаем пустой объект
        }
    }

    // метод для получения количества сеансов
    int getSessionCount() { return sessionCount; }
};

int main() {
    Cinema cinema;  // создаем объект кинотеатра
    string input;

    // вводим данные о кинотеатре
    cout << "Enter cinema name: ";
    getline(cin, input);
    cinema.setName(input);

    cout << "Enter cinema address: ";
    getline(cin, input);
    cinema.setAddress(input);

    // добавляем сеансы (5 с помощью первого метода и 5 с помощью второго)
    for (int i = 0; i < 5; i++) {
        cout << "\nAdding session " << i + 1 << " (interactive mode):" << endl;
        Session s;
        s.setData();  // используем первый метод setData()
        cinema.addSession(s);
    }

    for (int i = 5; i < 10; i++) {
        cout << "\nAdding session " << i + 1 << " (direct mode):" << endl;
        Session s;
        s.setData("01.01.2023", "12:00", "Movie " + to_string(i + 1));  // используем второй метод setData()
        cinema.addSession(s);
    }

    // выводим информацию о кинотеатре и всех сеансах
    cout << "\n=== Cinema Information ===" << endl;
    cout << "Name: " << cinema.getName() << endl;
    cout << "Address: " << cinema.getAddress() << endl;
    cout << "\n=== Sessions ===" << endl;

    for (int i = 0; i < cinema.getSessionCount(); i++) {
        Session s = cinema.getSession(i);
        cout << "Session " << i + 1 << ":" << endl;
        cout << "  Movie: " << s.getMovieTitle() << endl;
        cout << "  Date: " << s.getDate() << endl;
        cout << "  Time: " << s.getTime() << endl;
        cout << endl;
    }

    return 0;
}