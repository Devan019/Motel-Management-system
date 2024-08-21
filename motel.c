#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>
static int ac_room = 100;
static int non_ac_room = 200;
void lines()
{
    printf("\t");
    for (int i = 0; i < 80; i++)
    {
        printf("-");
    }
}
char olddata;
void help()
{
    printf("\n\n\t\t\t==> PRESS ENTER TO CONTINUE... ");
    getchar();
}
void hidepass(char *s)
{
    char ch;
    int i = 0;
    while ((ch = getch()) != 13)
    {
        if (ch == '\b')
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else
        {
            s[i] = ch;
            i++;
            printf("*");
        }
    }
    s[i] = '\0';
    printf("\n");
}

int isEmail(char id[])
{
    int c = 0, c1 = 0;
    for (int i = 0; i < strlen(id); i++)
    {
        if (id[i] == ' ')
        {
            return 0;
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
        return 1;
    }
    return 0;
}

int isPhone(char no[])
{
    int c = 0;
    for (int i = 0; i < strlen(no); i++)
    {
        if (no[i] >= 48 && no[i] <= 58)
        {
            c++;
        }
    }

    if (c == 10)
    {
        return 1;
    }
    return 0;
}
typedef struct
{
    char username[100];
    char password[100];
} Manager;

typedef struct
{
    char name[100];
    char email_id[100];
    char password[100];
    char phone_no[100];
    int bill;
    int cus_id;

} Customer;

typedef struct
{
    Customer cus;
    int room_no;
    char booking_time[100];
    char room_type[100];
} Room;

int Manager_sign_in(Manager *m)
{
    char username[100];
    char password[100];
    char uname[100];
    char pass[100];

    int flag = 0;

    printf("\n\n\t\t-> enter your username : ");
    gets(username);

    printf("\n\n\t\t-> enter your password : ");
    hidepass(password);

    FILE *fptr;
    fptr = fopen("managerdb.txt", "r");

    char fname[20], fpass[20], temp[30];
    int cout = 0;
    while (fgets(temp, sizeof(temp), fptr) != NULL)
    {
        cout++;
    }
    // printf(" %d " , cout);
    FILE *f;
    f = fopen("managerdb.txt", "r");
    while (cout > 0)
    {
        fscanf(f, "%s", fname);
        fscanf(f, "%s", fpass);

        if (!(strcmp(fname, username)))
        {
            if (!(strcmp(fpass, password)))
            {
                strcpy(m->username, username);
                strcpy(m->password, password);
                return 1;
            }
        }
        cout -= 2;
    }
    if (flag == 0)
    {
        printf("\n\n\t\t==> sorry you can't login!\n");
        return 0;
    }
    else
    {
        return 1;
    }
    help();
}

void ForManager(char name[], char id[], char pass[], char ph[], int bill, int cno, char time[], int room_no, char room_type[], Room *room)
{
    strcpy(room->cus.name, name);
    strcpy(room->cus.email_id, id);
    strcpy(room->cus.password, pass);
    strcpy(room->cus.phone_no, ph);
    room->cus.cus_id = cno;
    room->cus.bill = bill;
    strcpy(room->booking_time, time);
    room->room_no = room_no;
    strcpy(room->room_type, room_type);
}

void display_all(Room *r)
{
    printf("\n\t\t\t\t\t--> booking time :- ");
    printf("%s\n\n", r->booking_time);
    printf("\n\t\t\t--> id :- ");
    printf("%d\n\n", r->cus.cus_id);
    printf("\n\t\t\t--> name :- ");
    printf("%s\n\n", r->cus.name);
    printf("\n\t\t\t--> phone_no :- ");
    printf("%s\n\n", r->cus.phone_no);
    printf("\n\t\t\t--> email_id :- ");
    printf("%s\n\n", r->cus.email_id);
    printf("\n\t\t\t--> room_no :- ");
    printf("%d\n\n", r->room_no);
    printf("\n\t\t\t--> room_type :- ");
    printf("%s\n\n", r->room_type);
    printf("\n\t\t\t--> %d\n\n", r->cus.bill);
}

void search(Room r)
{
    lines();
    display_all(&r);
    lines();
}

void booking(Room *r)
{

    FILE *fptr;
    fptr = fopen("room.txt", "r");
    int room_no, cno, bill, count = 0, t1 = 101, t2 = 201, froom_no;
    char name[100], phone[20], email[30], room_type[30], t[20], temp[20];

    while (fgets(t, sizeof(t), fptr))
    {
        count++;
    }
    // printf("count = %d",count);
    if (count > 1)
    {
        FILE *file;
        file = fopen("room.txt", "r");
        while (count > 0)
        {
            fgets(t, sizeof(t), file);
            fgets(temp, sizeof(temp), file);
            fscanf(file, "%d", &cno);

            fscanf(file, "%d", &froom_no);

            fscanf(file, "%d", &bill);
            fgets(temp, sizeof(temp), file);

            fgets(room_type, sizeof(room_type), file);
            fgets(name, sizeof(name), file);
            fgets(phone, sizeof(phone), file);
            fgets(email, sizeof(email), file);

            if (100 < froom_no && froom_no < 200)
            {
                if (t1 < froom_no)
                {
                    t1 = froom_no;
                }
            }

            else if (200 < froom_no && froom_no < 216)
            {
                if (t2 < froom_no)
                {
                    t2 = froom_no;
                }
            }

            ac_room = t1;
            non_ac_room = t2;
            count -= 10;
        }
    }

    int flag = 0;
    int op1, op2;
    printf("BOOK ROOM FOR : \n");
    printf("\n\t\t\t1. NON A.C ROOM\n");
    printf("\n\t\t\t2. A.C. ROOM");
    printf("\n\nchose option : ");

    scanf("%d", &op1);
    getchar();

    switch (op1)
    {
    case 1:
    {
        non_ac_room++;
        printf("\nhere room types\n");
        printf("\n\t\t\t1. 12hr (ROOM RENT: RS. 800)\n");
        printf("\n\t\t\t2. 24hr (ROOM RENT: RS. 1500)\n");
        printf("choose option : ");

        scanf("%d", &op2);
        getchar();

        switch (op2)
        {

        case 1:
            strcpy(r->room_type, "NON A.C ROOM - 12hr");
            flag = 1;
            r->cus.bill += 800;
            break;

        case 2:
            strcpy(r->room_type, "NON A.C ROOM - 24hr");
            flag = 1;
            r->cus.bill += 1500;
            break;
        default:
            break;
        }
    }
    break;
    case 2:
    {

        ac_room++;
        printf("\nhere room types\n");
        printf("\n\t\t\t1. 12hr (ROOM RENT: RS. 1400)\n");
        printf("\n\t\t\t2. 24hr (ROOM RENT: RS. 2500)\n");
        printf("choose option : ");

        scanf("%d", &op2);
        getchar();

        switch (op2)
        {

        case 1:
            strcpy(r->room_type, "A.C ROOM - 12hr");
            flag = 2;
            r->cus.bill += 1400;
            break;

        case 2:
            strcpy(r->room_type, "A.C ROOM - 24hr");
            flag = 2;
            r->cus.bill += 2500;
            break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }

    printf("\n\tyour room type is : %s\n", r->room_type);

    if (flag == 1)
    {
        r->room_no = non_ac_room;
        printf("\n\tyour room no is : %d", r->room_no);
    }
    else
    {
        r->room_no = ac_room;
        printf("\n\tyour room no is : %d", r->room_no);
    }
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;
    snprintf(r->booking_time, sizeof(r->booking_time), "%02d:%02d:%02d   %02d/%02d/%d", hour, minute, second, day, month, year);

    FILE *save_details;
    save_details = fopen("room.txt", "a");

    fprintf(save_details, "%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n", r->booking_time, r->cus.cus_id, r->room_no, r->cus.bill, r->room_type, r->cus.name, r->cus.phone_no, r->cus.email_id);
    fflush(save_details);

    fclose(save_details);
    help();
}

void Room_details(Room m[], int n)
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

    printf("\n\n\n\t\ttotal AC room are :  ");
    for (i = 0; i < 15; i++)
    {
        printf("%d ", ac[i]);
    }
    printf("\n\n\n\t\ttotal NON_AC room are :  ");
    for (i = 0; i < 15; i++)
    {
        printf("%d ", nonac[i]);
    }

    if (n != 0)
    {
        int c[15] = {}, c1[15] = {};
        printf("\n\n\n\n\t\tbooked ac rooms :   ");
        for (i = 0; i <= n; i++)
        {
            if (m[i].room_no > 100 && m[i].room_no < 200)
            {
                printf("%d ", m[i].room_no);
            }
        }
        printf("\n\n\t\tbooked non_ac rooms :   ");
        for (i = 0; i <= n; i++)
        {
            if (m[i].room_no > 200 && m[i].room_no < 216)
            {
                printf("%d ", m[i].room_no);
            }
        }

        printf("\n\n");

        for (i = 0; i < 15; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (m[j].room_no == ac[i])
                {
                    c[i]++;
                }
            }
        }

        for (i = 0; i < 15; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (m[j].room_no == nonac[i])
                {
                    c1[i]++;
                }
            }
        }

        printf("\n\n\t\tavaliable AC rooms :    ");

        for (i = 0; i < 15; i++)
        {
            if (c[i] == 0)
            {
                printf("%d ", ac[i]);
            }
        }

        printf("\n\n\n\t\tavaliable Non_AC rooms :    ");

        for (i = 0; i < 15; i++)
        {
            if (c1[i] == 0)
            {
                printf("%d ", nonac[i]);
            }
        }
    }
    else
    {
        printf("\n\n\t-->all rooms are avaliable!\n");
    }
    printf("\n");
    help();
}
void EX_Booking(Room M[], int n)
{
    int id;
    printf("\n\n\t\tenter customer id(for extand booking) :- ");
    scanf("%d", &id);
    getchar();

    if (id > n || M[id - 1].room_no < 100)
    {
        printf("--> not exit!\n");
    }
    else
    {
        int hrs;
        printf("\n\n\t\t--> How many hours customer wants to extand :- ");
        scanf("%d", &hrs);
        getchar();

        int index = id - 1;

        if (M[index].room_no > 100 && M[index].room_no < 200)
        {
            printf("\n\n\t\t--> Your room no is : %d so for 1Hr price is : 200", M[index].room_no);

            printf("\n\t\t--> total price is : %d", hrs * 200);
            printf("\n\n\n\n\t\t\tThank You!");
            M[index].cus.bill += (hrs * 200);
        }
        else if (M[index].room_no > 200 && M[index].room_no < 216)
        {
            printf("\n\n\t\t--> Your room no is : %d so for 1Hr price is : 150", M[index].room_no);

            printf("\n\t\t--> total price is : %d", hrs * 150);
            printf("\n\n\n\n\t\t\tThank You!");
            M[index].cus.bill += (hrs * 150);
        }
        else
        {
            printf("sorry! no is not valid!");
        }
    }
}

