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
    "e", "f", "fis", "g", "gis", "a", "b", "h", "c", "cis", "d", "dis"
};


string transponujAkord(string akord, int transpozycja) {

    bool isMolowy = islower(akord[0]); // sprawdza czy akord był molowy czy durowy
    akord[0]=tolower(akord[0]);

    // Znajdowanie indexu akordu
    int oryginalnyIndex;
    if(find(Akordy,akord)!=-1) oryginalnyIndex = find(Akordy,akord); 
    else return "---";

    // Obliczanie nowego indexu akordu i tworzenie go
    int nowyIndex = (oryginalnyIndex + transpozycja + 12) % 12;
    string nowyAkord = Akordy[nowyIndex];

    if (!isMolowy) nowyAkord[0] = toupper(nowyAkord[0]); // zamienianie akordu na durowy jeśli taki był wcześniej
    
    return nowyAkord;
}

void transponujAkordy(vector<string>& linie, int transpozycja) {
    for (string& linia : linie) {

        string nowaLinia;
        string akord;
        
        linia += " "; // Dodajemy spację na końcu, aby przetworzyć ostatni akord

        for (char c : linia) {
            if (c == ' ') {
                if (!akord.empty()) {
                    nowaLinia += transponujAkord(akord, transpozycja) + " ";
                    akord.clear();  // Resetujemy akord po przetworzeniu
                }
            } else {
                akord += c;
            }
        }
        linia = nowaLinia; // Zastępujemy oryginalną linię przetworzonymi akordami
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
    cout << "Czy chesz zapisac transponowane akordy do pliku? (t/n): ";
    char anw;
    cin >> anw;
    if(anw=='t') zapisdopliku(linie);

    // Zamyka program dopiero po akcji użytkownika
    int tmp;
    cin>>tmp;

    return 0;
}
