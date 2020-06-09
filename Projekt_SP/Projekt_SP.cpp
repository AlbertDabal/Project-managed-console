#include "pch.h"
#include <iostream>
#include "string"
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <io.h>
#include<stdio.h>



using namespace std;



//https://www.highlite.com/en/products/cables-connectors/powerdistribution/240v-extensioncords.html

//SMD1 wymiary 0,5m x 0,5m  //sygnal 15 kostek
//SMD2 wymiary 0,5m x 0,5m 
//SMD3 wymiary 0,5m x 0,5m 
//SMD4 wymiary 1m x 0,5m

//**************************************************************

//ustawia maxymalny rozmiar konsoli

//POBOR PRADU
//>>SMD1<<
//Średnie: 320W / m² Max : 740W / m² https://ledsee.pl/ekran-led-391-zew-standard
//>>SMD2<<
//Średnie: 200W/m² Max: 600W/m² https://ledsee.pl/ekran-led-481-standard
//>>SMD3<<
//Średnie: 140W / m² Max : 420W / m² https://ledsee.pl/ekran-led-p6
//>>SMD4<<
//Średnie: 400W / m² Max : 1200W / m² https://ledsee.pl/ekran-led-p6

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);




int Menu() {
	
	//wygląd konsoli 
	
	
	COORD size;

	size.X = 300;
	size.Y = 200;

	SetConsoleScreenBufferSize(hConsole, size);
	HWND uchwytKonsoli = GetConsoleWindow();
	MoveWindow(uchwytKonsoli, 0, 0, 1600, 1000, TRUE);
	
	
	int wybor;

	cout << "<<<<<<<<<<<<<<WITAJ W PROGRAMIE DO OBSLUGI DIODY NA EVENTACH>>>>>>>>>>>>>>" << endl;


	cout << "<<STWORZ EVENT<<[0]>>"<<endl;

	cout << "<<MAGAZYN<<[1]>>"<<endl;

	cout << "<<ZNAJDZ PRZEDMIOT<<[2]>>"<<endl;

	cout << "<<AKTUALNE EVENTY<<[3]>>" << endl;

	cout << "<<USUN EVENT<<[4]>>" << endl;
	
	cin >> wybor;
	system("cls");

	return wybor;
}



struct dioda {
	int id_dioda;
	string nazwa;
	double szerokosc;
	double wysokosc;
	double pobor;    //pobor prądu średni
	double maxpobor;  //pobor prądu maxymalny 

};

double Pobor_produ(double pole,double pobor,double maxpobor) {
	pobor = pole * pobor;
	
	maxpobor = pole * maxpobor;
	
	cout <<"SREDNI POBOR TO:"<< pobor<<"W"<<endl;

	cout <<"MAX POBOR TO:"<< maxpobor <<"W"<< endl;

	
	return maxpobor;

}


//zasilanie dla diody SMD3/4

double Pobor_produ_big(int pole, double pobor, double maxpobor, double pobor2, double maxpobor2) {
	pobor = pole * pobor;
	pobor2 = pole * pobor2;

	maxpobor = pole * maxpobor;
	maxpobor2 = pole * maxpobor2;

	cout << "SREDNI POBOR DLA DIODY SMD3:" << pobor << "W" << endl;
	cout << "SREDNI POBOR DLA DIODY SMD4:" << pobor2 << "W" << endl;
	cout << "MAX POBOR DLA DIODY SMD3 TO :" << maxpobor << "W" << endl;
	cout << "MAX POBOR DLA DIODY SMD4 TO:" << maxpobor2 << "W" << endl;

	maxpobor = maxpobor + maxpobor2;

	return maxpobor;




	

}



double Wymiardiody(double wymiar, double wysokosc)
{
	for (int g=1; g < wymiar; g++)
	{
		
		wysokosc++;
	}
	cout << wysokosc;
	int a = 0;
	if (wysokosc > wymiar)
	{
		a = 1;
	}
	return a;


	//dokończyć skrypt który liczy diodę wiemy kiedy już trzeba użyć dwóch
}

void newtekst() {
	
	SetConsoleTextAttribute(hConsole, 151);
	
}

void oldtekst() {
	SetConsoleTextAttribute(hConsole, 15);
}


void Pliki() {

	_finddata_t danePliku;
	long uchwyt = _findfirst("./eventy/*.txt", &danePliku);
	string nazwa_pliku;
	int dlugosc_plik;
	int kolejnosc = 1;

	for (int i_1 = 0; !i_1; i_1 = _findnext(uchwyt, &danePliku))
	{
		nazwa_pliku = danePliku.name;


		dlugosc_plik = nazwa_pliku.length();

		nazwa_pliku.erase(dlugosc_plik - 4);

		cout << "[" << kolejnosc << "]" << nazwa_pliku << endl;
		kolejnosc++;
		cout << endl;
	}
	_findclose(uchwyt);
}


