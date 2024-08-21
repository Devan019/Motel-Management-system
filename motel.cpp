#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;
void lines()
{
    cout << "\t";
    for (int i = 0; i < 80; i++)
    {
        cout << "-";
    }
}
string hidepass()
{
    string password;
    char ch;
    while ((ch = getch()) != 13)
    { 
        if (ch == '\b')
        { 
            if (!password.empty())
            {
                cout << "\b \b";     
                password.pop_back(); 
            }
        }
        else
        {
            password.push_back(ch); 
            cout << '*';            
        }
    }
    cout << endl; 
    return password;
}
bool isEmail(string id)
{
    int c = 0, c1 = 0;
    for (int i = 0; i < id.size(); i++)
    {
        if (id[i] == ' ')
        {
            return false;
        }
        else if (id[i] == '@')
        {
            c++;
        }
        else if (id[i] == '.')
        {
            c1++;
        }
    }
    if (c > 0 && c1 > 0)
    {
        return true;
    }
    return false;
}

bool isPhone(string no)
{
    int c = 0;
    for (int i = 0; i < no.size(); i++)
    {
        if (no[i] >= 48 && no[i] <= 58)
        {
            c++;
        }
    }

    if (c == 10)
    {
        return true;
    }
    return false;
}
void help()
{
    cout << "\n\n\t\t\t==> PRESS ENTER TO CONTINUE... ";
    getchar();
}
class ForManager;
class Login
{
public:
    virtual bool sign_in() = 0;
};

class Manager : public Login
{
protected:
    string username;
    string password;

public:
    virtual bool sign_in() override;
};

class Customer : public Login
{
protected:
    string name;
    string email_id;
    string password;
    string phone_no;
    int bill;
    int cus_id;

public:
    Customer(string n = "\0", string id = "\0", string pass = "\0", string ph = "\0", int b = 0) : name(n), email_id(id), password(pass), phone_no(ph), bill(b)
    {
    }
    virtual bool sign_in() override;
    void updatebill(int b)
    {
        bill += b;
    }
    int getbill()
    {
        return bill;
    }
    int getid()
    {
        return cus_id;
    }
    string getname()
    {
        return name;
    }
    string getemail()
    {
        return email_id;
    }
    string getphone()
    {
        return phone_no;
    }
    string getpass()
    {
        return password;
    }
    int getcusid()
    {
        return cus_id;
    }
    void setname(string name)
    {
        this->name = name;
    }
    void setemailid(string id)
    {
        this->email_id = id;
    }
    void setno(string no)
    {
        this->phone_no = no;
    }
};
bool Customer::sign_in()
{
}

class Room : public Customer
{
protected:
    int room_no;
    static int ac_room_no;
    static int non_ac_room_no;
    string room_type;
    string booking_time;

public:
    void booking();
    int getroom()
    {
        return room_no;
    }
    string gettype()
    {
        return room_type;
    }
    string gettime()
    {
        return booking_time;
    }
};
int Room::ac_room_no = 100;
int Room::non_ac_room_no = 200;

class ForCustomer : public Room
{
public:
    void signup();
    void history();
    int submenu(ForManager *m, int &n);
    bool sign_in();
};

class ForManager : public Room
{
public:
    ForManager(string name = "", string id = "", string pass = "", string ph = "", int bill = 0, int cno = 0)

    {
        cus_id = cno;
        this->name = name;
        this->email_id = id;
        this->password = pass;
        this->phone_no = ph;
        this->bill = bill;
    }
    ForManager(string name, string phone, string email, int room_no, string room_type, int cno, int bill, string time)
    {
        cus_id = cno;
        this->name = name;
        this->phone_no = phone;
        this->email_id = email;
        this->room_no = room_no;
        this->room_type = room_type;
        this->cus_id = cno;
        this->bill = bill;
        this->booking_time = time;
    }

    void EX_Booking(ForManager m[], int n);
    void Room_details(ForManager m[], int n);
    void Checkout(ForManager m[], int);
    void New_cus();
    void display_all();
    void search();
};

