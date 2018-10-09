#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace std;
const int KOM_ROZMIAR = 100;
const int DANA_DL = 20;
const int BUFOR = 50;
const int STUDENT_DANE = 4;
const int PROJEKT_DANE = 3;
const int KOMENT_DANE = 3;
const char DANE_OS[] = "Dane_osobowe.txt";
const char PROJEKTY[] = "Projekty.txt";
const char KOMENT[] = "Komentarze.txt";
struct Student {
	int index;
	string imie;
	string nazwisko;
	string email;
};
struct Projekt {
	int ktoryStudent;
	int nr_projektu;
	string data;

};
struct Komentarz {
	int cel;
	char data[DANA_DL];
	char dana[KOM_ROZMIAR];
};
void wczytajStudenta(fstream &plik, Student &student) {
	if (plik.is_open() && plik.good()) {
		plik >> student.index;
		plik >> student.imie;
		plik >> student.nazwisko;
		plik >> student.email;
	}
}
void wczytajProjekt(fstream &plik, Projekt &projekt) {
	if (plik.is_open() && plik.good()) {
		plik >> projekt.ktoryStudent;
		plik >> projekt.nr_projektu;
		plik >> projekt.data;
	}
}
void kopiuj(string lin, char tab[], int &ind) {
	int j = 0;

	while (lin[ind] != '\0' && lin[ind] != '\t') {
		tab[j] = lin[ind];
		j++;
		ind++;
	}
	tab[j] = '\0';

	ind--;
}
void wypisz_studenta(Student st){
	cout << st.index << '\t' << st.imie << '\t' << st.nazwisko << '\t' << st.email << '\n';
}
void wypisz_projekt(Projekt proj,Student st){
	cout << st.imie << '\t' << st.nazwisko << '\t' << st.index << '\t' << proj.data <<'\t'<< proj.nr_projektu << '\n';
}
void wypisz_kom_stud(Komentarz km,Student st){
	cout << st.index << '\t' << st.imie << '\t' << st.nazwisko << '\t' << km.dana << '\t' << km.data << '\n';
}
void wypisz_kom_proj(Komentarz km, Projekt pr){
	cout << pr.ktoryStudent << '\t' << pr.nr_projektu  << '\t' << km.dana << '\t' << km.data << '\n';
}
void wczytajKom(fstream &plik, Komentarz &kom) {
	string temp;
	int zmiana = 1;
	char tab[BUFOR];
	bool liczba = true;
	getline(plik, temp);
	int i = 0;
	bool in = false;
	while (temp[i] != '\0') {
		if (temp[i] != ' ' && temp[i] != '\t') in = true;
		if (in == true) {
			kopiuj(temp, tab, i);
			in = false;
			switch (zmiana)
			{
			case 1:
				kom.cel = atoi(tab);
				zmiana++;
				break;
			case 2:
				strcpy(kom.data, tab);
				zmiana++;
				break;
			case 3:
				strcpy(kom.dana, tab);
				zmiana++;
				break;
			default:
				break;
			}
			if (zmiana > 3) break;
		}
		i++;
	}
}


