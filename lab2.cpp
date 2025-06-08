#include <iostream>
#include <string>

using namespace std;

class Session {  // дополнительный класс "Сеанс"
private:
    string date;
    string time;
    string movieTitle;

public:
    // конструкторы
    Session() {  // конструктор по умолчанию
        date = "01.01.1970";
        time = "00:00";
        movieTitle = "No title";
        cout << "Session: Default constructor" << endl;
    }
    
    Session(string d, string t, string mt) {  // конструктор с параметрами
        date = d;
        time = t;
        movieTitle = mt;
        cout << "Session: Constructor with parameters" << endl;
    }
    
    Session(const Session &s) {  // конструктор копирования
        date = s.date;
        time = s.time;
        movieTitle = s.movieTitle;
        cout << "Session: Copy constructor" << endl;
    }
    
    // деструктор
    ~Session() {
        cout << "Session: Destructor" << endl;
    }

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
    // конструкторы
    Cinema() {  // конструктор по умолчанию
        name = "No name";
        address = "No address";
        cout << "Cinema: Default constructor" << endl;
    }
    
    Cinema(string n, string a) {  // конструктор с параметрами
        name = n;
        address = a;
        cout << "Cinema: Constructor with parameters" << endl;
    }
    
    Cinema(const Cinema &c) {  // конструктор копирования
        name = c.name;
        address = c.address;
        sessionCount = c.sessionCount;
        for (int i = 0; i < sessionCount; i++) {
            sessions[i] = c.sessions[i];
        }
        cout << "Cinema: Copy constructor" << endl;
    }
    
    // деструктор
    ~Cinema() {
        cout << "Cinema: Destructor" << endl;
    }

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
    
    // новый метод (пункт 5 задания) - создает объект Session с параметрами и добавляет в массив
    void addNewSession(string date, string time, string title, int index) {
        if (index >= 0 && index < 10) {
            Session newSession(date, time, title);  // создание с конструктором с параметрами
            sessions[index] = newSession;
            if (index >= sessionCount) {
                sessionCount = index + 1;
            }
        } else {
            cout << "Invalid index!" << endl;
        }
    }
    
    // новый метод (пункт 6 задания) - создает копии объекта и добавляет в массив
    void addCopiedSessions(const Session &s, int count) {
        for (int i = 0; i < count && sessionCount < 10; i++) {
            Session newSession(s);  // создание с конструктором копирования
            sessions[sessionCount] = newSession;
            sessionCount++;
        }
        if (count > 10 - sessionCount) {
            cout << "Added only " << (10 - sessionCount) << " sessions (max reached)" << endl;
        }
    }
};

int main() {
    cout << "============= Step 1: Creating Cinema objects" << endl;
    Cinema cinema1;  // конструктор по умолчанию
    Cinema cinema2("Star Cinema", "Main Street 123");  // конструктор с параметрами
    Cinema cinema3(cinema2);  // конструктор копирования
    
    cout << "============= Step 2: Creating Session objects" << endl;
    Session session1;  // конструктор по умолчанию
    Session session2("15.05.2023", "18:30", "Avengers: Endgame");  // конструктор с параметрами
    Session session3(session2);  // конструктор копирования
    
    cout << "============= Step 3: Using new methods" << endl;
    // использование нового метода (пункт 5)
    cinema1.addNewSession("20.05.2023", "15:00", "Spider-Man: No Way Home", 0);
    
    // использование нового метода (пункт 6)
    cinema1.addCopiedSessions(session2, 3);
    
    cout << "============= Step 4: Displaying information" << endl;
    // выводим информацию о кинотеатре и всех сеансах
    cout << "\n=== Cinema 1 Information ===" << endl;
    cout << "Name: " << cinema1.getName() << endl;
    cout << "Address: " << cinema1.getAddress() << endl;
    cout << "\n=== Sessions ===" << endl;

    for (int i = 0; i < cinema1.getSessionCount(); i++) {
        Session s = cinema1.getSession(i);
        cout << "Session " << i + 1 << ":" << endl;
        cout << "  Movie: " << s.getMovieTitle() << endl;
        cout << "  Date: " << s.getDate() << endl;
        cout << "  Time: " << s.getTime() << endl;
        cout << endl;
    }
    
    cout << "============= End of program" << endl;
    return 0;
}