// manager class
bool Manager::sign_in()
{

    string username;
    string password;
    string uname;
    string pass;
    int flag = 0;

    cout << "\n\n\t\t-> enter your username : ";
    cin >> username;

    cout << "\n\n\t\t-> enter your password : ";

    password = hidepass();

    ifstream login_for_manager("managerdb.txt");
    while (login_for_manager >> uname >> pass)
    {
        login_for_manager >> uname;
        login_for_manager >> pass;

        if (uname == username && pass == password)
        {
            this->username = uname;
            this->password = pass;
            return true;
        }
    }
    if (flag == 0)
    {
        cout << "\n\n\t\t==> sorry you can't login!\n";

        login_for_manager.clear(); // Clear any error flags
        login_for_manager.seekg(0, ios::beg);
        return false;
    }
    else
    {
        return true;
    }
    help();
}

// forManager class
void ForManager::New_cus()
{
    booking();
}
void ForManager::display_all()
{

    cout << endl
         << "\t\t\t\t\t--> booking time :- " << booking_time << endl
         << endl
         << "\n\t\t\t--> id :- " << cus_id << endl
         << "\n\t\t\t--> name :- " << name << endl
         << endl;
    cout << "\t\t\t--> phone_no :- " << phone_no << endl
         << endl;
    cout << "\t\t\t--> email-id :- " << email_id << endl
         << endl;
    cout << "\t\t\t--> room no : - " << room_no << endl
         << endl;
    cout << "\t\t\t--> room_type :- " << room_type << endl
         << endl;
    cout << "\t\t\t--> " << getbill() << endl
         << endl;
}
void ForManager::search()
{
    display_all();
}
// room class

