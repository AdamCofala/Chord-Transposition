#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Mapa dla podstawowych akordów durowych i molowych
unordered_map<string, int> akordy = {
    {"c", 0}, {"cis", 1}, {"d", 2}, {"dis", 3}, {"e", 4}, {"f", 5},
    {"fis", 6}, {"g", 7}, {"gis", 8}, {"a", 9}, {"b", 10}, {"h", 11}
};

// Odwrotna mapa dla konwersji liczbowej na akordy
vector<string> odwrotneAkordy = {
    "C", "Cis", "D", "Dis", "E", "F", "Fis", "G", "Gis", "A", "B", "H"
};

string transponujAkord(string akord, int transpozycja) {
    bool isMolowy = islower(akord[0]);
    akord[0]=tolower(akord[0]);
    int oryginalnyIndex = akordy[akord];
    int nowyIndex = (oryginalnyIndex + transpozycja + 12) % 12;

    string nowyAkord = odwrotneAkordy[nowyIndex];
    if (isMolowy) {
        nowyAkord[0] = tolower(nowyAkord[0]);
    }

    return nowyAkord;
}

void transponujAkordy(vector<string>& linie, int transpozycja) {
    for (string& linia : linie) {
        string nowaLinia;
        string akord;
        for (char c : linia) {
            if (c == ' ') {
                if (!akord.empty()) {
                    nowaLinia += transponujAkord(akord, transpozycja) + " ";
                    akord.clear();
                }
            } else {
                akord += c;
            }
        }
        if (!akord.empty()) {
            nowaLinia += transponujAkord(akord, transpozycja);
        }
        linia = nowaLinia;
    }
}

void zapisdopliku(vector<string>& linie){
    
    string nazwaPlikuWyjsciowego;
    cout << "Podaj nazwe pliku wyjsciowego: ";
    cin >> nazwaPlikuWyjsciowego;
    nazwaPlikuWyjsciowego+=".txt";

    ofstream plikWyjsciowy(nazwaPlikuWyjsciowego);
    if (!plikWyjsciowy) {
        cout << "Nie mozna utworzyc pliku " << nazwaPlikuWyjsciowego << endl;
    }else{
    
    for (const string& l : linie) {
        plikWyjsciowy << l << endl;
    }
    plikWyjsciowy.close();

    cout << "Zapisano wynik w pliku " << nazwaPlikuWyjsciowego<< endl;
    }
    
}

int main() {
    vector<string> linie;
    int transpozycja;

    // Wczytaj poziom transpozycji
    cout << "Podaj poziom transpozycji (-11 do 11): ";
    cin >> transpozycja;

    // Zapytaj uzytkownika, czy chce wczytac dane z pliku
    cout << "Czy chcesz wpisac dane z pliku dane.txt? (wpisz \"t\" aby wczytac z pliku, lub dowolny klawisz aby wpisac recznie): ";
    char odp;
    cin >> odp;

    if (odp == 't') {
        // Wczytaj dane z pliku dane.txt
        ifstream plik("dane.txt");
        if (!plik) {
            cerr << "Nie mozna otworzyc pliku dane.txt" << endl;
            return 1;
        }

        string linia;
        while (getline(plik, linia)) {
            linie.push_back(linia);
        }
        plik.close();
    } else {
        // Wczytaj dane recznie
        cout << "Wpisz ile linijek danych masz zamiar wpisac: ";
        int liczbaLinii;
        cin >> liczbaLinii;
        cin.ignore();  // Oczyszczanie bufora wejściowego

        cout << "Wpisz akordy (oddzielone spacjami):" << endl;
        for (int i = 0; i < liczbaLinii; ++i) {
            string linia;
            cout << "Linia " << i + 1 << ": ";
            getline(cin, linia);
            linie.push_back(linia);
        }
    }

    // Transponuj akordy
    transponujAkordy(linie, transpozycja);

    // Wyświetl wyniki na ekranie
    cout << "Transponowane akordy:" << endl;
    for (const string& l : linie) {
        cout << l << endl;
    }

    // Zapisz wyniki do pliku
    cout << "Czy chesz zapisac do zapisac transponowane akordy do pliku? (t/n): ";
    char anw;
    cin >> anw;
    if(anw=='t') zapisdopliku(linie);

    return 0;
}