void Checkout(Room m[], int n, Room *r)
{
    FILE *ptr = fopen("room.txt", "w");
    fclose(ptr);
    ptr = NULL;

    lines();
    display_all(r);
    lines();
    int temp_id = r->cus.cus_id;
    strcpy(r->cus.name, "\0");
    strcpy(r->cus.email_id, "\0");
    strcpy(r->cus.phone_no, "\0");
    r->room_no = 0;
    strcpy(r->room_type, "\0");
    strcpy(r->booking_time, "\0");
    strcpy(r->cus.password, "\0");
    r->cus.cus_id = 0;

    ptr = fopen("room.txt", "a");
    for (int i = 0; i < n; i++)
    {
        if (m[i].cus.cus_id != 0)
        {
            fprintf(ptr, "%s%d\n%d\n%d%s%s%s%s", m[i].booking_time, m[i].cus.cus_id, m[i].room_no, m[i].cus.bill, m[i].room_type, m[i].cus.name, m[i].cus.phone_no, m[i].cus.email_id);
        }
    }

    printf("\n\n\t\t\t--> Checkout successful for guest: %d\n\n", temp_id);
    
    help();
}

void history()
{
    int c = 0;
    FILE *file;
    file = fopen("history.txt", " r");
    char t[30];
    while (fgets(t, sizeof(t), file))
    {
        c++;
    }

    if (c > 1)
    {
        system("cls");
        FILE *fptr;
        fptr = fopen("history.txt", "r");
        char cus_id[10], room_no[10], bill[10], room_type[25], name[25], p_no[20], id[20], time[25];

        printf("\n\n\thistory! -->");

        while (c > 1)
        {
            fgets(time, sizeof(time), fptr);
            fgets(cus_id, sizeof(cus_id), fptr);
            fgets(room_no, sizeof(room_no), fptr);
            fgets(bill, sizeof(bill), fptr);
            fgets(room_type, sizeof(room_type), fptr);
            fgets(name, sizeof(name), fptr);
            fgets(p_no, sizeof(p_no), fptr);
            fgets(id, sizeof(id), fptr);

            printf("\n\n\t --> booking time  : %s", time);
            printf("\n\n\t --> name  : %s", name);
            printf("\n\n\t --> phone no  : %s", p_no);
            printf("\n\n\t --> email_id  : %s", id);
            printf("\n\n\t --> room_no  : %s", room_no);
            printf("\n\n\t --> room_type  : %s", room_type);
            printf("\n\n\t --> bill  : %s\n\n", bill);

            lines();

            c -= 9;
        }
    }
    else
    {
        printf("\n\n\t\t ==> your history is empty!\n\n");
    }

    help();
}