void Room::booking()
{
   

    ifstream count_lines("room.txt");
    string temp1;
    int c = 0, froom_no, t1 = 101, t2 = 201, temp;
    while (getline(count_lines, temp1))
    {
        c++;
    }

    if (c > 1)
    {
        ifstream room_nos("room.txt");
        while (c > 0)
        {
            getline(room_nos >> ws, temp1);
            room_nos >> temp;
            room_nos >> froom_no;
            room_nos >> temp;
            getline(room_nos >> ws, temp1);
            getline(room_nos >> ws, temp1);
            getline(room_nos >> ws, temp1);
            getline(room_nos >> ws, temp1);

            if (100 < froom_no && froom_no < 200)
            {
                if (t1 < froom_no)
                {
                    t1 = froom_no;
                }
            }

            else if (200 < froom_no)
            {
                if (t2 < froom_no)
                {
                    t2 = froom_no;
                }
            }

            ac_room_no = t1;
            non_ac_room_no = t2;
            c -= 8;
        }
    }

    int flag = 0;
    int op1, op2;
    cout << "BOOK ROOM FOR:" << endl;
    cout << "\n\t\t\t1. NON A.C ROOM" << endl;
    cout << "\n\t\t\t2. A.C. ROOM" << endl;
    cout << "chose option : ";
    cin >> op1;
    getchar();

    switch (op1)
    {
    case 1:
        non_ac_room_no++;
        cout << endl;
        cout << "here room types\n";
        cout << "\n\t\t\t1. 12hr (ROOM RENT: RS. 800)" << endl;
        cout << "\n\t\t\t2. 24hr (ROOM RENT: RS. 1500)" << endl;
        cout << "chose option : ";

        cin >> op2;
        getchar();

        switch (op2)
        {
        case 1:
            room_type = "NON A.C ROOM - 12hr";
            flag = 1;
            updatebill(800);
            break;
        case 2:
            room_type = "NON A.C ROOM - 24hr";
            flag = 1;
            updatebill(1500);
            break;
        default:
            break;
        }
        break;

    case 2:

        ac_room_no++;
        cout << "\n\t\t\t1. 12hr (ROOM RENT: RS. 1400)" << endl;
        cout << "\n\t\t\t2. 24hr (ROOM RENT: RS. 2500)" << endl;
        cout << "chose option : ";
        cin >> op2;
        getchar();
        switch (op2)
        {
        case 1:
            room_type = "A.C ROOM - 12hr";

            flag = 2;
            updatebill(1400);
            break;
        case 2:
            room_type = "A.C ROOM - 24hr";

            flag = 2;
            updatebill(2500);
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
    cout << "\n\tyour room type is : " << room_type << endl;

    if (flag == 1)
    {
        room_no = non_ac_room_no;
        cout << "\n\tyour room no is : " << room_no;
    }
    else
    {
        room_no = ac_room_no;
        cout << "\n\tyour room no is : " << room_no;
    }
    cus_id++;
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
    tm *local_time = std::localtime(&time_now);

    // Extract date and time components
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;

    this->booking_time = to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + "   " + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << "\n\n\t--> suceesfully your rooms was booked \n\n";
    ofstream save_details;
    save_details.open("room.txt", std::ofstream::out | std::ofstream::app);

    // else
    {

        save_details << booking_time << "\n"
                     << cus_id << "\n"
                     << room_no << "\n"
                     << bill << "\n"
                     << room_type << "\n"
                     << name << "\n"
                     << phone_no << "\n"
                     << email_id << endl;

        save_details.flush();
    }

    help();
}
void ForManager::Room_details(ForManager m[], int n)
{
    int ac[15], nonac[15];
    int i;
    for (i = 0; i < 15; i++)
    {
        ac[i] = 100 + (i + 1);
    }

    for (i = 0; i < 15; i++)
    {
        nonac[i] = 200 + (i + 1);
    }

    cout << endl
         << "\n\n\t\ttotal AC room are :  ";
    // cout << "\t\t";
    for (i = 0; i < 15; i++)
    {
        cout << ac[i] << "  ";
    }

    cout << endl
         << "\n\n\t\ttotal NON_AC room are :  ";

    // cout << "\t\t";
    for (i = 0; i < 15; i++)
    {
        cout << nonac[i] << "  ";
    }

    if (n != 0)
    {
        int c[15] = {}, c1[15] = {}; // c for ac AND c1 for non
        cout << "\n\n\n\n\t\tbooked ac rooms :   ";
        for (i = 0; i <= n; i++)
        {
            if (m[i].getroom() > 100 && m[i].getroom() < 200)
            {
                cout << m[i].getroom() << "  ";
            }
        }

        cout << "\n\n\t\tbooked non_ac rooms :   ";
        for (i = 0; i <= n; i++)
        {
            if (m[i].getroom() > 200 && m[i].getroom() < 216)
            {
                cout << m[i].getroom() << "  ";
            }
        }

        cout << endl
             << endl;
        for (i = 0; i < 15; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (m[j].getroom() == ac[i])
                {
                    c[i]++;
                }
            }
        }

        for (i = 0; i < 15; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (m[j].getroom() == nonac[i])
                {
                    c1[i]++;
                }
            }
        }

        cout << "\n\n\t\tavaliable AC rooms :    ";

        for (i = 0; i < 15; i++)
        {
            if (c[i] == 0)
            {
                cout << ac[i] << " ";
            }
        }

        cout << "\n\n\n\t\tavaliable Non_AC rooms :    ";

        for (i = 0; i < 15; i++)
        {
            if (c1[i] == 0)
            {
                cout << nonac[i] << " ";
            }
        }
    }
    else
    {
        cout << "\n\n\t-->all rooms are avaliable!\n";
    }
    cout << endl;
    help();
}
void ForManager::EX_Booking(ForManager M[], int n)
{
    int id;
    cout << "\n\n\t\tenter customer id(for extand booking) :- ";
    cin >> id;
    getchar();

    if (id > n || M[id - 1].getroom() < 100)
    {
        cout << "--> not exit!\n";
    }
    else
    {
        int hrs;
        cout << "\n\n\t\t--> How many hours customer wants to extand :- ";
        cin >> hrs;
        getchar();

        int index = id - 1;
        if (M[index].getroom() > 100 && M[index].getroom() < 200)
        {
            cout << "\n\n\t\t--> Your room no is : " << M[index].getroom() << " so for 1Hr price is : " << 200;
            cout << "\n\t\t--> total price is : " << hrs * 200;

            cout << "\n\n\n\n\t\t\tThank You!";

            M[index].updatebill(hrs * 200);
        }
        else if (M[index].getroom() > 200 && M[index].getroom() < 216)
        {
            cout << "\n\n\t\t--> Your room no is : " << M[index].getroom() << " so for 1Hr price is : " << 150;
            cout << "\n\t\t--> total price is : " << hrs * 150;

            cout << "\n\n\n\n\t\t\tThank You!";

            M[index].updatebill(hrs * 150);
        }
        else
        {
            cout << "sorry! try again!";
            EX_Booking(M, n);
        }
    }
    // help();
}
void ForManager::Checkout(ForManager m[], int n)
{
    cout << "\n\n\t";
    for (int i = 0; i < 54; i++)
    {
        cout << "_";
    }
    cout << "\n\t|" << setw(54) << right << "|\n";
    cout << "\t|\tname\t   :- " << setw(31) << left << name;
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|\temail\t   :- " << setw(31) << left << email_id;
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|\tphone_no   :- " << setw(31) << left << phone_no;
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|\troom_no\t   :- " << setw(31) << left << room_no;
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|\troom_type  :- " << setw(31) << left << room_type;
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|\tBill\t   :- " << setw(31) << left << getbill();
    cout << "|" << endl
         << "\t|" << setw(53) << right << "|" << endl;

    cout << "\t|" << setw(53) << right << "|" << endl;
    cout << "\t|" << setw(53) << right << "|" << endl;
    cout << "\t|";
    for (int i = 0; i < 52; i++)
    {
        cout << "_";
    }
    cout << "|\n\n\t\t";
    int temp_id = cus_id;
    name = "\0";
    email_id = "\0";
    phone_no = "\0";
    room_no = 0;
    room_type = "\0";
    booking_time = "\0";
    password = "\0";
    cus_id = 0;

    remove("room.txt");

    ofstream put_data;
    put_data.open("room.txt", std::ofstream::out | std::ofstream::app);

    for (int i = 0; i < n; i++)
    {
        if (m[i].getcusid() != 0)
        {
            put_data << m[i].booking_time << endl
                     << m[i].cus_id << endl
                     << m[i].room_no << endl
                     << m[i].bill << "\n"
                     << m[i].room_type << "\n"
                     << m[i].name << "\n"
                     << m[i].phone_no << "\n"
                     << m[i].email_id << endl;
        }
    }

    cout << "\n\n\t\t\t--> Checkout successful for guest: " << temp_id << endl
         << endl;

    help();
}

