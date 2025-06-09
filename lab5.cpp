#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Session {
protected:
    string date;
    string time;
    string movieTitle;

private:
    static int objectCount;  // счетчик созданных объектов

public:
    // конструктор по умолчанию
    Session() {
        date = "01.01.1970";
        time = "00:00";
        movieTitle = "No title";
        objectCount++;
        cout << "Session: Default constructor" << endl;
    }

    // конструктор с параметрами
    Session(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
        objectCount++;
        cout << "Session: Constructor with parameters" << endl;
    }

    // конструктор копирования
    Session(const Session &s) {
        date = s.date;
        time = s.time;
        movieTitle = s.movieTitle;
        objectCount++;
        cout << "Session: Copy constructor" << endl;
    }

    // виртуальный деструктор
    virtual ~Session() {
        objectCount--;
        cout << "Session: Destructor" << endl;
    }

    // статический метод для получения количества объектов
    static int getObjectCount() {
        return objectCount;
    }

    // методы доступа к данным
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getMovieTitle() const { return movieTitle; }

    // методы установки данных
    void setData(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
    }

    // чисто виртуальная функция
    virtual void printDetailedInfo() const = 0;

    // виртуальная функция базовой информации
    virtual void printBasicInfo() const {
        cout << "Movie: " << movieTitle << " (Date: " << date << ", Time: " << time << ")";
    }
};

// инициализация статической переменной
int Session::objectCount = 0;

class Booking : public Session {
private:
    string customerName;
    string phoneNumber;
    int seatNumber;
    bool isConfirmed;

public:
    // конструктор по умолчанию
    Booking() : Session() {
        customerName = "No name";
        phoneNumber = "No phone";
        seatNumber = 0;
        isConfirmed = false;
        cout << "Booking: Default constructor" << endl;
    }

    // конструктор с параметрами
    Booking(string d, string t, string mt, string cn, string pn, int sn)
        : Session(d, t, mt) {
        customerName = cn;
        phoneNumber = pn;
        seatNumber = sn;
        isConfirmed = false;
        cout << "Booking: Constructor with parameters" << endl;
    }

    // конструктор копирования
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

    // метод подтверждения бронирования
    void confirmBooking() {
        isConfirmed = true;
    }

    // реализация виртуальной функции
    void printDetailedInfo() const override {
        cout << "=== Booking Details ===" << endl;
        printBasicInfo();
        cout << "\nCustomer: " << customerName
             << "\nPhone: " << phoneNumber
             << "\nSeat: " << seatNumber
             << "\nStatus: " << (isConfirmed ? "Confirmed" : "Pending") << endl;
    }
};

class PaidTicket : public Session {
private:
    string ticketNumber;
    float price;
    string paymentMethod;

public:
    // конструктор по умолчанию
    PaidTicket() : Session() {
        ticketNumber = "000000";
        price = 0.0f;
        paymentMethod = "Cash";
        cout << "PaidTicket: Default constructor" << endl;
    }

    // конструктор с параметрами
    PaidTicket(string d, string t, string mt, string tn, float p, string pm)
        : Session(d, t, mt) {
        ticketNumber = tn;
        price = p;
        paymentMethod = pm;
        cout << "PaidTicket: Constructor with parameters" << endl;
    }

    // конструктор копирования
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

    // реализация виртуальной функции
    void printDetailedInfo() const override {
        cout << "=== Paid Ticket Details ===" << endl;
        printBasicInfo();
        cout << "\nTicket #: " << ticketNumber
             << "\nPrice: " << price << " RUB"
             << "\nPayment method: " << paymentMethod << endl;
    }
};

class Cinema {
private:
    string name;
    string address;
    vector<Session*> sessions;
    static int storedSessionCount;  // счетчик сохраненных сеансов

public:
    // конструктор по умолчанию
    Cinema() {
        name = "No name";
        address = "No address";
        cout << "Cinema: Default constructor" << endl;
    }

    // конструктор с параметрами
    Cinema(string n, string a) : name(n), address(a) {
        cout << "Cinema: Constructor with parameters" << endl;
    }

    // деструктор
    ~Cinema() {
        for (auto session : sessions) {
            delete session;
        }
        cout << "Cinema: Destructor" << endl;
    }

    // метод добавления сеанса
    void addSession(Session* s) {
        sessions.push_back(s);
        storedSessionCount++;
    }

    // статический метод для получения количества сеансов
    static int getStoredSessionCount() {
        return storedSessionCount;
    }

    // метод вывода информации о всех сеансах
    void printAllSessions() const {
        cout << "\n=== All Sessions at " << name << " (" << address << ") ===" << endl;
        for (size_t i = 0; i < sessions.size(); ++i) {
            cout << "\nSession #" << i+1 << ":" << endl;
            sessions[i]->printDetailedInfo();
        }
    }

    // демонстрация полиморфизма
    void demonstratePolymorphism() const {
        cout << "\n=== Polymorphism Demonstration ===" << endl;
        for (auto session : sessions) {
            cout << "\nSession type: ";
            session->printBasicInfo();
            cout << endl;
        }
    }
};

// инициализация статической переменной
int Cinema::storedSessionCount = 0;

int main() {
    cout << "\n============= Initial Counts =============" << endl;
    cout << "Session count: " << Session::getObjectCount() << endl;
    cout << "Stored sessions in Cinema: " << Cinema::getStoredSessionCount() << endl;

    // создание объектов
    Booking* booking1 = new Booking("26.05.2023", "20:30", "Fast X", "Ivan Ivanov", "+79123456789", 15);
    PaidTicket* ticket1 = new PaidTicket("27.05.2023", "15:45", "The Little Mermaid", "T123456", 350.0f, "Credit Card");

    // работа с кинотеатром
    Cinema cinema("Star Cinema", "Main Street 123");
    cinema.addSession(new Booking(*booking1));
    cinema.addSession(new PaidTicket(*ticket1));
    cinema.addSession(new Booking("30.05.2023", "18:15", "The Batman", "Anna Sergeeva", "+79031112233", 12));
    cinema.addSession(new PaidTicket("31.05.2023", "21:30", "Dune", "T987654", 400.0f, "Gift Card"));

    cout << "\n============= After Creating Objects =============" << endl;
    cout << "Session count: " << Session::getObjectCount() << endl;
    cout << "Stored sessions in Cinema: " << Cinema::getStoredSessionCount() << endl;

    // вывод информации
    cinema.printAllSessions();
    cinema.demonstratePolymorphism();

    // освобождение памяти
    delete booking1;
    delete ticket1;

    cout << "\n============= End of program =============" << endl;
    return 0;
}