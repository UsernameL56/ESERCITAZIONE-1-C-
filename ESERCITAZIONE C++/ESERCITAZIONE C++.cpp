#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
    string stringa;
    int scelta;
    bool c = false;
    do {
        system("CLS");              // equivalente Console.Clear()
        cout << "1 - Tiramisu'\n2 - Torta alle mele\n3 - Zuppa inglese\n4 - Pastiera napoletana\n5 - Putizza\n6 - Pandoro\n7 - Panforte\n8 - Panna cotta\n9 - Crostata di fragole\n10 - Strudel\n0 - Uscita\n";
        cout << "Inserire la scelta: ";
        cin >> scelta;
        switch (scelta) {
        default:
            cout << "Opzione non valida!";
            break;
        case 0:
            c = true;
            break;
        case 1:
            cout << "siu";
            break;
        }
        cout << "Premere un tasto per continuare: ";
        cin.ignore(flush);
    } while (!c);

}