void dodaj_studenta() {
	fstream plik(DANE_OS, ios::in);
	if (!plik.is_open()) return;
	string dane[STUDENT_DANE];
	for (int i = 0; i < STUDENT_DANE; i++) {
		switch (i){
		case 0:
			cout << "Podaj indeks"<<endl;
			break;
		case 1:
			cout << "Podaj imie" << endl;
			break;
		case 2:
			cout << "Podaj nazwisko" << endl;
			break;
		case 3:
			cout << "Podaj email" << endl;
			break;
		}
		cin >> dane[i];
	}
	string temp;
	while (1){
		plik >> temp;
		if (plik.eof()) break;
		if (dane[0] == temp){
			cout << "nie mozna dodac, index juz istnieje" << endl;
			return;
		}
		for (int i = 0; i < STUDENT_DANE - 1; i++){
			plik >> temp;
		}
	}
	plik.close();
	plik.open(DANE_OS, ios::out | ios::app);
	for (int i = 0; i < STUDENT_DANE; i++) {
		plik << dane[i];
		plik << '\t';
	}
	plik << '\n';
	plik.close();
	system("cls");
}
void dodaj_studenta(Student temp, fstream &plik) {
	plik << temp.index;
	plik << '\t';
	plik << temp.imie;
	plik << '\t';
	plik << temp.nazwisko;
	plik << '\t';
	plik << temp.email;
	plik << '\n';
}
void dodaj_projekt(Projekt temp, fstream &plik) {
	plik << temp.ktoryStudent;
	plik << '\t';
	plik << temp.nr_projektu;
	plik << '\t';
	plik << temp.data;
	plik << '\t';
	plik << '\n';
}
void dodaj_kom(Komentarz temp, fstream &plik){
	plik << temp.cel;
	plik << '\t';
	plik << temp.data;
	plik << '\t';
	plik << temp.dana;
	plik << '\t';
	plik << '\n';
}
void modyfikuj_studenta(){
	system("cls");
	fstream plik(DANE_OS, ios::in);
	if (!plik.good()) return;
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	int nr;
	string dane[3];
	Student temp;
	cout << "Podaj indeks studenta" << endl;
	cin >> nr;
	cout << "Podaj nowe imie" << endl;
	cin >> dane[0];
	cout << "Podaj nazwisko" << endl;
	cin >> dane[1];
	cout << "Podaj nowy mail" << endl;
	cin >> dane[2];
	bool znaleziony = false;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		if (temp.index == nr){
			znaleziony = true;
			nowy << nr << '\t' << dane[0] << '\t' << dane[1] << '\t' << dane[2] << '\n';
		}
		else dodaj_studenta(temp, nowy);
	}
	plik.close();
	remove(DANE_OS);
	nowy.close();
	rename("nowy.txt", DANE_OS);
	if (znaleziony == false) cout << "nie znaleziono studenta"<<endl;
	else cout << "zmodyfikowano !" << endl;
}

