#include <iostream>
#include <string>

using namespace std;

class Session {  // базовый класс "Сеанс"
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
    
    // деструктор
    virtual ~Session() {
        cout << "Session: Destructor" << endl;
    }

    // методы для получения данных
    string getDate() { return date; }
    string getTime() { return time; }
    string getMovieTitle() { return movieTitle; }

    // методы для установки данных
    void setData(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
    }

    // виртуальный метод для вывода информации
    virtual void printInfo() {
        cout << "Session Info:" << endl;
        cout << "  Movie: " << movieTitle << endl;
        cout << "  Date: " << date << endl;
        cout << "  Time: " << time << endl;
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

    // переопределение метода вывода информации
    void printInfo() override {
        Session::printInfo();
        cout << "  Type: Booking" << endl;
        cout << "  Customer: " << customerName << endl;
        cout << "  Phone: " << phoneNumber << endl;
        cout << "  Seat: " << seatNumber << endl;
        cout << "  Status: " << (isConfirmed ? "Confirmed" : "Pending") << endl;
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

    // переопределение метода вывода информации
    void printInfo() override {
        Session::printInfo();
        cout << "  Type: Paid Ticket" << endl;
        cout << "  Ticket #: " << ticketNumber << endl;
        cout << "  Price: " << price << endl;
        cout << "  Payment method: " << paymentMethod << endl;
    }
};

class Cinema {  // основной класс "Кинотеатр"
private:
    string name;
    string address;
    Session* sessions[10];  // массив указателей на базовый класс
    int sessionCount = 0;

public:
    // конструкторы и деструкторы
    Cinema() {
        name = "No name";
        address = "No address";
        cout << "Cinema: Default constructor" << endl;
    }
    
    Cinema(string n, string a) {
        name = n;
        address = a;
        cout << "Cinema: Constructor with parameters" << endl;
    }
    
    ~Cinema() {
        // освобождаем память для всех сеансов
        for (int i = 0; i < sessionCount; i++) {
            delete sessions[i];
        }
        cout << "Cinema: Destructor" << endl;
    }

    // методы для работы с сеансами
    void addSession(Session* s) {
        if (sessionCount < 10) {
            sessions[sessionCount] = s;
            sessionCount++;
        } else {
            cout << "Maximum number of sessions reached!" << endl;
        }
    }

    void printAllSessions() {
        cout << "\n=== All Sessions at " << name << " ===" << endl;
        for (int i = 0; i < sessionCount; i++) {
            cout << "Session #" << i+1 << ":" << endl;
            sessions[i]->printInfo();
            cout << endl;
        }
    }
};

int main() {
    cout << "============= Step 1: Creating objects =============" << endl;
    // создаем объекты базового класса
    Session session1;
    Session session2("25.05.2023", "19:00", "Guardians of the Galaxy Vol. 3");
    
    // создаем объекты классов-наследников
    Booking booking1("26.05.2023", "20:30", "Fast X", "Ivan Ivanov", "+79123456789", 15);
    PaidTicket ticket1("27.05.2023", "15:45", "The Little Mermaid", "T123456", 350.0f, "Credit Card");
    
    cout << "\n============= Step 2: Working with base class array =============" << endl;
    // создаем массив базового класса (указателей)
    Session* sessionArray[4];
    sessionArray[0] = new Session(session1);
    sessionArray[1] = new Session(session2);
    sessionArray[2] = new Booking(booking1);
    sessionArray[3] = new PaidTicket(ticket1);
    
    // выводим информацию через массив базового класса
    for (int i = 0; i < 4; i++) {
        cout << "Element #" << i+1 << ":" << endl;
        sessionArray[i]->printInfo();
        cout << endl;
    }
    
    cout << "\n============= Step 3: Working with derived class array =============" << endl;
    // создаем массив класса-наследника Booking
    Booking bookingArray[2];
    bookingArray[0] = booking1;
    bookingArray[1] = Booking("28.05.2023", "22:00", "John Wick 4", "Petr Petrov", "+79876543210", 22);
    
    // выводим информацию через массив класса-наследника
    for (int i = 0; i < 2; i++) {
        cout << "Booking #" << i+1 << ":" << endl;
        bookingArray[i].printInfo();
        cout << endl;
    }
    
    cout << "\n============= Step 4: Working with Cinema class =============" << endl;
    Cinema cinema("Star Cinema", "Main Street 123");
    cinema.addSession(new Session(session2));
    cinema.addSession(new Booking(booking1));
    cinema.addSession(new PaidTicket(ticket1));
    cinema.printAllSessions();
    
    cout << "============= Cleaning up =============" << endl;
    // освобождаем память
    for (int i = 0; i < 4; i++) {
        delete sessionArray[i];
    }
    
    cout << "============= End of program =============" << endl;
    return 0;
}