#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;
struct prodotto
{
    string dolce;
    string ingrediente[100];
    string procedimento[100];
    int indice = 0;
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
static bool AggiuntaDispensa(string ingrediente, fstream& dispensa) 
{
    fstream reader;
    reader.open("Dispensa.csv", ios::in);
    string line;
    bool controllo = true;
    while (getline(reader, line))
    {
        string split = line.substr(0, line.find(";"));
        if (split != ingrediente)
        {
            controllo = true;
        }
        else
            controllo = false;
    }
    reader.close();
    return controllo;
}
static void AggiuntaMenu(string dolceOrdinato, int &dim, string path)
{
    fstream file, dispensa, reader, prc;
    string line;
    bool controllo;
    int q, pr;
    prodotto p;
    int r = Ricerca(dolceOrdinato, path);
    if (r == -1)
    {
        if (dim < 100)
        {
            p.dolce = dolceOrdinato;
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
            dispensa.close();


            file.open(path, ios::out | ios::app);
            file << p.dolce;
            for (int i = 1; i <= q; i++)
            {
                file << ";" << p.ingrediente[i - 1] << " " << p.quantità[i - 1];
            }
            file << endl;
            file.close();

            cout << "Inserire il numero di procedimenti necessari: ";
            cin >> pr;
            for (int i = 1; i <= pr; i++) 
            {
                cout << "Inserire il " << i << " passaggio: ";
                cin >> p.procedimento[i - 1];
            }
            prc.open("RicettarioMomentaneo.csv", ios::out | ios::app);
            prc << endl << p.dolce << ";";
            for (int i = 1; i <= pr; i++) 
            {
                prc << i << ". " << p.procedimento[i - 1] << ";";
            }
            prc.close();
            dim++;
        }
        else {
            cout << "Errore! Limite massimo raggiunto" << endl;
        }
    }
    else {
        cout << "Dolce gia presente!" << endl;
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
    string line, sep = ";";
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
    string line, sep = ";", ingpath = "Ingredienti.csv", ricpath = "RicettarioGenerale.csv";
    fstream reader, readering;
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
    reader.close();
}
static void EliminaDolce(string dolceSelezionato, fstream& output, string nome_file_mod)
{
    string nome_file = "ListaDolci.csv", line, nome_file2 = "RicettarioGenerale.csv", ricettarioMom = "RicettarioMomentaneo.csv";
    fstream input, input2, output2;
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
    output2.open(ricettarioMom, ios::out);
    input2.open(nome_file2, ios::in);
    while (getline(input2, line))
    {
        string split = line.substr(0, line.find(";"));
        if (split != dolceSelezionato)
        {
            output2 << line << endl;
        }
    }
    input2.close();
    output2.close();
}
static void ModificaDolce(string dolceSelezionato, string nuovoDolce, fstream& output, string nome_file_mod)
{
    string nome_file = "ListaDolci.csv", line, rcg = "RicettarioGenerale.csv", nome_file_mod2 = "RicettarioMomentaneo.csv";
    fstream input, input2, output2;
    int indice = 1;
    prodotto p;
    input.open(nome_file, ios::in);
    while (getline(input, line))
    {
        string split = line.substr(0, line.find(";"));
        if (split != dolceSelezionato)
        {
            output << line << endl;
        }
        else {
            output << nuovoDolce;
            string split2 = line.substr(split.length());
            output << split2 << endl;
        }
    }
    input.close();

    output2.open(nome_file_mod2, ios::out);
    input2.open(rcg, ios::in);
    while (getline(input2, line))
    {
        string split = line.substr(0, line.find(";"));
        if (split != dolceSelezionato)
        {
            output2 << line << endl;
        }
        else {
            output2 << nuovoDolce;
            string split2 = line.substr(split.length());
            output2 << split2 << endl;
        }
    }
    input2.close();
    output2.close();
}
static void Sostituzione(string appoggio, string vecchio) {
    remove(vecchio.c_str());
    if (rename(appoggio.c_str(), vecchio.c_str()) == 0)
        cout << "File renamed successfully" << endl;
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
    int scelta, dim = 0, indice = 1, r;
    char uscita;
    bool c = false;
    string path = "ListaDolci.csv", ord = "RicetteOrdine.csv", nome_file_mod = "Ingredienti TempTEMP.csv", dolceOrdinato, nuovoDolce;
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
            cout << "Inserire il dolce: ";
            cin >> dolceOrdinato;
            dolceOrdinato[0] = toupper(dolceOrdinato[0]);
            AggiuntaMenu(dolceOrdinato, dim, path);
            break;
        case 2:
            remove("RicetteOrdine.csv");
            do
            {
                system("CLS");
                RicavaMenu();
                cout << "Inserire il dolce che si vuole ordinare: ";
                cin >> dolceOrdinato;
                dolceOrdinato[0] = toupper(dolceOrdinato[0]);
                r = Ricerca(dolceOrdinato, "Ingredienti.csv");
                if (r == -1) {
                    cout << "Dolce non trovato!" << endl;
                    _getch();
                }
                else {
                    ricetteOrdini.open(ord, ios::out | ios::app);
                    Ordinazione(dolceOrdinato, ricetteOrdini);
                    ricetteOrdini.close();
                    indice++;
                    system("CLS");
                    StampaProcedimento(dolceOrdinato);
                }
                system("CLS");
                cout << "Inserire un altro dolce? (Y/N) ";
                cin >> uscita;
                uscita = toupper(uscita);
                while (uscita != 'Y' && uscita != 'N') {
                    system("CLS");
                    cout << "Inserire un altro dolce? (Y/N)" << endl << "Inserire come input 'Y' o 'N'" << endl;
                    cin >> uscita;
                    uscita = toupper(uscita);
                }
            } while (uscita != 'N');
            break;
        case 3:
            system("CLS");
            RicavaMenu();
            cout << "Inserire il dolce che si desidera eliminare: ";
            cin >> dolceOrdinato;
            dolceOrdinato[0] = toupper(dolceOrdinato[0]);
            r = Ricerca(dolceOrdinato, "Ingredienti.csv");
            if (r == -1) {
                cout << "Dolce non trovato!" << endl;
            }
            else {
                output.open(nome_file_mod, ios::out);
                EliminaDolce(dolceOrdinato, output, nome_file_mod);
                output.close();
                Sostituzione(nome_file_mod, path);
            }
            break;
        case 4:
            system("CLS");
            RicavaMenu();
            cout << "Inserire il dolce che si desidera modificare: ";
            cin >> dolceOrdinato;
            dolceOrdinato[0] = toupper(dolceOrdinato[0]);
            r = Ricerca(dolceOrdinato, "Ingredienti.csv");
            if (r == -1) {
                cout << "Dolce non trovato!" << endl;
            }
            else {
                cout << "Inserire il nuovo dolce: ";
                cin >> nuovoDolce;
                nuovoDolce[0] = toupper(nuovoDolce[0]);
                output.open(nome_file_mod, ios::out);
                ModificaDolce(dolceOrdinato, nuovoDolce, output, nome_file_mod);
                output.close();
                Sostituzione(nome_file_mod, path);
            }
            break;
        }
        cout << "Premere un tasto per continuare...";
        _getch();
    } while (!c);
}