#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<locale>
using namespace std;

class Personne {
	int Id;
	string nom;
public:
	void saisie();
	void saisienom();
	void afficher();
	int operator==(Personne);
};

void Personne::saisie() {
	bool test;
	do {
		test = false;
		cout << "Id:";
		cin >> Id;
		if (cin.fail()) {
			test = true;
			cin.clear();
			cin.ignore();
			cout << "Entrer un entier!" << endl;
		}
	} while (test == true);
	cout << "nom:";
	cin.ignore();
	getline(cin,nom);
}

void Personne::saisienom() {
	cout << "nom:";
	cin.ignore();
	getline(cin, nom);
}

void Personne::afficher() {
	cout << setw(10) << "\nId:" << Id << setw(10) << "nom:" << nom;
}

int Personne::operator==(Personne P) {
	if (nom == P.nom) return 1;
	else return 0;
}

class Etudiant : public Personne {
	int Note[3];
public:
	friend class Direction;
	void saisie();
	void afficher();
};

void Etudiant::saisie() {
	int i = 0;
	Personne::saisie();
	do {	//faire avec vector???
		cout << "Note[" << i << "]:";
		cin >> Note[i];
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Entrer un entier!" << endl;
		}
		else i++;
	} while (i<3);
}

void Etudiant::afficher() {
	Personne::afficher();
	for (int i = 0; i < 3; i++) {
		cout << setw(10) << "Note[" << i << "]:" << Note[i];
	}
}

class Prof : public Personne {
	string service;
public:
	void saisie();
	void afficher();
};

void Prof::saisie() {
	Personne::saisie();
	cout << "service:";
	getline(cin, service);
}

void Prof::afficher() {
	Personne::afficher();
	cout << setw(10) << "service:" << service;
}

class Direction : public Prof {
	string titre;
public:
	void saisie();
	void afficher();
	void moyenne(list<Etudiant>);
};

void Direction::saisie() {
	cout << "\ntitre:";
	cin.ignore();
	getline(cin, titre);
}

void Direction::afficher() {
	cout << setw(10) << "\n" << titre<<" calcule la moyenne des étudiants!"<<endl;
}

void Direction::moyenne(list<Etudiant> EE) {
	int i = 0;
	float moy;
	list<Etudiant>::iterator it;
	for (it = EE.begin(); it != EE.end(); it++,i++) {
		moy = (float)(it->Note[0] + it->Note[1] + it->Note[2]) / 3;
		cout << "Moyenne E["<<i<<"]:" << moy<<endl;
	}
}

void menu(int &);
template <class T, class U, class V> void saisieLV(T &); //case 1+2
template <class T, class U> void printLV(T, U, string); //case 1+2
template <class T, class U> void printLV(T, string); //case 1+2 // avec U en local
template <class T, class U> void effacerLV(T &); //case 3
void moyenne(list<Etudiant>); //case 4
template <class T, class U, class V> void chercherLV(T); //case 5

int main() {
	setlocale(LC_ALL, "");

	int choix,choixEP;
	bool testEP = false,testE=false, testP=false;
	list<Etudiant> E;
	vector<Prof> P;
	list<Etudiant>::iterator itl;
	vector<Prof>::iterator itv;

	do {
		menu(choix);
		switch (choix) {
		case 1:
			saisieLV<list<Etudiant>, Etudiant, list<Etudiant>::iterator>(E);
			//printLV<list<Etudiant>, list<Etudiant>::iterator>(E, itl, "Etudiant:");
			printLV<list<Etudiant>, list<Etudiant>::iterator>(E, "Etudiant:");
			testE = true;
			break;
		case 2:
			saisieLV<vector<Prof>, Prof, vector<Prof>::iterator>(P);
			printLV<vector<Prof>, vector<Prof>::iterator>(P, itv, "Prof:");
			testP = true;
			break;
		case 3:
			cout << endl;
			do {
				cout << "Effacer Etudiant(1) ou Prof(2)?:";
				do {
					testEP = false;
					cin >> choixEP;
					if (cin.fail()) {
						testEP = true;
						cin.clear();
						cin.ignore();
						cout << "Choisir entre 1 et 2!" << endl;
					}
				} while (testEP == true);
			} while ((choixEP < 1) || (choixEP > 2));
			if (choixEP == 1) {
				if (testE == false) {
					saisieLV<list<Etudiant>, Etudiant, list<Etudiant>::iterator>(E);
					printLV<list<Etudiant>, list<Etudiant>::iterator>(E, itl, "Etudiant:");
					testE = true;
				}
				effacerLV<list<Etudiant>, list<Etudiant>::iterator>(E);
				printLV<list<Etudiant>, list<Etudiant>::iterator>(E, itl, "Etudiant:");
				if (E.empty()) {
					cout << "C'est vide"<<endl;
				}
			}
			else {
				if (testP == false) {
					saisieLV<vector<Prof>, Prof, vector<Prof>::iterator>(P);
					printLV<vector<Prof>, vector<Prof>::iterator>(P, itv, "Prof:");
					testP = true;
				}
				effacerLV<vector<Prof>, vector<Prof>::iterator>(P);
				printLV<vector<Prof>, vector<Prof>::iterator>(P, itv, "Prof:");
				if (P.empty()) {
					cout << "C'est vide" << endl;
				}
			}
			break;
		case 4:
			if (testE == false) {
				saisieLV<list<Etudiant>, Etudiant, list<Etudiant>::iterator>(E);
				printLV<list<Etudiant>, list<Etudiant>::iterator>(E, itl, "Etudiant:");
				testE = true;
			}
			moyenne(E);
			break;
		case 5:
			cout << endl;
			do {
				cout << "Chercher Etudiant(1) ou Prof(2)?:";
				do {
					testEP = false;
					cin >> choixEP;
					if (cin.fail()) {
						testEP = true;
						cin.clear();
						cin.ignore();
						cout << "Choisir entre 1 et 2!" << endl;
					}
				} while (testEP == true);
			} while ((choixEP < 1) || (choixEP > 2));
			if (choixEP == 1) {
				if (testE == false) {
					saisieLV<list<Etudiant>, Etudiant, list<Etudiant>::iterator>(E);
					printLV<list<Etudiant>, list<Etudiant>::iterator>(E, itl, "Etudiant:");
					testE = true;
				}
				chercherLV<list<Etudiant>, Etudiant, list<Etudiant>::iterator>(E);
			}
			else {
				if (testP == false) {
					saisieLV<vector<Prof>, Prof, vector<Prof>::iterator>(P);
					printLV<vector<Prof>, vector<Prof>::iterator>(P, itv, "Prof:");
					testP = true;
				}
				chercherLV<vector<Prof>, Prof, vector<Prof>::iterator>(P);
			}
			break;
		case 6:
			break;
		case 7:
			E.clear();
			P.clear();
			testE = false, 
			testP = false;
			cout << "Effacé!"<<endl;
			break;
		default:
			cout << "\nFaire un choix entre 1 et 6!" << endl;
		}
	} while (choix != 6);
	//cout << "Hello" << endl;
	//system("pause");
	return 0;
}

