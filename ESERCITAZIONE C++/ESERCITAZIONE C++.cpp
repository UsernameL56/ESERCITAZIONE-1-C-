#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <conio.h>

using namespace std;
struct prodotto
{
    string dolce;
    string ingrediente[100];
    int quantità;
};

#pragma region Funzioni
static int Ricerca(string nome, string filePath)
{
    int posizione = -1;
    ifstream file(filePath);
    string line;
    int riga = 0;
    while (getline(file, line))
    {
        riga++;
        size_t pos = line.find(';');
        string name = line.substr(0, pos);
        if (name == nome)
        {
            posizione = riga;
            break;
        }
    }
    file.close();
    return posizione;
}
static void Aggiunta(string nome, string ingrediente, string filePath)
{
    ofstream file(filePath, ios::app);
    file << nome << ";" << ingrediente << ";1" << endl;
    file.close();
}

static void AggiuntaMenu(int dim, string path)
{
    fstream file;
    int q;
    prodotto p;
    cout << "Inserire il dolce: ";
    cin >> p.dolce;
    cout << "Inserire il numero di ingredienti necessari: ";
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cout << "Inserire l'ingrediente " << i << ": ";
        cin >> p.ingrediente[i - 1];
    }
    file.open(path, ios::out | ios::app);
    file << p.dolce;
    for (int i = 1; i <= q; i++)
    {
        file << ";" << p.ingrediente[i - 1];
    }
    file << endl;
    file.close();
    dim++;
    
}

static void Ricetta(string input) 
{
    string line;
    ifstream file;
    file.open("Ricette.csv", ios::in | ios::app);

    ifstream ricetta;
    ricetta.open("Ricetta.csv", ios::out);
    if (ricetta.is_open())
    {
        while (getline(ricetta, line))
        {
            cout << line << '\n';
            if (line == "!")
            {
                break;
            }
        }
        ricetta.close();
        file.close();
    }
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
    
    prodotto p;
    int scelta;
    int dim = 0;
    string path = "ListaDolci.csv";
    string d;
    string DolceFile;
    int indice = 1;
    bool c = false;
    
    do {
        system("CLS");              // equivalente Console.Clear()
        cout << "1 - Aggiunta dolce\n2 - Ordinazione\n3 - Elimina dolce\n4 - Ricerca ricetta\n5 - Modifica dolce\n0 - Uscita\n" << endl;
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
            AggiuntaMenu(dim, path);
            /*
            if (dim < 100)
            {
                bool esist = false;
                int ps = 0;
                for (int i = 0; i < dim; i++)
                {
                    if (d == p[i].dolce)
                    {
                        esist = true;
                        ps = i;
                    }
                }
                if (!esist)
                {
                    p[dim].dolce = d;
                    p[dim].ingrediente = in;
                    p[dim].quantità = 1;
                    dim++;
                }
                else
                {
                    p[ps].quantità++;
                }
            }
            else
            {
                cout << "Array pieno!, Errore!" << endl;
            }
            */
            break;
        case 2:
            cout << "gg";            
            break;
        case 3:
            break;
        }
        cout << "Premere un tasto per continuare...";
        _getch();
    } while (!c);
}
