#include "Sorters.hpp"
#include "stats.hpp"

#include <random>

#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

ostream &operator<<(ostream &os, const vector<int> &v)
{
    for (auto elem : v)
    {
        os << elem << ' ';
    }
    return os;
}

int check()
{
    int number = 0;

    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n')
            ;
        cout << "Incorrect value\n";
    }

    return number;
}

vector<int> *random_vector(int size)
{
    vector<int> *v = new vector<int>(size);
    for (int i = 0; i < size; i++)
    {
        v->at(i) = lcg();
    }
    return v;
}

int MenuChoice()
{
    cout << "\n\t[1] - Regenerate vector" << endl;
    cout << "\n\t[2] - Insertion sort" << endl;
    cout << "\n\t[3] - Quicksort" << endl;
    cout << "\n\t[4] - Comd sort" << endl;
    cout << "\n\t[5] - buffer" << endl;
    cout << "\n\n\tEsc - Exit" << endl;
    while (true)
    {
        int key = getch();
        if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 54) || (key == 127) || (key == 27))
        {
            return key;
        }
    }
}

vector<int> *regenerate_vector()
{
    cout << "Input length of new vector: " << endl;
    int l = check();
    return random_vector(l);
}

void process_sort(stats (*sort)(vector<int> *), vector<int> *v)
{
    vector<int> COPY(*v);
    vector<int> *pt = &COPY;
    cout << "Result of sorting:" << endl;
    sort(pt);
    cout << *pt << endl;
}

void process_quicksort(vector<int> Vector)
{
    cout << "Quicksort\n\n";
    quickSort(&Vector, 0, Vector.size() - 1);
    cout << "Result of sorting:" << endl;
    cout << Vector << endl;
}

void menu()
{

    vector<int> *Vector = nullptr;

    while (true)
    {
        system("clear");
        if (Vector != nullptr)
            cout << *Vector << endl;
        int Choice = MenuChoice();

        switch (Choice)
        {
        case 49:
            Vector = regenerate_vector();
            break;
        case 50:
            cout << "Insertion sort\n\n";
            process_sort(insertion_sort, Vector);
            break;
        case 51:
            process_quicksort(*Vector);
            break;
        case 52:
            cout << "Comd sort\n\n";
            process_sort(comb_sort, Vector);
            break;
        case 53:
            // test
            break;
        case 27: // Exit
            system("clear");
            return;
            break;
        default:
            break;
        }

        cout << "Press any key" << endl;
        getch();
    }
}

int main(int argc, const char **argv)
{
    menu();

    return EXIT_SUCCESS;
}