int main()
{
	
		int zakoncz;
		

		do {
			system("cls");
			int wybor = Menu();

			if (wybor == 0)

			{
				dioda smd[5];

				smd[1] = { 1,"SMD1",0.5,0.5,320,740 };

				smd[2] = { 2,"SMD2",0.5,0.5,200,600 };

				smd[3] = { 3,"SMD3",0.5,0.5,140,420 };

				smd[4] = { 4,"SMD4",0.5,1,400,1200 };

				double wymiar[2];
				int rodzaj;
				string event;



				cout << "Podaj nazwe eventu: ";
				cin >> event;

				cout << "Wybierz rodzaj diody ktory chcesz urzywac na event\nSMD1[0]\nSMD2[1]\nSMD3/4[2]";

				cin >> rodzaj;
				cout << "Jaki rozmiar ma dioda" << endl;

				cout << "podaj szerokosc w metrach" << endl;
				cin >> wymiar[0];

				cout << "podaj wysokosc w metrach" << endl;
				cin >> wymiar[1];

				cout << endl;

				//przypisanie wielkosci do do diody		


				double potrzeba;
				double wielkosc;
				double pole;


				switch (rodzaj)
				{
				case 0:

					pole = wymiar[0] * wymiar[1];

					cout << smd[1].nazwa << endl;


					wymiar[0] = wymiar[0] / smd[1].szerokosc;
					wymiar[1] = wymiar[1] / smd[1].wysokosc;

					cout << "ilosc kabinetow: " << wymiar[0] * wymiar[1];

					break;

				case 1:
					pole = wymiar[0] * wymiar[1];

					cout << smd[2].nazwa << endl;

					wymiar[0] = wymiar[0] / smd[2].szerokosc;
					wymiar[1] = wymiar[1] / smd[2].wysokosc;

					cout << "ilosc kabinetow: " << wymiar[0] * wymiar[1];



					break;

				case 2:
					cout << "SMD3/4" << endl;
					potrzeba = Wymiardiody(wymiar[1], smd[4].wysokosc);
					pole = wymiar[0] * wymiar[1];

					wymiar[0] = wymiar[0] / smd[3].szerokosc;


					if (potrzeba == 1)
					{


						wielkosc = smd[3].wysokosc;

						wymiar[1] = wymiar[1] - smd[3].wysokosc;

						wymiar[1] = wymiar[1] / smd[4].wysokosc;

						cout << "ilosc kabinetow SMD3: " << wymiar[0] << endl;

					}

					cout << "ilosc kabinetow SMD4: " << wymiar[0] * wymiar[1] << endl;

					break;

				default:
					cout << "nie wybrales diody dostepnej w firmie";
					break;
				}

				int kabinet = 0;
				int smallkabinet = 0;

				if (rodzaj == 1 || rodzaj == 0)
				{


					cout << endl;
					for (int i = 0; i < wymiar[1]; i++)
					{
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							kabinet++;
							newtekst();
							if (kabinet >= 10 && kabinet <= 99)
								cout << " " << kabinet << "  ";
							else if (kabinet >= 100)
								cout << " " << kabinet << " ";
							else
								cout << "  " << kabinet << "  ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}

						cout << endl;
					}
				}

				else
				{



					if (potrzeba == 1)
					{
						cout << endl;

						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							kabinet++;
							smallkabinet++;
							newtekst();
							if (kabinet >= 10 && kabinet <= 99)
								cout << " " << kabinet << "  ";
							else if (kabinet >= 100)
								cout << " " << kabinet << " ";
							else
								cout << "  " << kabinet << "  ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}

						cout << endl;

					}


					for (int i = 0; i < wymiar[1]; i++)
					{
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();

							cout << "     ";
							oldtekst();

							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							kabinet++;
							newtekst();
							if (kabinet >= 10 && kabinet <= 99)
								cout << " " << kabinet << "  ";
							else if (kabinet >= 100)
								cout << " " << kabinet << " ";
							else
								cout << "  " << kabinet << "  ";
							oldtekst();
							cout << " ";
						}
						cout << endl;
						for (int x = 0; x < wymiar[0]; x++)
						{
							cout << " ";
							newtekst();
							cout << "     ";
							oldtekst();
							cout << " ";
						}

						cout << endl;
					}



				}



				//>>>>ZAPOTRZEBOWANIE PRĄDU

				double maxpobory;

				if (rodzaj == 2)
				{
					if (potrzeba == 1)
					{

						maxpobory = Pobor_produ_big(pole, smd[rodzaj + 1].pobor, smd[rodzaj + 1].maxpobor, smd[rodzaj + 2].pobor, smd[rodzaj + 2].maxpobor);
					}
					else
					{

						maxpobory = Pobor_produ(pole, smd[rodzaj + 2].pobor, smd[rodzaj + 2].maxpobor);

					}
				}
				else
				{

					maxpobory = Pobor_produ(pole, smd[rodzaj + 1].pobor, smd[rodzaj + 1].maxpobor);
				}


				//ilosc pionu 32A

				int pion = 0;
				double kwpobor = maxpobory / 1000;
				do {
					pion++;
					kwpobor = kwpobor - 21;

				} while (kwpobor > 21);

				cout << "Ilosc pionow:" << pion << "x32 A" << endl;

				int ilosc_powercon = 0;
				double powercon = maxpobory / 3680;

				do
				{
					ilosc_powercon++;
					powercon--;
				} while (powercon > 1);

				cout << "Ilosc zasilan PC:" << ilosc_powercon << endl;

				double pc = ((kabinet * 2) - ilosc_powercon) - 1;

				int rj45 = 0;



				//jedna rj45 moze byc na 15 kabinetow

				for (int t=0; t<kabinet ;t=t+15)
				{
					rj45++;
				}

				int etercon;
				etercon = ((kabinet * 2) - rj45)-1;

				




				ofstream mojStrumien("./eventy/" + event + ".txt");


				if (mojStrumien)
				{
					if (rodzaj == 2)
					{
						if (potrzeba == 1)
						{
							mojStrumien << smd[rodzaj + 1].nazwa << "	" << smallkabinet << endl;
							mojStrumien << smd[rodzaj + 2].nazwa << "	" << kabinet << endl;
						}
						else
						{
							mojStrumien << smd[rodzaj + 2].nazwa << "	" << kabinet << endl;
						}
					}
					else
					{
						mojStrumien << smd[rodzaj + 1].nazwa << "	" << kabinet << endl;
					}



					mojStrumien << "pion" << "	" << pion << endl;
					mojStrumien << "pc230v" << "	" << ilosc_powercon << endl;
					mojStrumien << "pc" << "	" << pc << endl;
					mojStrumien << "etercon" << "	" << etercon << endl;
					mojStrumien << "rozdzielnia" << "	" << pion << endl;
					mojStrumien << "rj45" << "	" << rj45 << endl;
				}
				else
				{
					cout << "BŁĄD: nie można otworzyć pliku." << endl;
				}

				mojStrumien.close();


			}



			else if (wybor == 1)
			{
				cout << "<<<<<<<<<WITAJ NA MAGAZYNIE>>>>>>>>>>" << endl<<endl;
	
				cout << "NAZWA\tILOSC"<<endl;
				//OTWIERANIE PLIKU MAGAZYN

				ifstream mojStrumien("magazyn.txt");

				if (mojStrumien)
				{
				
					int m = 0;
					int p = 0;
					string slowo[9999];
					double liczba[9999];

				//PRZYPIDANIE WARTOSCI Z PLIKU ZMIENNYM

					while (mojStrumien >> slowo[m])
					{
						m++;
						mojStrumien >> liczba[p];
						p++;

					}
				
					for (int n = 0; n < m; n++)
					{
						cout << slowo[n];
						cout <<"\t";
						cout << liczba[n]<<endl;
					}
					
				
				}
				else
				{
					cout << "BŁAD nie otwarto pliku" << endl;
				}

				mojStrumien.close();
			
			}
			else if (wybor == 2)
			{
				string wyszukaj;

				cout << "Witaj w wyszkiwaniu podaj nazwe przedmiotu ktorego szukasz"<<endl;
				cin >> wyszukaj;

				ifstream mojStrumien("magazyn.txt");

				if (mojStrumien)
				{
					int a = 0;
					string wyszukaj_ilosc;
					double ilosc;
					
					while (mojStrumien >> wyszukaj_ilosc)
					{
						if (wyszukaj_ilosc == wyszukaj)
						{
							cout << "Znaleziono przedmiot na magazynie jego ilosc to:";
							mojStrumien >> ilosc;
							cout << ilosc << endl;
							a = 1;
							break;
						}
					}
					if (a == 0)
						cout << "Nie ma przedmiotu na magazynie";
				}
				
				mojStrumien.close();
			}

			else if(wybor==3)
			{
				cout << "AKTUALNE EVENTY"<<endl;
				
				cout << endl;

				Pliki();
				
				

				
			
			}

			else if (wybor == 4) {

				cout << "USUWANIE EVENTU" << endl;

				cout << "Aktualne eventy" << endl;
				cout << endl;
				Pliki();

				cout << "Wpisz nazwe eventu ktory chcesz usunac" << endl;
				char tab[6];
				
				cin >> tab;
				
				
				
	
				char filename[] = "eventy/";
				char txtname[] = ".txt";
				char nowa[99];
				
				for (int g = 0; g < 7; g++)
				{
					nowa[g] = filename[g];
					cout << nowa[g];
				}
				int g = 7;
				for (int c = 0; c < sizeof(tab); c++)
				{
					
					nowa[g] = tab[c];
					cout << nowa[g];
					g++;
				}
				g = 7 + sizeof(tab);
				for (int b = 0; b < 4; b++)
				{
					g++;
					nowa[g] = txtname[b];
					cout << nowa[g];
					g++;
				}
				
				for (int b = 0; b < sizeof(nowa); b++)
				{
					
					
					cout << nowa[b];
					
				}
					
			const int result = remove(nowa);
				

			}

			cout << endl;
			cout << "Czy chcesz powrucic do menu glownego 1/tak 0/nie:";

			cin >> zakoncz;
		

		}while(zakoncz==1);



	return 0;
}