// for customer

// int cus_id;
void ForCustomer::history()
{
    int c = 0;
    ifstream lines("history.txt");
    string temp;
    while (getline(lines, temp))
    {
        c++;
    }
    if (c > 1)
    {
        system("cls");
        ifstream get_his("history.txt");
        string cus_id, room_no, bill, room_type, name, p_no, id, time;
        cout << "\n\n\thistory! -->";
        while (c > 0)
        {
            getline(get_his >> ws, time);
            getline(get_his >> ws, cus_id);
            getline(get_his >> ws, room_no);
            getline(get_his >> ws, bill);
            getline(get_his >> ws, room_type);
            getline(get_his >> ws, name);
            getline(get_his >> ws, p_no);
            getline(get_his >> ws, id);

            cout << "\n\n\t --> booking time  : " << time;
            cout << "\n\n\t --> name : " << name;
            cout << "\n\n\t --> phone_no : " << p_no;
            cout << "\n\n\t --> email_id : " << id;
            cout << "\n\n\t --> room_no : " << room_no;
            cout << "\n\n\t --> room_type : " << room_type;
            cout << "\n\n\t --> bill : " << bill;

            cout << endl
                 << endl;

            c -= 9;
        }
    }
    else
    {
        cout << "\n\n\t\t ==> your history is empty!\n\n";
    }
    help();
}
int FLAG = 0;
int ForCustomer::submenu(ForManager *m, int &n)
{
    while (1)
    {
        system("cls");
        int flag;
        cout << "SOFTWARE SERVICE :- \n\n\t\t\t1 - Booking Room\n\n\t\t\t2 - History\n\n\t\t\t3 - quit\n\nchose your option : ";
        cin >> flag;
        getchar();

        if (flag == 1)
        {
            if (FLAG == 1)
            {
                ForManager *temp = new ForManager[n + 1];
                if (m != nullptr)
                {
                    for (int j = 0; j < n; j++)
                    {
                        temp[j] = m[j];
                    }
                    delete[] m;
                }
                m = temp;
                system("cls");
                m[n] = ForManager(name + "(online booking)", email_id, password, phone_no, 0, n);
                // ForManager(string name = "", string id = "", string pass = "", string ph = "", int bill = 0, int cno = 0)
                m[n].booking();

                ofstream for_history;
                for_history.open("history.txt", std::ofstream::out | std::ofstream::app);
                for_history << m[n].gettime() << endl
                            << m[n].getcusid() << endl
                            << m[n].getroom() << endl
                            << m[n].getbill() << endl
                            << m[n].gettype() << endl
                            << m[n].getname() << endl
                            << m[n].getphone() << endl
                            << m[n].getemail() << endl;
            }
            else if (FLAG == 0)
            {

                system("cls");
                ForManager temp;
                temp.setname(name);
                temp.setemailid(email_id);
                temp.setno(phone_no);
                temp.booking();

                ofstream fordecent;
                fordecent.open("decent.txt", std::ofstream::out | std::ofstream::app);
                fordecent << temp.gettime() << endl
                          << n + 1 << endl
                          << temp.getroom() << endl
                          << temp.getbill() << endl
                          << temp.gettype() << endl
                          << this->name << endl
                          << this->phone_no << endl
                          << this->email_id << endl;

                ofstream for_history;
                for_history.open("history.txt", std::ofstream::out | std::ofstream::app);
                for_history << temp.gettime() << endl
                            << n + 1 << endl
                            << temp.getroom() << endl
                            << temp.getbill() << endl
                            << temp.gettype() << endl
                            << name << endl
                            << phone_no << endl
                            << email_id << endl;
            }
        }
        else if (flag == 2)
        {
            history();
        }
        else if (flag == 3)
        {
            return 3;
        }
        else
        {
            cout << "\n\n--> sorry! your option not valid. \n";
            help();
            submenu(m, n);
        }
    }
}
bool ForCustomer::sign_in()
{
    string input_id;
    string input_pass;
    string fname;
    string fphone;
    string fid;
    string fpass;
    string temp;
    int c = 0;

    ifstream count_cus("customer.txt");
    while (getline(count_cus, temp))
    {
        c++;
    }
    if (c < 2)
    {
        cout << "\n\n\t\t\t==> You need to make your account!\n\n";

        return false;
    }
    system("cls");
    while (1)
    {
        cout << "\n\n\t--> Enter your email_id (for sign in) : ";
        getline(cin >> ws, input_id);
        if (isEmail(input_id))
        {
            break;
        }
        else
        {
            cout << "\n\n\t\t--> enter valid email_id\n\n";
        }
    }

    cout << "\n\n\t--> Enter your password : ";
    input_pass = hidepass();

    if (c > 1)
    {
        ifstream get_cus("customer.txt");
        while (!get_cus.eof())
        {
            getline(get_cus >> ws, fname);
            getline(get_cus >> ws, fid);
            getline(get_cus >> ws, fphone);
            getline(get_cus >> ws, fpass);

            if (input_id == fid && input_pass == fpass)
            {
                cout << "\n\n\t\t\t==> you login successfully!\n\n";
                help();
                this->name = fname;
                this->email_id = fid;
                this->phone_no = fphone;
                this->password = fpass;
                return true;
            }
        }
    }
    cout << "\n\n\t--> email_id is not avaliable!";
    return false;
}
void ForCustomer::signup()
{
    system("cls");
    string name, id, pass, repass, pno;
    cout << "\n\t\t--> enter your name :- ";
    getline(cin >> ws, name);
    while (1)
    {
        cout << "\n\t\t--> enter your email_id :- ";
        getline(cin >> ws, id);

        if (!isEmail(id))
        {
            cout << "\n\t==> your email id invalid!\n";
        }
        else
            break;
    }
    while (1)
    {
        cout << "\n\t\t--> enter your phone no :- ";
        getline(cin >> ws, pno);

        if (!isPhone(pno))
        {
            cout << "\n\t==> your phone no invalid!\n";
        }
        else
            break;
    }
    while (1)
    {
        cout << "\n\t\t--> enter your password (pls not forget your password) :- ";
        pass = hidepass();
        cout << "\n\t\t--> re-enter your password :- ";
        repass = hidepass();

        if (pass == repass)
        {
            break;
        }
        else
        {
            cout << "\n\n\t--> sorry your password is wrong!";
        }
    }

    if (pass == repass)
    {
        this->name = name;
        this->email_id = id;
        this->phone_no = pno;
        this->password = pass;

        ofstream put_cus;
        put_cus.open("customer.txt", std::ofstream::out | std::ofstream::app);

        put_cus << this->name << endl
                << this->email_id << endl
                << this->phone_no << endl
                << this->password << endl;
        // m[i] = ForManager(name , email_id ,pass ,  pno,0 , i+1 );
    }
}
int forlogin()
{
    int option;
    while (1)
    {
        cout << "\n\t\t 1 : for try again\n\t\t 2 : for quit\n";
        cout << "choose your option : ";
        cin >> option;
        if (option == 1)
            return 1;
        else if (option == 2)
            return 2;
        else
            cout << "\n\t==> your option is invalid!\n";
    }
}
int main()
{
    remove("decent.txt");
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t __        __  _____   __      ____   ___    __  __   _____" << endl;
    cout << "\t\t\t\t\t\t \\ \\      / / | ____| | |     / ___/ / _ \\  |  \\/  | | ____|" << endl;
    cout << "\t\t\t\t\t\t  \\ \\ /\\ / /  |  _|   | |    | |    | | | | | |\\/| | | _|  " << endl;
    cout << "\t\t\t\t\t\t   \\ V  V /   | |___  | |__  | |__  | |_| | | |  | | | |___ " << endl;
    cout << "\t\t\t\t\t\t    \\_/\\_/    |_____| |____|  \\____\\ \\___/  |_|  |_| |_____|" << endl;
    cout << "\n\n\t\t\t\t\t\t---------------------------------------------------------------" << endl
         << endl;

    help();
    int check;
    int for_old_data = 0;
    char olddata;
    system("cls");

    int i = 0;
    int flag_cus = 0;
    int flag_manager = 0;
    int flag = 0;
    int choice;
    int login_for;
    bool full = false;

    ForManager *M = nullptr;

    while (1)
    {
        if(i == 30)
        {
            system("cls");
            cout << "\n\n\n\t\t --> your all rooms are full!\n";
            help();
            break;
        }

        if (flag == 0)
        {
            system("cls");

            cout << "\n\n\t\t\t1 - MANAGER\n\n\t\t\t2 - CUSTOMER (For online booking - only for tommorow)\n\n\t\t\t3 - quit\n\nenter your option :- ";
            cin >> login_for;
            getchar();
            flag = 1;
            system("cls");
        }

        if (login_for == 1) // for man.
        {
            if (flag_manager == 0)
            {
                Manager temp;
                if (temp.sign_in())
                {

                    if (for_old_data == 0)
                    {
                        flag_manager = 1;
                        check = 0;

                        cout << "\n\n\t\t\t\t=> verify your are manager! <=\n\n";

                        while (1)
                        {
                            cout << "\n\t\tAre you want you work with old data [y/n] : ";
                            cin >> olddata;
                            getchar();
                            if (olddata != 'y' && olddata != 'Y' && olddata != 'n' && olddata != 'N')
                            {
                                cout << "\n\n\t-->enter valid ans :- ";
                            }
                            else
                            {
                                break;
                            }
                        }

                        for_old_data = 1;
                        cout << "\n\n";
                        help();
                        if (olddata == 'n' || olddata == 'N')
                        {

                            remove("room.txt");
                            
                            ifstream takecount("decent.txt");
                            int room_no, cno, bill, count = 0;
                            string name, phone, email, room_type, t;

                            while (getline(takecount, t))
                            {
                                count++;
                            }
                            
                            ifstream takeolddata("decent.txt");
                            while (count > 0)
                            {
                                check = 1;

                                getline(takeolddata >> ws, t);
                                takeolddata >> cno;
                                takeolddata >> room_no;
                                takeolddata >> bill;
                                getline(takeolddata >> ws, room_type);
                                getline(takeolddata >> ws, name);
                                getline(takeolddata >> ws, phone);
                                getline(takeolddata >> ws, email);

                                ForManager *temp;
                                temp = new ForManager[i + 1];
                                if (M != nullptr)
                                {
                                    for (int j = 0; j < i; j++)
                                    {
                                        temp[j] = M[j];
                                    }
                                    delete[] M;
                                }
                                M = temp;
                                M[i] = ForManager(name, phone, email, room_no, room_type, i + 1, bill, t + "(online booking) ");

                                i++;
                                count -= 8;
                            }
                            
                        }
                        else
                        {
                            ifstream takecount("room.txt");
                            int room_no, cno, bill, count = 0;
                            string name, phone, email, room_type, t;

                            while (getline(takecount, t))
                            {
                                count++;
                            }
                            
                            ifstream takeolddata("room.txt");
                            while (count > 0)
                            {
                                check = 1;
                                
                                getline(takeolddata >> ws, t);
                                takeolddata >> cno;
                                takeolddata >> room_no;
                                takeolddata >> bill;
                                getline(takeolddata >> ws, room_type);
                                getline(takeolddata >> ws, name);
                                getline(takeolddata >> ws, phone);
                                getline(takeolddata >> ws, email);

                                ForManager *temp;
                                temp = new ForManager[i + 1];
                                if (M != nullptr)
                                {
                                    for (int j = 0; j < i; j++)
                                    {
                                        temp[j] = M[j];
                                    }
                                    delete[] M;
                                }
                                M = temp;
                                M[i] = ForManager(name, phone, email, room_no, room_type, i + 1, bill, t);

                                i++;
                                count -= 8;
                            }
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\t=> sorry! try again! <=\n\n";
                        flag_manager = 1;
                    }
                }
                else
                {
                    int options = forlogin();
                    if (options == 2)
                    {
                        flag = 0;
                    }
                    help();
                    getchar();
                }
            }

            if (flag_manager == 1)
            {
                system("cls");
                cout << "\n\n\n\n";
                cout << "\n\t\t\t\t\tWELCOME TO OUR MOTEL" << endl;
                cout << "\n\t\t\t\t\t1. NEW COUSTOMER" << endl;
                cout << "\n\t\t\t\t\t2. DISPLAY ALL COUSTOMER RECORD" << endl;
                cout << "\n\t\t\t\t\t3. SEARCH ANY CUSTOMER DETAILS" << endl;
                cout << "\n\t\t\t\t\t4. EXTEND BOOKING" << endl;
                cout << "\n\t\t\t\t\t5. ROOM DETAILS" << endl;
                cout << "\n\t\t\t\t\t6. BILL & CHECKOUT" << endl;
                cout << "\n\t\t\t\t\t7. EXIT" << endl;
                cout << "\n\nenter your option : ";
                cin >> choice;
                getchar();

                system("cls");

                switch (choice)
                {
                case 1:
                {
                    ForManager *temp;
                    temp = new ForManager[i + 1];
                    if (M != nullptr)
                    {
                        for (int j = 0; j < i; j++)
                        {
                            temp[j] = M[j];
                        }
                        delete[] M;
                    }
                    M = temp;
                    // dynamic(i , M);
                    string name;
                    string email_id;
                    string phone;

                    cout << "\n\n\tenter customer name : ";
                    getline(cin >> ws, name);

                    while (1)
                    {
                        cout << "\n\n\tenter customer email id : ";
                        getline(cin >> ws, email_id);
                        if (isEmail(email_id))
                        {
                            break;
                        }
                        else

                        {
                            cout << "\n\n\t\t-->pls enter valid email_id.";
                            help();
                        }
                    }

                    while (1)
                    {
                        cout << "\n\n\tenter customer phone_no : ";
                        getline(cin >> ws, phone);
                        if (isPhone(phone))
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n\n\t\t--> pls enter valid phone no.";
                            help();
                        }
                    }
                    M[i] = ForManager(name, email_id, "\0", phone, 0, i);
                    M[i].New_cus();

                    i++;
                }
                break;
                case 2:
                {
                    int c = 0;
                    for (int j = 0; j < i; j++)
                    {
                        if (M[j].getroom() > 100 && M[j].getroom() < 300)
                        {
                            c++;
                        }
                    }

                    if (i == 0 || c == 0)
                    {
                        cout << "\n\n\t--> no record found! \n";
                    }
                    else
                    {
                     
                        {

                            for (int j = 0; j < i; j++)
                            {
                                if (M[j].getroom() > 100 && M[j].getroom() < 300)
                                {

                                    M[j].display_all();
                                    lines();
                                }
                            }
                        }
                    }
                    help();
                }
                break;
                case 3:
                {
                    int id;
                    cout << "\n\n\t--> enter customer id for see : ";
                    cin >> id;
                    getchar();

                    if (id > i || M[id - 1].getroom() < 100)
                    {
                        cout << "\n\n\t\t--> no record found\n\n";
                        help();
                    }
                    else
                    {
                        M[id - 1].search();
                        help();
                    }
                }
                break;
                case 4:
                {
                    ForManager temp;
                    temp.EX_Booking(M, i);
                    help();
                }
                break;
                case 5:
                {
                    ForManager temp;
                    temp.Room_details(M, i);
                }
                break;
                case 6:
                {
                    int n;
                    cout << "\n\n\t--> enter customer id :- ";
                    cin >> n;
                    getchar();

                    if (n > i || M[n - 1].getroom() < 100)
                    {
                        cout << "\n\tsorry! " << n << "not avaliable : ";
                        help();
                    }
                    else
                    {
                        M[n - 1].Checkout(M, i);
                    }
                }
                break;
                case 7:
                {
                    flag = 0;
                    flag_manager = 0;
                }
                break;
                }
            }
        }

        else if (login_for == 2) // for cus.
        {
            system("cls");
            flag_cus = 1;
            flag = 1;
            int j = 0, cquit = 0;
            int flag2, menu;
            cout << "SOFTWARE SERVICE :- \n\n\t\t\t1 - SIGN IN\n\n\t\t\t2 - SIGN UP\n\n\t\t\t3 - quit\n\nchose your option : ";
            cin >> flag2;
            getchar();

            switch (flag2)
            {
            case 1:
            {
                ForCustomer temp;
                if (temp.sign_in())
                {

                    int o = temp.submenu(M, i);
                    if (o == 3)
                    {
                        login_for = 2;
                    }
                }
                else
                {
                    int option = forlogin();
                    while (1)
                    {
                        if (option == 2)
                        {
                            login_for = 2;
                            break;
                        }
                        else
                        {
                            if (temp.sign_in())
                            {
                                int t = temp.submenu(M, i);
                                if(t == 3)
                                login_for = 2;
                                break;
                            }
                        }
                    }
                    help();
                }
                help();
            }
            break;

            case 2:
            {
                ForCustomer t;
                t.signup();

                cout << "\n\n\t\t\t ==> your account succesfully created!\n\n";
                help();
                int option = t.submenu(M, i);
                if (option == 3)
                {
                    login_for = 2;
                }
            }
            break;

            case 3:
                flag = 0;
                break;

            default:
                cout << "\n\n\t-->try again! invalid no";
                help();
                break;
            }
        }
        else if (login_for == 3)
        {
            flag = 0;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t\t _____  _   _      _      _   _    _  __   __   __   ___    _   _  " << endl;
            cout << "\t\t\t\t\t\t|_   _|| | | |    / \\    | \\ | |  | |/ /   \\ \\ / /  / _ \\  | | | |  " << endl;
            cout << "\t\t\t\t\t\t  | |  | |_| |   / _ \\   |  \\| |  | ' /     \\ V /  | | | | | | | |" << endl;
            cout << "\t\t\t\t\t\t  | |  |  _  |  / ___ \\  | |\\  |  | . \\      | |   | |_| | | |_| |   _   _   _   _  " << endl;
            cout << "\t\t\t\t\t\t  |_|  |_| |_| /_/   \\_\\ |_| \\_|  |_|\\_\\     |_|    \\___/  \\ ___ /  |_| |_| |_| |_|  " << endl;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
            break;
        }
        else
        {
            cout << "\n\n\t--> you enter invalid no , pls try again!\n";
            help();
            flag = 0;
        }
    }
    delete[] M;

    return 0;
}