int FLAG = 0;
int submenu(Room m[], int *n, Customer *c)
{
    c->name[strlen(c->name) - 1] = '\0';
    c->phone_no[strlen(c->phone_no) - 1] = '\0';
    while (1)
    {
        system("cls");
        int flag;
        printf("SOFTWARE SERVICE :- \n\n\t\t\t1 - Booking Room\n\n\t\t\t2 - History\n\n\t\t\t3 - quit\n\nchose your option : ");
        scanf("%d", &flag);
        getchar();

        if (flag == 1)
        {
            if (FLAG == 1)
            {
                system("cls");

                int i = *n;
                printf("i = %d\n", i);
                help();
                strcpy(m[i].cus.name, c->name);
                strcpy(m[i].cus.email_id, c->email_id);
                strcpy(m[i].cus.phone_no, c->phone_no);
                strcpy(m[i].cus.password, c->password);
                m[i].cus.bill = 0;
                m[i].cus.cus_id = i + 1;
                booking(&m[i]);

                help();
                FILE *ftr;
                ftr = fopen("history.txt", "a");
                fprintf(ftr, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", m[i].booking_time, m[i].cus.cus_id, m[i].room_no, m[i].cus.bill, m[i].room_type, m[i].cus.name, m[i].cus.phone_no, m[i].cus.email_id);
                ++(*n);
            }
            else if (FLAG == 0)
            {
                system("cls");
                Room temp;
                strcpy(temp.cus.name, c->name);
                strcpy(temp.cus.email_id, c->email_id);
                strcpy(temp.cus.phone_no, c->phone_no);
                temp.cus.bill = 0;
                temp.cus.cus_id = *n + 1;
                booking(&temp);
                printf("after booking\n");

                FILE *fptr;
                fptr = fopen("decent.txt", "a");
                fprintf(fptr, "%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n", temp.booking_time, (*n) + 1, temp.room_no, temp.cus.bill, temp.room_type, temp.cus.name, temp.cus.phone_no, temp.cus.email_id);

                FILE *fptr2;
                fptr2 = fopen("history.txt", "a");
                fprintf(fptr2, "%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n", temp.booking_time, (*n) + 1, temp.room_no, temp.cus.bill, temp.room_type, temp.cus.name, temp.cus.phone_no, temp.cus.email_id);
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
            printf("\n\n--> sorry! your option not valid. \n");
            help();
            submenu(m, n, c);
        }
    }
}

int sign_in(Customer *cus)
{
    char input_id[100];
    char input_pass[100];
    char fname[100];
    char fphone[100];
    char fid[100];
    char fpass[100];
    char temp[100];
    int c = 0;

    FILE *fptr;
    fptr = fopen("customer.txt", "r");

    int cout = 0;
    while (fgets(temp, sizeof(temp), fptr) != NULL)
    {
        cout++;
    }

    if (cout < 2)
    {
        printf("\n\n\t\t\t==> You need to make your account!\n\n");
        return 0;
    }
    system("cls");
    while (1)
    {
        printf("\n\n\t--> Enter your email_id (for sign in) : ");
        gets(input_id);
        if (isEmail(input_id))
        {
            break;
        }
        else
        {
            printf("\n\n\t\t--> enter valid email_id\n\n");
        }
    }

    printf("\n\n\t--> Enter your password : ");
    hidepass(input_pass);

    if (cout > 1)
    {
        FILE *fptr;
        fptr = fopen("customer.txt", "r");
        while (cout > 0)
        {

            fgets(fname, sizeof(fname), fptr);
            fscanf(fptr, "%s", fid);
            fgets(temp, sizeof(temp), fptr);

            fgets(fphone, sizeof(fphone), fptr);
            fscanf(fptr, "%s", fpass);
            fgets(temp, sizeof(temp), fptr);

            if (!strcmp(fid, input_id) && !strcmp(fpass, input_pass))
            {
                printf("\n\n\t\t\t==> you login successfully!\n\n");
                help();
                strcpy(cus->email_id, fid);
                strcpy(cus->name, fname);
                strcpy(cus->password, fpass);
                strcpy(cus->phone_no, fphone);
                return 1;
            }
            cout -= 4;
        }
    }

    printf("\n\n\t--> email_id is not available!");
    help();
    return 0;
}
void signup(Customer *c)
{
    system("cls");
    char name[100], id[100], pass[100], repass[100], pno[100];
    printf("\n\t\t--> enter your name :- ");

    gets(name);
    while (1)
    {
        printf("\n\t\t--> enter your email_id :- ");

        gets(id);

        if (!isEmail(id))
        {
            printf("\n\t==> your email id invalid!\n");
        }
        else
            break;
    }
    while (1)
    {
        printf("\n\t\t--> enter your phone no :- ");

        gets(pno);

        if (!isPhone(pno))
        {
            printf("\n\t==> your phone no invalid!\n");
        }
        else
            break;
    }
    while (1)
    {
        printf("\n\t\t--> enter your password (pls not forget your password) :- ");
        hidepass(pass);
        printf("\n\t\t--> re-enter your password :- ");
        hidepass(repass);

        if (!strcmp(pass, repass))
        {
            break;
        }
        else
        {
            printf("\n\n\t--> sorry your password is wrong!");
        }
    }

    if (!strcmp(pass, repass))
    {
        strcpy(c->name, name);
        strcpy(c->email_id, id);
        strcpy(c->phone_no, pno);
        strcpy(c->password, pass);
        
    }
}
int forlogin()
{
    int option;
    while (1)
    {
        printf("\n\t\t 1 : for try again\n\t\t 2 : for quit\n");
        printf("choose your option:");
        scanf("%d", &option);
        if (option == 1)
            return 1;
        else if (option == 2)
            return 2;
        else
            printf("\n\t==> your option is invalid!\n");
    }
}

int main()
{
    remove("decent.txt");
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t __        __  _____   __      ____   ___    __  __   _____\n");
    printf("\t\t\t\t\t\t \\ \\      / / | ____| | |     / ___/ / _ \\  |  \\/  | | ____|\n");
    printf("\t\t\t\t\t\t  \\ \\ /\\ / /  |  _|   | |    | |    | | | | | |\\/| | | _|  \n");
    printf("\t\t\t\t\t\t   \\ V  V /   | |___  | |__  | |__  | |_| | | |  | | | |___ \n");
    printf("\t\t\t\t\t\t    \\_/\\_/    |_____| |____|  \\____\\ \\___/  |_|  |_| |_____|\n");
    printf("\n\n\t\t\t\t\t\t---------------------------------------------------------------\n\n");

    help();
    int check;
    int for_old_data = 0;
    system("cls");

    int i = 0;
    int flag_cus = 0;
    int flag_manager = 0;
    int flag = 0;
    int choice;
    int login_for;
    int full = 0;

    Room M[30];
    Manager man;

    while (1)
    {
        if (i == 30)
        {
            system("cls");
            printf("\n\n\n\t\t --> your all rooms are full!\n");
            help();
            break;
        }

        if (flag == 0)
        {
            system("cls");

            printf("\n\n\t\t\t1 - MANAGER\n\n\t\t\t2 - CUSTOMER (For online booking - only for tommorow)\n\n\t\t\t3 - quit\n\nenter your option :- ");
            scanf("%d", &login_for);
            getchar();
            flag = 1;
            system("cls");
            
        }

        if (login_for == 1) // for man.
        {
            if (flag_manager == 0)
            {

                if (Manager_sign_in(&man))
                {
                    if (for_old_data == 0)
                    {
                        flag_manager = 1;
                        check = 0;

                        printf("\n\n\t\t\t\t=> verify your are manager! <=\n\n");

                        while (1)
                        {
                            printf("\n\t\tAre you want you work with old data [y/n] : ");
                            scanf("%c", &olddata);

                            getchar();
                            
                            if (olddata != 'y' && olddata != 'Y' && olddata != 'n' && olddata != 'N')
                            {
                                printf("\n\n\t-->enter valid ans :- ");
                            }
                            else
                            {
                                break;
                            }
                        }

                        for_old_data = 1;
                        printf("\n\n");
                        
                        if (olddata == 'n' || olddata == 'N')
                        {

                            remove("room.txt");
                            FILE *fptr;
                            fptr = fopen("decent.txt", "r");
                            int room_no, cno, bill, count = 0;
                            char name[100], phone[20], email[30], room_type[15], t[15];

                            while (fgets(t, sizeof(t), fptr))
                            {
                                count++;
                            }
                            
                            FILE *file;
                            file = fopen("decent.txt", "r");
                            while (count > 0)
                            {

                                fgets(t, sizeof(t), file);
                                fscanf(file, "%d", &cno);
                                fscanf(file, "%d", &room_no);
                                fscanf(file, "%d", &bill);
                                fgets(room_type, sizeof(room_type), file);
                                fgets(name, sizeof(name), file);
                                fgets(phone, sizeof(phone), file);
                                fgets(email, sizeof(email), file);

                                ForManager(name, email, "\0", phone, bill, i + 1, strcat(t, "(online booking)"), room_no, room_type, &M[i]);
                                i++;
                                count -= 8;
                            }
                        }
                        else
                        {
                            FILE *fptr;
                            fptr = fopen("room.txt", "r");
                            int room_no, cno, bill, count = 0;
                            char name[100], phone[20], email[30], room_type[30], t[30], temp[10];

                            while (fgets(t, sizeof(t), fptr))
                            {
                                count++;
                            }
                           

                            FILE *file;
                            file = fopen("room.txt", "r");
                            while (count > 0)
                            {
                                fgets(t, sizeof(t), file);
                                fscanf(file, "%d", &cno);
                                fscanf(file, "%d", &room_no);
                                fscanf(file, "%d", &bill);
                                fgets(temp, sizeof(temp), file);
                                fgets(room_type, sizeof(room_type), file);
                                fgets(name, sizeof(name), file);
                                fgets(phone, sizeof(phone), file);
                                fgets(email, sizeof(email), file);

                                ForManager(name, email, "\0", phone, bill, i + 1, t, room_no, room_type, &M[i]);

                                i++;
                                count -= 8;
                            }
                            help();
                        }
                    }
                    else
                    {
                        printf("\n\t\t\t=> verify your are manager! <=\n\n");
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
                printf("\n\n\n\n");
                printf("\n\t\t\t\t\tWELCOME TO OUR MOTEL\n");
                printf("\n\t\t\t\t\t1. NEW COUSTOMER\n");
                printf("\n\t\t\t\t\t2. DISPLAY ALL COUSTOMER RECORD\n");
                printf("\n\t\t\t\t\t3. SEARCH ANY CUSTOMER DETAILS\n");
                printf("\n\t\t\t\t\t4. EXTEND BOOKING\n");
                printf("\n\t\t\t\t\t5. ROOM DETAILS\n");
                printf("\n\t\t\t\t\t6. BILL & CHECKOUT\n");
                printf("\n\t\t\t\t\t7. EXIT\n");
                printf("\n\nenter your option : ");
                scanf("%d", &choice);
                getchar();

                system("cls");

                switch (choice)
                {
                case 1:
                {
                    char name[100];
                    char email_id[30];
                    char phone[30];

                    printf("\n\n\tenter customer name : ");
            
                    gets(name);

                    while (1)
                    {
                        printf("\n\n\tenter customer email id : ");
                
                        gets(email_id);
                        if (isEmail(email_id))
                        {
                            break;
                        }
                        else
                        {
                            printf("\n\n\t\t-->pls enter valid email_id.");
                            help();
                        }
                    }

                    while (1)
                    {
                        printf("\n\n\tenter customer phone_no : ");

                        gets(phone);

                        if (isPhone(phone))
                        {
                            break;
                        }
                        else
                        {
                            printf("\n\n\t\t--> pls enter valid phone no.");
                            help();
                        }
                    }
                    ForManager(name, email_id, "\0", phone, 0, i + 1, "\0", 0, "\0", &M[i]);
                    booking(&M[i]);
                    i++;
                }
                break;
                case 2:
                {
                    int c = 0;
                    for (int j = 0; j < i; j++)
                    {
                        if (M[j].room_no > 100 && M[j].room_no < 300)
                        {
                            c++;
                        }
                    }

                    if (i == 0 || c == 0)
                    {
                        printf("\n\n\t--> no record found! \n");
                    }
                    else
                    {
                        {

                            for (int j = 0; j < i; j++)
                            {
                                if (M[j].room_no > 100 && M[j].room_no < 300)
                                {
                                    display_all(&M[j]);
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
                    printf("\n\n\t--> enter customer id for see : ");
                    scanf("%d", &id);
                    getchar();

                    if (id > i || M[id - 1].room_no < 100)
                    {
                        printf("\n\n\t\t--> no record found\n\n");
                        help();
                    }
                    else
                    {
                        
                        search(M[id - 1]);
                        help();
                    }
                }
                break;
                case 4:
                {
                    Room temp;
                    EX_Booking(M, i);
                    help();
                }
                break;
                case 5:
                {
                    Room temp;
                    Room_details(M, i);
                }
                break;
                case 6:
                {
                    int n;
                    printf("\n\n\t--> enter customer id :- ");
                    scanf("%d", &n);
                    getchar();

                    if (n > i || M[n - 1].room_no < 100)
                    {
                        printf("\n\tsorry! %d not avaliable : ", n);
                        help();
                    }
                    else
                    {
                        Checkout(M, i, &M[n - 1]);
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
            printf("SOFTWARE SERVICE :- \n\t\t\t1 - SIGN IN\n\t\t\t2 - SIGN UP\n\t\t\t3 - quit\nchose your option : ");
            scanf("%d", &flag2);
            getchar();

            switch (flag2)
            {
            case 1:
            {
                Customer temp;
                if (sign_in(&temp))
                {

                    int o = submenu(M, &i, &temp);
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
                            if (sign_in(&temp))
                            {
                                int t = submenu(M, &i, &temp);
                                if (t == 3)
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
                Customer t;
                signup(&t);

                printf("\n\n\t\t\t ==> your account succesfully created!\n\n");
                help();
                int option = submenu(M, &i, &t);
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
                printf("\n\n\t-->try again! invalid no");
                help();
                break;
            }
        }
        else if (login_for == 3)
        {
            flag = 0;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\t _____  _   _      _      _   _    _  __   __   __   ___    _   _  \n");
            printf("\t\t\t\t\t\t|_   _|| | | |    / \\    | \\ | |  | |/ /   \\ \\ / /  / _ \\  | | | |  \n");
            printf("\t\t\t\t\t\t  | |  | |_| |   / _ \\   |  \\| |  | ' /     \\ V /  | | | | | | | |\n");
            printf("\t\t\t\t\t\t  | |  |  _  |  / ___ \\  | |\\  |  | . \\      | |   | |_| | | |_| |   _   _   _   _  \n");
            printf("\t\t\t\t\t\t  |_|  |_| |_| /_/   \\_\\ |_| \\_|  |_|\\_\\     |_|    \\___/  \\ ___ /  |_| |_| |_| |_|  \n");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            break;
        }
        else
        {
            printf("\n\n\t--> you enter invalid no , pls try again!\n");
            help();
            flag = 0;
        }
    }
    return 0;
}