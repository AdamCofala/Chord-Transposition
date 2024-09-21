#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int find(const vector<string> A, string s){
    for(int i=0; i<A.size(); i++){
        if(A[i]==s) return i;
    }
    return -1;
}

vector<string> Akordy = {
    "c", "cis", "d", "dis", "d", "f", "fis", "g", "gis", "a", "b", "h"
};

string transponujAkord(string akord, int transpozycja) {

    bool isMolowy = islower(akord[0]);
    akord[0]=tolower(akord[0]);

    int oryginalnyIndex;
    if(find(Akordy,akord)!=-1) oryginalnyIndex = find(Akordy,akord);
    else return "---";

    int nowyIndex = (oryginalnyIndex + transpozycja + 12) % 12;

    string nowyAkord = Akordy[nowyIndex];
    if (!isMolowy) {
        nowyAkord[0] = toupper(nowyAkord[0]);
    }

    return nowyAkord;
}

void transponujAkordy(vector<string>& linie, int transpozycja) {
    for (string& linia : linie) {

        string nowaLinia;
        
        linia+=" ";

        for (char c : linia) {
            string akord;
            if (c == ' ') {
                if (!akord.empty()) {
                    nowaLinia += transponujAkord(akord, transpozycja) + " ";
                    akord.clear();
                }
            } else {
                akord += c;
            }
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
            cout << "Nie mozna otworzyc pliku dane.txt" << endl;
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