void usun_studenta() {
	system("cls");
	fstream plik(DANE_OS, ios::in);
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	cout << "Podaj indeks studenta do usuniecia" << endl;
	int klucz;
	cin >> klucz;
	Student temp;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		if (temp.index != klucz) dodaj_studenta(temp, nowy);
	}
	plik.close();
	remove(DANE_OS);
	nowy.close();
	rename("nowy.txt", DANE_OS);
	cout << "usunieto studenta" << endl;
}
void usun_studenta_naz() {
	system("cls");
	fstream plik(DANE_OS, ios::in);
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	cout << "Podaj nazwisko studenta do usuniecia" << endl;
	string nazwisko;
	cin >> nazwisko;
	Student temp;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		if (temp.nazwisko != nazwisko) dodaj_studenta(temp, nowy);
	}
	plik.close();
	remove(DANE_OS);
	nowy.close();
	rename("nowy.txt", DANE_OS);
	cout << "usunieto studenta" << endl;
}
void wypisz_studentow(){
	fstream plik(DANE_OS, ios::in);
	if (!plik.good()){
		cout << "nie znaleziono pliku :(" << endl;
		return;
	}
	Student temp;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		wypisz_studenta(temp);
	}
}
void studenci(){
	system("cls");
	int btn;
	cout << "1.Dodaj" << endl;
	cout << "2.Modyfikuj" << endl;
	cout << "3.Usun - indeks" << endl;
	cout << "4.Usun - nazwisko" << endl;
	cin >> btn;
	switch (btn){
	case 1:
		dodaj_studenta();
		break;
	case 2:
		modyfikuj_studenta();
		break;
	case 3:
		usun_studenta();
		break;
	case 4:
		usun_studenta_naz();
		break;
	default:
		return;
	}
}
void dodaj_projekt(){
	fstream plik(PROJEKTY, ios::in);
		if (!plik.is_open()) return;
		string dane[PROJEKT_DANE];
		for (int i = 0; i < PROJEKT_DANE; i++) {
			switch (i){
			case 0:
				cout << "Podaj indeks studenta" << endl;
				break;
			case 1:
				cout << "Podaj numer projektu" << endl;
				break;
			case 2:
				cout << "Podaj date przeslania" << endl;
				break;
			}
			cin >> dane[i];
		}
		Projekt proj;
		while (1){
			wczytajProjekt(plik, proj);
			if (plik.eof())break;
			if (proj.nr_projektu == stoi(dane[1])){
				cout << "projekt juz istnieje " << endl;
				return;
			}
		}
		plik.clear();
		plik.close();
		plik.open(PROJEKTY, ios::out | ios::app);
		string temp;
		for (int i = 0; i < PROJEKT_DANE; i++) {
			plik << dane[i];
			plik << '\t';
		}
		plik << '\n';
		plik.close();
		system("cls");
}
void modyfikuj_projekt(){
	system("cls");
	fstream plik(PROJEKTY, ios::in);
	if (!plik.good()) return;
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	int nr, indeks;
	string data;
	Projekt temp;
	cout << "Podaj indeks studenta" << endl;
	cin >> indeks;
	cout << "Podaj nr projektu" << endl;
	cin >> nr;
	cout << "podaj nowa date" << endl;
	cin >> data;
	bool znaleziony = false;
	while (1){
		wczytajProjekt(plik, temp);
		if (plik.eof())break;
		if (temp.nr_projektu == nr && temp.ktoryStudent == indeks){
			znaleziony = true;
			nowy << indeks << '\t' << nr << '\t' << data << '\n';
		}
		else  dodaj_projekt(temp, nowy);
	}
	plik.close();
	remove(PROJEKTY);
	nowy.close();
	rename("nowy.txt", PROJEKTY);
	if (znaleziony == false) cout << "nie znaleziono projektu" << endl;
	else cout << "zmodyfikowano !" << endl;
}
void usun_projekt(){
	system("cls");
	fstream plik(PROJEKTY, ios::in);
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	int indeks,nr;
	cout << "Podaj indeks studenta " << endl;
	cin >> indeks;
	cout << "Podaj nr projektu " << endl;
	cin >> nr;
	Projekt temp;
	while (1){
		wczytajProjekt(plik, temp);
		if (plik.eof())break;
		if (temp.ktoryStudent != indeks && temp.nr_projektu !=nr) dodaj_projekt(temp, nowy);
	}
	plik.close();
	remove(PROJEKTY);
	nowy.close();
	rename("nowy.txt", PROJEKTY);
	cout << "usunieto projekt" << endl;
}
void projekty(){
	system("cls");
	int btn;
	cout << "1.Dodaj" << endl;
	cout << "2.Modyfikuj" << endl;
	cout << "3.Usun - indeks" << endl;
	cin >> btn;
	switch (btn){
	case 1:
		dodaj_projekt();
		break;
	case 2:
		modyfikuj_projekt();
		break;
	case 3:
		usun_projekt();
		break;

	default:
		return;
	}
}
void dodaj_komentarz(){
	fstream plik(KOMENT,ios::out | ios::app);
	if (!plik.is_open()) return;
	string dane[KOMENT_DANE-1];
	char text[BUFOR];
	for (int i = 0; i < KOMENT_DANE-1; i++) {
		switch (i){
		case 0:
			cout << "Podaj cel komentarza" << endl;
			break;
		case 1:
			cout << "Podaj date" << endl;
			break;
		}
		cin >> dane[i];
	}
	cout << "Podaj tresc komentarza" << endl;
	cin.ignore(1000, '\n');
	cin.getline(text, BUFOR);
	for (int i = 0; i < STUDENT_DANE-1; i++) {
		plik << dane[i];
		plik << '\t';
	}
	plik << text;
	plik << '\n';
	plik.close();
	system("cls");
}
void modyfikuj_komentarz(){
	system("cls");
	fstream plik(KOMENT, ios::in);
	if (!plik.good()) return;
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	int nr;
	string data;
	char text[BUFOR];
	Komentarz temp;
	cout << "Podaj cel komentarza" << endl;
	cin >> nr;
	cout << "Podaj date komentarza" << endl;
	cin >> data;
	cout << "podaj nowa tresc" << endl;
	cin.ignore(1000, '\n');
	cin.getline(text, BUFOR);
	bool znaleziony = false;
	while (1){
		wczytajKom(plik, temp);
		if (plik.eof())break;
		if (temp.cel == nr && temp.data == data){
			znaleziony = true;
			nowy << nr << '\t' << data << '\t' << text << '\n';
		}
		else  dodaj_kom(temp, nowy);
	}
	plik.close();
	remove(KOMENT);
	nowy.close();
	rename("nowy.txt", KOMENT);
	if (znaleziony == false) cout << "nie znaleziono projektu" << endl;
	else cout << "zmodyfikowano !" << endl;
}
void usun_komentarz(){
	system("cls");
	fstream plik(KOMENT, ios::in);
	fstream nowy("nowy.txt", ios::out | ios::trunc);
	if (!plik.good() && !nowy.good()){
		cout << "nie mozna otworzyc plikow" << endl;
		return;
	}
	int cel;
	string data;
	cout << "Podaj cel" << endl;
	cin >> cel;
	cout << "Podaj date kom " << endl;
	cin >> data;
	Komentarz temp;
	while (1){
		wczytajKom(plik, temp);
		if (plik.eof())break;
		if (temp.cel != cel && temp.data != data) dodaj_kom(temp, nowy);
	}
	plik.close();
	remove(KOMENT);
	nowy.close();
	rename("nowy.txt", KOMENT);
	cout << "usunieto komentarz" << endl;
}
void komentarze(){
	system("cls");
	int btn;
	cout << "1.Dodaj" << endl;
	cout << "2.Modyfikuj" << endl;
	cout << "3.Usun" << endl;
	cin >> btn;
	switch (btn){
	case 1:
		dodaj_komentarz();
		break;
	case 2:
		modyfikuj_komentarz();
		break;
	case 3:
		usun_komentarz();
		break;

	default:
		return;
	}
}
void szukaj_stud_ind(){
	system("cls");
	fstream plik(DANE_OS, ios::in);
	if (!plik.good()){
		cout << "NIE MOZNA ZNAEZC PLIKU" << endl;
		return;
	}
	int index;
	cout << "Podaj index szukany" << endl;
	cin >> index;
	Student temp;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		if (temp.index == index)
			wypisz_studenta(temp);
	}
	plik.close();
}
void szukaj_stud_naz(){
	system("cls");
	fstream plik(DANE_OS, ios::in);
	if (!plik.good()){
		cout << "NIE MOZNA ZNAEZC PLIKU" << endl;
		return;
	}
	string naz;
	cout << "Podaj nazwisko szukane" << endl;
	cin >> naz;
	Student temp;
	while (1){
		wczytajStudenta(plik, temp);
		if (plik.eof())break;
		if (temp.nazwisko == naz)
			wypisz_studenta(temp);
	}
	plik.close();
}
void wypisz_projekty(){
	system("cls");
	fstream stud(DANE_OS, ios::in);
	fstream proj(PROJEKTY, ios::in);
	if (!stud.good() && !proj.good()){
		cout << "Nie mozna otworzyc plikow" << endl;
		return;
	}
	Student st;
	Projekt pj;
	int ind;
	cout << "Podaj indeks studenta" << endl;
	cin >> ind;
	bool S_znal = false, P_znal = false;
	while (1){
		wczytajStudenta(stud,st );
		if (stud.eof())break;
		if (st.index == ind){
			S_znal = true;
			break;
		}
	}
	if (S_znal){
		while (1){
			wczytajProjekt(proj, pj);
			if (proj.eof())break;
			if (pj.ktoryStudent == st.index){
				P_znal = true;
				wypisz_projekt(pj, st);
			}
		}
	}
	else{
		cout << "Nie znaleziono studenta" << endl;
		return;
	}
	if (!P_znal){
		cout << "Nie znaleziono projektu" << endl;
		return;
	}
	
}
void wypisz_stud_komentarze(){
	system("cls");
	fstream stud(DANE_OS, ios::in);
	fstream kom(KOMENT, ios::in);
	if (!stud.good() && !kom.good()){
		cout << "Nie mozna otworzyc plikow" << endl;
		return;
	}
	Student st;
	Komentarz km;
	int ind;
	cout << "Podaj indeks studenta" << endl;
	cin >> ind;
	bool S_znal = false, K_znal = false;
	while (1){
		wczytajStudenta(stud, st);
		if (stud.eof())break;
		if (st.index == ind){
			S_znal = true;
			break;
		}
	}
	if (S_znal){
		while (1){
			wczytajKom(kom, km);
			if (kom.eof())break;
			if (km.cel == st.index){
				K_znal = true;
				wypisz_kom_stud(km, st);
			}
		}
	}
	else{
		cout << "Nie znaleziono studenta" << endl;
		return;
	}
	if (!K_znal){
		cout << "Nie znaleziono komentarzy" << endl;
		return;
	}

}
void wypisz_proj_komentarze(){
	system("cls");
	fstream proj(PROJEKTY, ios::in);
	fstream kom(KOMENT, ios::in);
	if (!proj.good() && !kom.good()){
		cout << "Nie mozna otworzyc plikow" << endl;
		return;
	}
	Projekt pr;
	Komentarz km;
	int nr;
	cout << "Podaj numer projektu" << endl;
	cin >> nr;
	bool P_znal = false, K_znal = false;
	while (1){
		wczytajProjekt(proj, pr);
		if (proj.eof())break;
		if (pr.nr_projektu == nr){
			P_znal = true;
			break;
		}
	}
	if (P_znal){
		while (1){
			wczytajKom(kom, km);
			if (kom.eof())break;
			if (km.cel == pr.nr_projektu){
				K_znal = true;
				wypisz_kom_proj(km, pr);
			}
		}
	}
	else{
		cout << "Nie znaleziono projektu" << endl;
		return;
	}
	if (!K_znal){
		cout << "Nie znaleziono komentarzy" << endl;
		return;
	}

}
void input(bool &program){
	int button;
	cin >> button;
	if (!cin) 
	{
		cin.clear(); 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
	}
	switch (button){
	case 1:
		studenci();
			break;
	case 2:
		projekty();
		break;
	case 3:
		komentarze();
		break;
	case 4:
		system("cls");
		wypisz_studentow();
		break;
	case 5:
		szukaj_stud_ind();
		break;
	case 6:
		szukaj_stud_naz();
		break;
	case 7:
		wypisz_projekty();
		break;
	case 8:
		wypisz_stud_komentarze();
		break;
	case 9:
		wypisz_proj_komentarze();
		break;
	case 10: 
		program = false;
		return;
	default:
		cin >> button;
	}
}

void menu(bool &program){
	cout << "-----------Baza danych-----------" << endl;
	cout <<"1.Studenci"<< endl;
	cout <<"2.Projekty"<< endl;
	cout <<"3.Komentarze"<< endl;
	cout <<"4.Wypisz studentow"<< endl;
	cout << "5.Szukaj studentow-index" << endl;
	cout << "6.Szukaj studentow-nazwisko" << endl;
	cout << "7.Wypisz projekty studenta" << endl;
	cout << "8.Wypisz komentarze do studenta" << endl;
	cout << "9.Wypisz komentarze do projektu" << endl;
	cout << "10.Wyjdz" << endl;
	input(program);
}

int main() {

	bool program = true;
	int wybor;
		while (program) {
			menu(program);
	}
}