void menu(int &choix1) {
	bool test;
	do {
		test = false;
		cout << "\nFaites un choix dans le menu";
		cout << "\n1_Saisie et/ou ajouts étudiants et affichage";
		cout << "\n2_Saisie et/ou ajout profs et affichage";
		cout << "\n3_Supprimer un étudiant ou un prof à la position P";
		cout << "\n4_Doyen membre de direction calcule la moyenne de chaque étudiant et affichage";
		cout << "\n5_Chercher un étudiant ou un prof selon le nom";
		cout << "\n6_Quitter";
		cout << "\n7_Effacer list ou vector" << endl;
		cin >> choix1;
		if (cin.fail()) {
			test = true;
			cin.clear();
			cin.ignore();
			cout << "\nChoisir un entier entre 1 et 6!"<<endl;
		}
	} while (test == true);
}

template <class T, class U, class V> void saisieLV(T &LV) { //case 1+2
	U temp;
	V it;
	it = LV.begin();
	for (int i = 0; i < LV.size() / 2; i++) {
		it++;
	}
	int taille;
	if (LV.empty()) {
		cout << endl;
		do {
			cout << "Combien d'élément(s)?:";
			cin >> taille;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\nChoisir un entier >0!" << endl;
			}
		} while (taille <= 0);
		for (int i = 0; i < taille; i++) {
			cout << "\n[" << i << "]" << endl;
			temp.saisie();
			LV.push_back(temp);
		}
	}
	else {
		cout << "\nNouvel élément:" << endl;
		temp.saisie();
		LV.push_back(temp); //insère au début
		//LV.insert(LV.end(), temp); //insère à la fin
		//LV.insert(LV.begin(), temp); //insère au début
		//LV.insert(it, temp); //insère à la position it
	}
}

template <class T, class U> void printLV(T LV, U itlv, string S) { //case 1+2
	cout << endl<<S;
	for (itlv = LV.begin(); itlv != LV.end(); itlv++) {
		itlv->afficher();
	}
	cout << endl;
}

template <class T, class U> void printLV(T LV, string S) { //case 1+2 //template avec U en local
	U it;
	cout << endl << S;
	for (it = LV.begin(); it != LV.end(); it++) {
		it->afficher();
	}
	cout << endl;
}

template <class T, class U> void effacerLV(T &LV) { //case 3
	bool test = false;
	int pos;
	U it = LV.begin();
	cout << endl;
	do {
		do {
			cout << "A quelle position effacer?:";
			cin >> pos;
			if (cin.fail()) {
				test = true;
				cin.clear();
				cin.ignore();
				cout << "\nChoisir un entier < " << LV.size() << "!" << endl;
			}
		} while (test == true);
	} while ((pos < 0) || (pos >= LV.size()));
	for (int i = 0; i < pos; i++) {
		it++;
	}
	LV.erase(it);
}

void moyenne(list<Etudiant> list) { //case 4
	Direction D;
	D.saisie();
	D.afficher();
	D.moyenne(list);
}

template <class T, class U, class V> void chercherLV(T LV) { //case 5
	U temp;
	V it;
	cout << "\nQui rechercher?:" << endl;
	temp.saisienom();
	it = find(LV.begin(), LV.end(), temp);
	if (it != LV.end()) {
		cout << "\nElément trouver"<<endl;
	}
	else {
		cout << "\nElément inexistant"<<endl;
	}
}