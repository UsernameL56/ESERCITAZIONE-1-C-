#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

#pragma region Funzioni
static int Ricerca(string d) {
    int ps = -1;
    ifstream fin("ListaDolci.csv");

}
static void Aggiunta(string d) {
    ofstream fout("Carrello.csv", ios::out | ios::app);
    fout << d + " 1;" << endl;
    fout.close();
}

static void AggiuntaMenu(string DolceFile, int& indice)
{
    indice++;
    fstream file;
    file.open("ListaDolci.csv", ios::out | ios::app);
    file << indice << ";" << DolceFile << endl;
    file.close();
    
}

static void Ricetta() 
{
    string line;
    ifstream file;
    file.open("ListaDolci.csv", ios::in | ios::app);

    ifstream ricetta;
    ricetta.open("Ricetta.csv", ios::out);
    getline("Ricetta.csv", line);
}
/*
void GeneraDispensa()
{
    fstream sr;
    sr.open("", ios::out);
    srand(time(NULL));

    //generazione degli elementi
    sr << "uova: " << rand() % 10 << " pezzi" << endl;
    sr << "farina: " << rand() % 2500 << "g" << endl;
    sr << "zucchero: " << rand() % 2500 << "g" << endl;
    sr << "pangrattato: " << rand() % 1000 << "g" << endl;
    sr << "pinoli: " << rand() % 100 << "g" << endl;
    sr << "uvetta: " << rand() % 100 << "g" << endl;
    sr << "cannella: " << rand() % 10 << "g" << endl;
    sr << "biscotti: " << rand() % 100 << "g" << endl;
    sr << "ricotta: " << rand() % 100 << "g" << endl;
    sr << "formaggio fresco: " << rand() % 100 << "g" << endl;
    sr << "panna: " << rand() % 100 << "g" << endl;
    sr << "marmellata: " << rand() % 1000 << "g" << endl;
    sr << "marsala: " << rand() % 100 << "g" << endl;
    sr << "strutto: " << rand() % 100 << "g" << endl;
    sr << "lievito: " << rand() % 10 << "g" << endl;
    sr << "biga: " << rand() % 100 << "g" << endl;
    sr << "pasta di arance " << rand() % 100 << "g" << endl;
    sr << "pasta di limoni " << rand() % 100 << "g" << endl;
    sr << "pasta di mandarini " << rand() % 100 << "g" << endl;
    sr << "cedro candito " << rand() % 100 << "g" << endl;
    sr << "miele di acacia " << rand() % 100 << "g" << endl;
    sr << "olio: " << rand() % 1000 << "ml" << endl;
    sr << "caffè: " << rand() % 100 << "ml" << endl;
    sr << "mascarpone: " << rand() % 100 << "g" << endl;
    sr << "savoiardi: " << rand() % 100 << "g" << endl;
    sr << "burro: " << rand() % 100 << "g" << endl;
    sr << "sale: " << rand() % 100 << "g" << endl;
    sr << "latte: " << rand() % 2500 << "ml" << endl;
    sr << "cioccolato: " << rand() % 100 << "g" << endl;
    sr << "mele: " << rand() % 10 << " pezzi" << endl;
    sr << "zucchero a velo: " << rand() % 100 << "g" << endl;
    sr << "cialda: " << rand() % 10 << " pezzi" << endl;
    sr.close();
}
*/
#pragma endregion

int main()
{
    char r;
    int scelta;
    string dolce;
    string DolceFile;
    int indice = 1;
    bool c = false;
    do {
        system("CLS");              // equivalente Console.Clear()
        cout << "1 - Scegli Dolce\n2 - \n3 - Aggiungi dolce al menu\n4 - Cancella dolce\n0 - Uscita\n" << endl;
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
            cout << "- Tiramisu'\n- Torta alle mele\n- Zuppa inglese\n- Brownies\n- Torta al cioccolato\n- Torta al limone\n- Pastiera napoletana\n- Panna cotta\n- Crostata di fragole\n- Strudel\n";
            cout << "Inserire il dolce che si vuole selezionare: ";
            cin >> dolce;
            Aggiunta(dolce);
            break;
        case 2:
            
            //Ricerca(dolce);
            break;
        case 3:
            cout << "Inserire il dolce da aggiungere alla lista: ";
            cin >> DolceFile;
            AggiuntaMenu(DolceFile, indice);
            break;


        }
        cout << "Premere un tasto per continuare...";
        cin >> r;
    } while (!c);
}
