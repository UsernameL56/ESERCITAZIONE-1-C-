#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
    char r;
    int scelta;
    string dolce;
    string DolceFile;
    bool c = false;
    do {
        system("CLS");              // equivalente Console.Clear()
        cout << "1 - Stampa lista\n2 - Scegli dolce\n3 - Aggiungi dolce\n4 - Cancella dolce\n0 - Uscita\n" << endl;
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
            system("CLS");
            cout << "- Tiramisu'\n- Torta alle mele\n- Zuppa inglese\n- Pastiera napoletana\n- Putizza\n- Pandoro\n- Panforte\n- Panna cotta\n- Crostata di fragole\n- Strudel\n";
            break;
        case 2:
            cout << "Inserire il dolce che si vuole selezionare: ";
            cin >> dolce;
            Aggiunta(dolce);
            //Ricerca(dolce);
            break;
        case 3:
            cout << "Inserire il dolce da aggiungere alla lista: ";
            cin >> DolceFile;
            AggiuntaMenu(DolceFile);
            break;


        }
        cout << "Premere un tasto per continuare... ";
        cin >> r;
    } while (!c);
}
static int Ricerca(string d) {
    int ps = -1;
    ifstream fin("ListaDolci.csv");

}
static void Aggiunta(string d) {
    ofstream fout("Carrello.csv", ios::app);
    if (fout.is_open()) {
        fout << d + "1" << endl;
    }
    fout.close();
}

    static void AggiuntaMenu(string DolceFile) {
    ofstream file("ListaDolci.csv", ios::app);
    if (file.is_open()) {
        file << "1 - " << DolceFile << endl;
    }
    file.close();
}