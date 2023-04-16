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
        int pos = line.find(';');
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
                    reader.close();
                    break;
                }
                else {
                    ricetteOrdini << line << endl;
                }
            }
        }
    }
    
}
static void RicavaMenu() {
    string line;
    string sep = ";";
    fstream reader;
    reader.open("Ingredienti.csv", ios::in);
    while (getline(reader, line))
    {
        string split = line.substr(0, line.find(sep));
        cout << "- " << split << endl;
    }
    reader.close();
}

static void StampaProcedimento(string dolceOrdinato) 
{
    string line, sep = ";", ingpath = "Ingredienti.csv", ricpath = "RicetteOrdine.csv";
    fstream reader, readering;
    int p = Ricerca(dolceOrdinato, ingpath);
    if (p == -1) {
        cout << "Errore! Dolce non trovato!" << endl;
    }
    else
    {
        cout << "Ingredienti:" << endl << endl;
        readering.open(ingpath, ios::in);
        while (getline(readering, line))
        {
            if (line.find(dolceOrdinato) != string::npos)
            {
                int inizio = line.find(";"); // Trova il primo carattere ";" nella riga
                while (inizio != string::npos)
                {
                    int fine = line.find(";", inizio + 1); // Trova il prossimo carattere ";" nella riga
                    string sottostringa = line.substr(inizio + 1, fine - inizio - 1); // Estrae la sottostringa tra i due caratteri ";"
                    cout << sottostringa << endl;
                    inizio = fine;
                }
            }
        }
        _getch();
        system("CLS");
        readering.close();
        cout << "Procedimento:" << endl << endl;
        reader.open(ricpath, ios::in);
        while (getline(reader, line))
        {
            if (line.find(dolceOrdinato) != string::npos)
            {

                while (getline(reader, line))
                {
                    if (line.find(";") != string::npos) {
                        cout << line << endl;
                        break;
                    }
                    else {
                        cout << line << endl;
                    }
                }
            }
        }
        _getch();
        reader.close();
    }
}
/*
* FUNZIONE THOMAS CHE NON VOGLIO DISTRUGGERE
static void EliminaDolce(string dolceSelezionato)
{
    string nome_file = "Ingredienti Temp.txt", nome_file_mod = "Ingredienti TempTEMP.txt", line;
    ifstream input(nome_file);
    ofstream output(nome_file_mod);
    int p = Ricerca(dolceSelezionato, nome_file);
    if (p == -1) {
        cout << "Errore! Dolce non trovato!" << endl;
    }
    else {
        input.open(nome_file, ios::in);
        while (getline(input, line))
        {
            if (line.find(dolceSelezionato) != string::npos)
            {

            }
        }
        input.close();
        output.close();
        // Sostituisci il file originale con quello temporaneo
        //remove(nome_file.c_str());
        //rename(nome_file_mod.c_str(), nome_file.c_str());
        cout << "Dolce eliminato con successo!" << endl;
    }
}
*/

static void EliminaDolce(string dolceSelezionato, fstream& output, string nome_file_mod)
{
    string nome_file = "ListaDolci.csv", line;
    fstream input;
    int p = Ricerca(dolceSelezionato, nome_file);
    if (p == -1) {
        cout << "Errore! Dolce non trovato!" << endl;
    }
    else {
        input.open(nome_file, ios::in);
        while (getline(input, line))
        {
            string split = line.substr(0, line.find(";"));
            if (split != dolceSelezionato)
            {
                output << line << endl;
            }
        }
        input.close();
        // Sostituisci il file originale con quello temporaneo


    }
}

static void Sostituzione(string appoggio, string vecchio) {
    remove(vecchio.c_str());
    if (rename(appoggio.c_str(), vecchio.c_str()) == 0)
        cout << "File renamed successfully";
    else
        perror("Error renaming file");
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
    int scelta, dim = 0, indice = 1;
    int r;
    char sceltagg;
    bool exit, c = false;
    string path = "ListaDolci.csv", ord = "RicetteOrdine.csv", nome_file_mod = "Ingredienti TempTEMP.csv", dolceOrdinato;
    fstream ricetteOrdini, ordini, ricavazione, output;
    do {
        system("CLS");
        cout << "1 - Aggiunta dolce\n2 - Ordinazione\n3 - Elimina dolce\n4 - Modifica dolce\n0 - Uscita\n" << endl;
        cout << "Inserire la scelta: ";
        cin >> scelta;
        switch (scelta) {
        default:
            cout << "Opzione non valida!" << endl;
            break;
        case 0:
            c = true;
            break;
        case 1:
            system("CLS");
            AggiuntaMenu(dim, path);
            break;
        case 2:
            remove("RicetteOrdine.csv");
            do
            {
                system("CLS");
                RicavaMenu();
                cout << "Inserire il dolce che si vuole ordinare: ";
                cin >> dolceOrdinato;
                ricetteOrdini.open(ord, ios::out | ios::app);
                Ordinazione(dolceOrdinato, ricetteOrdini);
                ricetteOrdini.close();
                indice++;
                system("CLS");
                StampaProcedimento(dolceOrdinato);
                system("CLS");
                cout << "Inserire un altro dolce? (Y/N) ";
                cin >> sceltagg;
                sceltagg = (sceltagg | ' ') - ' ';
                switch (sceltagg) {
                default:
                    cout << "Input non valido!" << endl;
                    exit = false;
                    break;
                case 'Y':
                    exit = true;
                    break;
                case 'N':
                    exit = false;
                    break;
                }
            } while (exit == true);
            break;
        case 3:
            system("CLS");
            cout << "Inserire il dolce che si desidera eliminare: ";
            cin >> dolceOrdinato;
            r = Ricerca(dolceOrdinato, "Ingredienti.csv");
            if (r == -1) {
                cout << "Dolce non trovato!" << endl;
                cout << "Premere un tasto per continuare...";
                _getch();
            }
            else {
                output.open(nome_file_mod, ios::out);
                EliminaDolce(dolceOrdinato, output, nome_file_mod);
                output.close();
                Sostituzione(nome_file_mod, path);
                cout << "Premere un tasto per continuare...";
                _getch();
            }
            
            
            break;
        case 4:
            break;
            cout << "Premere un tasto per continuare...";
            _getch();
        } 
    } while (!c);
}