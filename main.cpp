#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>

using namespace std;

struct Patobulinimas
{
    float gyvybes;
    float atakos;
    float apsauga;
};

struct Inventorius
{
    string pavadinimas;
    int gyvybes;
    int apsauga;
    int ataka;
};

struct Pokemonas
{
    string vardas;
    int gyvybes;
    int apsauga;
    int ataka;
    void PridetiInventoriu(Inventorius naujasInventorius);
    void Kovoti(Pokemonas pokemonas);
    void Aktyvuoti(Patobulinimas patobulinimas);
    void InicijuotiPokemona(string vardas, int gyvybes, int apsauga, int ataka);
    void Isspausdinimas();
    int GyvybeIrApsauga();
private:
    int pradinesGyvybes;
    int pradineApsauga;
    int pradineAtaka;

    Inventorius inventorius[100];
    Patobulinimas patobulinimas[100];
    int uzimtaInventoriaus=0;
    int patobulinta = 0;

    void GaliosPerskaiciavimas();

};

int main()
{
    Pokemonas pokemonas;
    Patobulinimas patobulinimas;
    Inventorius inventorius;
    inventorius.pavadinimas = "pavadinimas";
    inventorius.ataka = 100;
    inventorius.gyvybes = 50;
    inventorius.apsauga = 100;
    patobulinimas.atakos = 1.25;
    patobulinimas.apsauga = 1.5;
    patobulinimas.gyvybes = 2;
    pokemonas.InicijuotiPokemona("Pikachu", 100, 500, 100);

    pokemonas.Isspausdinimas();
    pokemonas.PridetiInventoriu(inventorius);
    pokemonas.Isspausdinimas();
    pokemonas.Aktyvuoti(patobulinimas);
    pokemonas.Isspausdinimas();


    Pokemonas pokemonas2;
    pokemonas2.InicijuotiPokemona("Charmanderis", 150, 250, 120);
    pokemonas2.PridetiInventoriu(inventorius);
    pokemonas2.PridetiInventoriu(inventorius);
    pokemonas2.PridetiInventoriu(inventorius);
    pokemonas.Kovoti(pokemonas2);
}

void Pokemonas::Isspausdinimas()
{
    cout << vardas << endl;
    cout << gyvybes << " " << "/" << " " << apsauga << " " << " /" << " " << ataka << " " << "/" << endl;
}

void Pokemonas::InicijuotiPokemona(string inVardas, int inGyvybes, int inApsauga, int inAtaka)
{
    this->vardas = inVardas;
    gyvybes = this->pradinesGyvybes =  inGyvybes;
    apsauga = this->pradineApsauga = inApsauga;
    ataka = this ->pradineAtaka = inAtaka;
}

void Pokemonas::PridetiInventoriu(Inventorius naujasInventorius)
{
    inventorius[uzimtaInventoriaus++]=naujasInventorius;
    GaliosPerskaiciavimas();
}

void Pokemonas::GaliosPerskaiciavimas()
{
    gyvybes = pradinesGyvybes;
    ataka = pradineAtaka;
    apsauga = pradineApsauga;
    for(int i=0; i<uzimtaInventoriaus; i++)
    {
        gyvybes += inventorius[i].gyvybes;
        ataka += inventorius[i].ataka;
        apsauga += inventorius[i].apsauga;
    }
    for(int i=0; i<patobulinta; i++)
    {
        gyvybes *= patobulinimas[i].gyvybes;
        ataka *= patobulinimas[i].atakos;
        apsauga *= patobulinimas[i].apsauga;
    }
}

void Pokemonas::Aktyvuoti(Patobulinimas patobulinimas)
{
    this->patobulinimas[patobulinta++]=patobulinimas;
    GaliosPerskaiciavimas();
}

int Pokemonas::GyvybeIrApsauga()
{
    return gyvybes+apsauga;
}

void Pokemonas::Kovoti(Pokemonas pokemonas)
{
    int suma = GyvybeIrApsauga();
    int priesininkoSuma = pokemonas.GyvybeIrApsauga();
    bool priesininkoAtaka = false;
    while(suma>0 && priesininkoSuma >0)
    {
        if(priesininkoAtaka==true)
        {
            suma-=pokemonas.ataka;
            cout << "Atakuoja " << pokemonas.vardas << " " << pokemonas.ataka << endl;
        }
        else
        {
            priesininkoSuma -= ataka;
            cout << "Atakuoja " << vardas << " " << ataka << endl;
        }
        priesininkoAtaka=!priesininkoAtaka;
        Sleep(2000);
    }
    if(priesininkoSuma<suma)
    {
        cout << "Laimejo " << vardas << endl;
    }
    else cout << "Laimejo " << pokemonas.vardas << endl;
}
