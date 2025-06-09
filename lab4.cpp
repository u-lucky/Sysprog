#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Session {  // абстрактный базовый класс "Сеанс"
protected:
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
    
    // виртуальный деструктор
    virtual ~Session() {
        cout << "Session: Destructor" << endl;
    }

    // методы для получения данных
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getMovieTitle() const { return movieTitle; }

    // методы для установки данных
    void setData(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
    }

    // чисто виртуальная функция (делаем класс абстрактным)
    virtual void printDetailedInfo() const = 0;
    
    // виртуальная функция для базовой информации
    virtual void printBasicInfo() const {
        cout << "Movie: " << movieTitle << " (Date: " << date << ", Time: " << time << ")";
    }
};

class Booking : public Session {  // класс-наследник "Бронирование"
private:
    string customerName;
    string phoneNumber;
    int seatNumber;
    bool isConfirmed;

public:
    // конструкторы
    Booking() : Session() {
        customerName = "No name";
        phoneNumber = "No phone";
        seatNumber = 0;
        isConfirmed = false;
        cout << "Booking: Default constructor" << endl;
    }
    
    Booking(string d, string t, string mt, string cn, string pn, int sn) 
        : Session(d, t, mt) {
        customerName = cn;
        phoneNumber = pn;
        seatNumber = sn;
        isConfirmed = false;
        cout << "Booking: Constructor with parameters" << endl;
    }
    
    Booking(const Booking &b) : Session(b) {
        customerName = b.customerName;
        phoneNumber = b.phoneNumber;
        seatNumber = b.seatNumber;
        isConfirmed = b.isConfirmed;
        cout << "Booking: Copy constructor" << endl;
    }
    
    // деструктор
    ~Booking() {
        cout << "Booking: Destructor" << endl;
    }

    // методы
    void confirmBooking() {
        isConfirmed = true;
    }

    // переопределение чисто виртуальной функции
    void printDetailedInfo() const override {
        cout << "=== Booking Details ===" << endl;
        printBasicInfo();
        cout << "\nCustomer: " << customerName 
             << "\nPhone: " << phoneNumber
             << "\nSeat: " << seatNumber
             << "\nStatus: " << (isConfirmed ? "Confirmed" : "Pending") << endl;
    }
};

class PaidTicket : public Session {  // класс-наследник "Оплаченный билет"
private:
    string ticketNumber;
    float price;
    string paymentMethod;

public:
    // конструкторы
    PaidTicket() : Session() {
        ticketNumber = "000000";
        price = 0.0f;
        paymentMethod = "Cash";
        cout << "PaidTicket: Default constructor" << endl;
    }
    
    PaidTicket(string d, string t, string mt, string tn, float p, string pm) 
        : Session(d, t, mt) {
        ticketNumber = tn;
        price = p;
        paymentMethod = pm;
        cout << "PaidTicket: Constructor with parameters" << endl;
    }
    
    PaidTicket(const PaidTicket &pt) : Session(pt) {
        ticketNumber = pt.ticketNumber;
        price = pt.price;
        paymentMethod = pt.paymentMethod;
        cout << "PaidTicket: Copy constructor" << endl;
    }
    
    // деструктор
    ~PaidTicket() {
        cout << "PaidTicket: Destructor" << endl;
    }

    // переопределение чисто виртуальной функции
    void printDetailedInfo() const override {
        cout << "=== Paid Ticket Details ===" << endl;
        printBasicInfo();
        cout << "\nTicket #: " << ticketNumber
             << "\nPrice: " << price << " RUB"
             << "\nPayment method: " << paymentMethod << endl;
    }
};

class Cinema {  // основной класс "Кинотеатр"
private:
    string name;
    string address;
    vector<Session*> sessions;  // вектор указателей на базовый класс

public:
    // конструкторы
    Cinema() {
        name = "No name";
        address = "No address";
        cout << "Cinema: Default constructor" << endl;
    }
    
    Cinema(string n, string a) : name(n), address(a) {
        cout << "Cinema: Constructor with parameters" << endl;
    }
    
    // деструктор
    ~Cinema() {
        // освобождаем память для всех сеансов
        for (auto session : sessions) {
            delete session;
        }
        cout << "Cinema: Destructor" << endl;
    }

    // методы для работы с сеансами
    void addSession(Session* s) {
        sessions.push_back(s);
    }

    void printAllSessions() const {
        cout << "\n=== All Sessions at " << name << " (" << address << ") ===" << endl;
        for (size_t i = 0; i < sessions.size(); ++i) {
            cout << "\nSession #" << i+1 << ":" << endl;
            sessions[i]->printDetailedInfo();
        }
    }
    
    // метод для демонстрации полиморфизма
    void demonstratePolymorphism() const {
        cout << "\n=== Polymorphism Demonstration ===" << endl;
        for (auto session : sessions) {
            cout << "\nSession type: ";
            session->printBasicInfo();
            cout << endl;
        }
    }
};

int main() {
    cout << "============= Step 1: Creating objects =============" << endl;
    // не можем создать объект абстрактного класса Session
    // Session session1;  // ошибка компиляции
    
    // создаем объекты классов-наследников
    Booking* booking1 = new Booking("26.05.2023", "20:30", "Fast X", 
                                  "Ivan Ivanov", "+79123456789", 15);
    PaidTicket* ticket1 = new PaidTicket("27.05.2023", "15:45", 
                                       "The Little Mermaid", "T123456", 
                                       350.0f, "Credit Card");
    
    cout << "\n============= Step 2: Working with base class array =============" << endl;
    // создаем массив указателей на базовый класс
    vector<Session*> sessionArray;
    sessionArray.push_back(new Booking(*booking1));
    sessionArray.push_back(new PaidTicket(*ticket1));
    sessionArray.push_back(new Booking("28.05.2023", "22:00", "John Wick 4", 
                                     "Petr Petrov", "+79876543210", 22));
    sessionArray.push_back(new PaidTicket("29.05.2023", "12:00", "Avatar 2", 
                                        "T654321", 450.0f, "Online Payment"));
    
    // выводим информацию через массив базового класса (полиморфизм)
    for (size_t i = 0; i < sessionArray.size(); ++i) {
        cout << "\nElement #" << i+1 << ":" << endl;
        sessionArray[i]->printDetailedInfo();
    }
    
    cout << "\n============= Step 3: Working with Cinema class =============" << endl;
    Cinema cinema("Star Cinema", "Main Street 123");
    
    // добавляем сеансы разных типов
    cinema.addSession(new Booking(*booking1));
    cinema.addSession(new PaidTicket(*ticket1));
    cinema.addSession(new Booking("30.05.2023", "18:15", "The Batman", 
                                "Anna Sergeeva", "+79031112233", 12));
    cinema.addSession(new PaidTicket("31.05.2023", "21:30", "Dune", 
                                   "T987654", 400.0f, "Gift Card"));
    
    // выводим информацию о всех сеансах
    cinema.printAllSessions();
    
    // демонстрируем полиморфизм
    cinema.demonstratePolymorphism();
    
    cout << "\n============= Cleaning up =============" << endl;
    // освобождаем память
    delete booking1;
    delete ticket1;
    
    for (auto session : sessionArray) {
        delete session;
    }
    
    cout << "============= End of program =============" << endl;
    return 0;
}