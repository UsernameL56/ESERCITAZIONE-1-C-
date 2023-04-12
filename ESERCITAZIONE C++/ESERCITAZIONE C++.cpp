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
    int quantità[100];
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

static void AggiuntaMenu(int &dim, string path)
{
    
    fstream file;
    int q;
    prodotto p;
    fstream dispensa;
    if (dim < 100)
    {
        cout << "Inserire il dolce: ";
        cin >> p.dolce;
        cout << "Inserire il numero di ingredienti necessari: ";
        cin >> q;
        for (int i = 1; i <= q; i++) {
            cout << "Inserire l'ingrediente " << i << ": ";
            cin >> p.ingrediente[i - 1];
            cout << "Inserire la quantita di quell'ingrediente: ";
            cin >> p.quantità[i - 1];
            
           
        }
        dispensa.open("Dispensa.csv", ios::out | ios::app);
        for (int i = 1; i <= q; i++)
        {
            dispensa << p.ingrediente[i - 1] << ";" << "..." << endl;
        }

        file.open(path, ios::out | ios::app);
        file << p.dolce;
        for (int i = 1; i <= q; i++)
        {
            file << ";" << p.ingrediente[i - 1] << " " << p.quantità[i - 1];
        }
        file << endl;
        file.close();

        dim++;
    }
    else {
        cout << "Errore! Limite massimo raggiunto" << endl;
    }
}

static void Ordinazione(string dolceOrdinato, fstream& ricetteOrdini)
{
    string line;
    fstream reader;
    reader.open("RicettarioGenerale.csv", ios::in);
    while (getline(reader, line))
    {
        if (line.find(dolceOrdinato) != string::npos)
        {
            ricetteOrdini << line << endl;
            while (getline(reader, line))
            {
                if (line.find(";") != string::npos) {
                    ricetteOrdini << line << endl;
                    ricetteOrdini << endl;
                    break;
                }
                else {
                    ricetteOrdini << line << endl;
                }
            }
        }
    }
    reader.close();
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
    char exit = 'N';
    int dim = 0;
    string path = "ListaDolci.csv";
    string ord = "RicetteOrdine.csv";
    string dolceOrdinato;
    int indice = 1;
    bool c = false;
    fstream ricetteOrdini;
    fstream ordini;

    do {
        system("CLS");              // equivalente Console.Clear()
        cout << "1 - Aggiunta dolce\n2 - Ordinazione\n3 - Elimina dolce\n4 - Ricerca ricetta\n5 - Modifica dolce\n0 - Uscita\n" << endl;
        cout << "Inserire la scelta: ";
        cin >> scelta;
        switch (scelta) {
        default:
            cout << "Opzione non valida!"<<endl;
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
            remove("RicetteOrdine.csv");
            do
            {
                system("CLS");
                cout << "Menu: \n- Tiramisu \n- Torta-alle-mele \n- Zuppa-inglese \n- Brownies \n- Torta-al-cioccolato \n- Torta-al-limone \n- Pastiera-napoletana \n- Panna-cotta \n- Crostata-di-fragole \n- Strudel-di-pere-e-cioccolato" << endl;
                cout << "Inserire il dolce che si vuole ordinare: ";
                cin >> dolceOrdinato;
                ricetteOrdini.open(ord, ios::out | ios::app);
                Ordinazione(dolceOrdinato, ricetteOrdini);
                ricetteOrdini.close();
                indice++;
                cout << "Inserire un altro dolce? (Y/N) ";
                cin >> exit;
                exit = (exit | ' ') - ' ';
            } while (exit != 'N');
            break;
        case 3:
            break;
        }
        cout << "Premere un tasto per continuare...";
        _getch();
    } while (!c);
}