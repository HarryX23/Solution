//Semestrální práce
//Petr Olša, OLS0041

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//struktura pro film
typedef struct
{
    int id;
    string nazev;
    int rok;
    string zanr;
    string puvod;
    int delka;
    vector<int> id_hercu;
} Film;

//struktura pro herce
typedef struct
{
    int id;
    string jmeno;
    string prijmeni;
    string datum_nar;
    string misto_nar;
    vector<int> id_filmu;

} Herec;

//deklarace funkcí pro všechny typy výpisů
void Vypis_All(vector<Film> &filmy);
void Vypis_Zanr(vector<Film> &filmy);
void Vypis_Rok(vector<Film> &filmy);
void Vypis_film_volba(vector<Film> &filmy, vector<Herec> &herci);
void Vypis_herec_volba(vector<Film> &filmy, vector<Herec> &herci);

int main()
{
    //jednotlivé vektory pro naplnění filmy a herci
    vector<Film> filmy;
    vector<Herec> herci;

    //znak oddělovače
    const char oddelovac = ';';

    //Načtení CSV souboru s filmy
    ifstream Movies_input("../vstupnidata/Movies.csv");

    //ověření otevření souboru
    if(Movies_input.is_open())
    {
        cout<<"Soubor s filmy byl uspesne otevren"<<endl;

        //proměné na řádky a pomocné pole pro ukládaní dat
        string line;
        string pom_pole[6];

        //procházení jedntlivých řádků souboru
        while (getline(Movies_input, line))
        {

            //procházení dat na řádku, ukládání do pomocného pole a postupné přesouvání na další data
            //data jsou oddělena středníkem, proto se přesouvám od středníku ke středníku
            //dokud nenarazím na znak odentrování a poté se while bude opakovat o řádek níže
            //celý proces končí jakmile proběhne tento proces na posledním řádku souboru
            stringstream ss(line);
            for(int i = 0; i < 6; i++)
                getline(ss, pom_pole[i], oddelovac);
            Film film;
            film.id = atoi(pom_pole[0].c_str());
            film.nazev = pom_pole[1];
            film.rok = atoi(pom_pole[2].c_str());
            film.zanr = pom_pole[3];
            film.puvod= pom_pole[4];
            film.delka = atoi(pom_pole[5].c_str());
            int id_herce;
            char skip;
            while(ss>> id_herce)
            {
                film.id_hercu.push_back(id_herce);
                ss >> skip;
            }
            //uložení dat pole do dat vectoru struktury
            filmy.push_back(film);
        }
        //uzavření souboru
        Movies_input.close();
    }
    else
    {
        cout<<"Soubor s filmy nebyl otevren!"<<endl;
    }


     //postup je stejný jako se soer s filmy, jenom se mění soubor, jinak je vše stejné
    ifstream Actors_input("../vstupnidata/Herci.csv");
    if(Actors_input.is_open())
    {
        cout<<"Soubor s herci byl uspesne otevren"<<endl;
        string line;
        string pom_pole[5];

        while (getline (Actors_input, line))
        {
            stringstream ss(line);
            for(int i = 0; i < 5; i++)
                getline(ss, pom_pole[i], oddelovac);
            Herec herec;
            herec.id = atoi(pom_pole[0].c_str());
            herec.jmeno= pom_pole[1];
            herec.prijmeni = pom_pole[2];
            herec.datum_nar = pom_pole[3];
            herec.misto_nar = pom_pole[4];

            int id_filmu;
            char skip;
            while(ss>> id_filmu)
            {
                herec.id_filmu.push_back(id_filmu);
                ss >> skip;
            }

            herci.push_back(herec);
        }
        Actors_input.close();
    }
    else
    {
        cout<<"Soubor s herci nebyl otevren!"<<endl;
    }


    //nabídka možností, které je program schopen provést
    int volba;
    do
    {
        cout<<"---------------------- Nabidka moznosti: ----------------------"<<endl;
        cout<<"1 - Vypsat filmy"<<endl;
        cout<<"2 - Vypsat filmy urciteho zanru"<<endl;
        cout<<"3 - Vypsat filmy natocene v urcitych letech (interval od - do)"<<endl;
        cout<<"4 - Vypsat informace o filmy po zadani ID nebo nazvu filmu"<<endl;
        cout<<"5 - Vypsat informace o herci po zadani ID nebo jmena herce"<<endl;
        cout<<"0 - Ukonceni programu"<<endl;
        cout<<"----------------------------------------------------------------"<<endl;
        cout<<"Vase volba: ";
        cin >> volba;
        cout<<endl;

        //switch rozlišující volbu, která byla zvolena a tím zavolání příslušné funkce
        switch(volba)
        {
        case 1:
            Vypis_All(filmy);
            break;

        case 2:
            Vypis_Zanr(filmy);
            break;

        case 3:
            Vypis_Rok(filmy);
            break;

        case 4:
            Vypis_film_volba(filmy, herci);
            break;

        case 5:
            Vypis_herec_volba(filmy,herci);
            break;

        case 0:
            return 0;
        break;

        default:
            cout<<"Nespravna volba!"<<endl;
        }
    }
    while(volba !=0);
    return 0;
}

//funkce pro výpis všech filmů
void Vypis_All(vector<Film> &filmy)
{

    cout<<"Nazev filmu"<<endl;
    cout<<"------------"<<endl;

    //prochzeních všech filmů uložeých ve struktuře a jejích postupný výpis
    for(unsigned int i = 0; i<filmy.size(); i++)
    {
        cout<<filmy[i].nazev<<endl;
    }
      cout<<endl;
    //dotaz zda mají být data uloženy do HTML souboru

    cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
    string volba;
    cin >> volba;
    if(volba == "ano")
    {
        //otevření výstupního souboru a ložení dat do něj
        ofstream output("../vystupnidata/Vypis_filmu.html");
        output<<"<p>";
        output<<"<b>Nazev filmu</b><br>"<< endl;

        for(unsigned int i = 0; i<filmy.size(); i++)
        {
            output<<filmy[i].nazev<<"<br />"<<endl;
        }
        output<<"</p>";
        output.close();
    }
}

//funkce pro výpis všech filmů, shodujících se s zadaných žánrem
void Vypis_Zanr(vector<Film> &filmy)
{
    //zadání žánru
    char volba_zanr[20];
    cout<<"Zadejte zanr: ";
    cin>>volba_zanr;
    cout<<endl;


    cout<<"Nazev filmu"<<endl;
    cout<<"------------"<<endl;

    //procházení všech dat ve struktuře
    for(unsigned int i = 0; i<filmy.size(); i++)
    {
        //podmínka ověření, zda se námi zadaný žánr shoduje se žánrem ve struktuře, pokud ano přijdeme na jeho výpis, pokud ne pokrečujeme dále
        if(filmy[i].zanr == volba_zanr)
        { cout<<endl;
            cout<<filmy[i].nazev<<endl;
        }
    }
     cout<<endl;
    //opět uložení do souboru
    cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
    string volba;
    cin >> volba;
    if(volba == "ano")
    {
        ofstream output("../vystupnidata/Vypis_filmu.html");
        output<<"<p>";
        output<<"<b>Nazev filmu</b><br>"<< endl;

        for(unsigned int i = 0; i<filmy.size(); i++)
        {
            if(filmy[i].zanr == volba_zanr)
            {
                output<<filmy[i].nazev<<"<br />"<<endl;
            }
        }
        output<<"</p>";
        output.close();
    }
}

//funkce pro výpis všech filmů shodujících se s námi zadaných intervalem let
void Vypis_Rok(vector<Film> &filmy)
{
    int rok_od;
    int rok_do;

    //zadání itervalu
    cout<<"Zadejte rok od - do (cisla oddelte mezerou): ";
    cin>>rok_od>>rok_do;
    cout<<endl;


    cout<<"Nazev filmu"<<endl;
    cout<<"------------"<<endl;

    for(unsigned int i = 0; i<filmy.size(); i++)
    {

        //ověření intervalu a výpis
        if(filmy[i].rok >= rok_od && filmy[i].rok <= rok_do)
        {
            cout<<filmy[i].nazev<<endl;
        }
    }
     cout<<endl;

    //uložení do souboru
    cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
    string volba;
    cin >> volba;

    if(volba== "ano")
    {
        ofstream output("../vystupnidata/Vypis_filmu.html");
        output<<"<p>";
        output<<"<b>Nazev filmu</b><br>"<< endl;

        for(unsigned int i = 0; i<filmy.size(); i++)
        {
            if(filmy[i].rok >= rok_od && filmy[i].rok <= rok_do)
            {
                output<<filmy[i].nazev<<"<br />"<<endl;
            }
        }
        output<<"</p>";
        output.close();
    }
}

//funkce pro výpis informací o filmu dle námi zadaného ID nebo názvu
void Vypis_film_volba(vector<Film> &filmy, vector<Herec> &herci)
{
    //dotaz zda chce uživatel zadat ID
    cout<<"Chcete vyhledavat dle ID? ano/ne"<<endl;
    string volba;
    cin >> volba;
     cout<<endl;

    if(volba == "ano")
    {
        int zadane_id;
        cout<<"Zadejte ID filmu:";
        cin>>zadane_id;
        cout<<endl;
         cout<<endl;

        cout<<"Nazev filmu | Rok | Zanr | Puvod | Delka"<<endl;
        cout<<"----------------------------------------"<<endl;

        //ověření zadaného ID s ID ve struktuře a pokud je shodné přestupuje se na výpis
        for(unsigned int i = 0; i<filmy.size(); i++)
        {
            if(filmy[i].id == zadane_id)
            {
                cout<<filmy[i].nazev<<"  "<<filmy[i].rok<<"  "<<filmy[i].zanr<<"  "<<filmy[i].puvod<<"  "<<filmy[i].delka<<"  "<< endl;
                cout << "Hraji: "<<endl;
                //před výpisem herců, je zde uvěření zda ID herce uvedené u filmu je shodné s nějakým hercem ve struktuře herců a pokud ano dojde na výpis jeho jména a příjmení
                for(unsigned int j = 0; j<filmy[i].id_hercu.size(); j++)
                {
                    for(unsigned int k = 0; k < herci.size(); k++)
                        if(filmy[i].id_hercu[j] == herci[k].id)
                        {
                            if(j != 0)
                                cout << ", ";
                            cout<<herci[k].jmeno<<" "<<herci[k].prijmeni;
                            break;
                        }
                }
                cout<<endl;
            }
        }
         cout<<endl;
        //zápis do souboru
        cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
        string volba;
        cin >> volba;

        if(volba == "ano")
        {
            ofstream output("../vystupnidata/Vypis_Informaci_o_filmu.html");
            output<<"<p>";
            output<<"<b>Nazev filmu | Rok | Zanr | Puvod | Delka </b><br />"<< endl;

            for(unsigned int i = 0; i<filmy.size(); i++)
            {
                if(filmy[i].id == zadane_id)
                {
                    output<<filmy[i].nazev<<"  "<<filmy[i].rok<<"  "<<filmy[i].zanr<<"  "<<filmy[i].puvod<<"  "<<filmy[i].delka<<"  "<< endl;;
                    output << "<br />Hraji: "<<endl;
                    for(unsigned int j = 0; j<filmy[i].id_hercu.size(); j++)
                    {
                        for(unsigned int k = 0; k < herci.size(); k++)
                            if(filmy[i].id_hercu[j] == herci[k].id)
                            {
                                if(j != 0)
                                    output << ", ";
                                output<<herci[k].jmeno<<" "<<herci[k].prijmeni;
                                break;
                            }
                    }
                    output<<"<br />";
                }
            }
            output<<"</p>";
            output.close();
        }
    }
    else
    {
        //pokud uživatel zadal, že nechce vyhledávat dle ID, dojde automaticky na vyhledávání dle uživatelem zadaného jména filmu
        //postup dále je stejný s vyhledáváním a výpisem dle ID, jenom místo ID používáme k porovnání název filmu
         cout<<endl;
        cout<<"Probehne vyhledavani dle nazvu filmu."<<endl;

        string zadany_nazev;
        cout<<"Zadejte nazev filmu:";
        cin>>zadany_nazev;
         cout<<endl;
          cout<<endl;

        cout<<"Nazev filmu | Rok | Zanr | Puvod | Delka"<<endl;
        cout<<"--------------------------------------"<<endl;

        for(unsigned int i = 0; i<filmy.size(); i++)
        {
            if(filmy[i].nazev == zadany_nazev)
            {
                cout<<filmy[i].nazev<<"  "<<filmy[i].rok<<"  "<<filmy[i].zanr<<"  "<<filmy[i].puvod<<"  "<<filmy[i].delka<<"  "<< endl;
                cout << "Hraji: "<<endl;
                for(unsigned int j = 0; j<filmy[i].id_hercu.size(); j++)
                {
                    for(unsigned int k = 0; k < herci.size(); k++)
                        if(filmy[i].id_hercu[j] == herci[k].id)
                        {
                            if(j != 0)
                                cout << ", ";
                            cout<<herci[k].jmeno<<" "<<herci[k].prijmeni;
                            break;
                        }
                }
                cout<<endl;
            }
        }
        cout<<endl;
        //uložení do souboru
        cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
        string volba;
        cin >> volba;

        if(volba == "ano")
        {
            ofstream output("../vystupnidata/Vypis_Informaci_o_filmu.html");
            output<<"<p>";
            output<<"<b>Nazev filmu | Rok | Zanr | Puvod | Delka</b><br />"<< endl;

            for(unsigned int i = 0; i<filmy.size(); i++)
            {
                if(filmy[i].nazev == zadany_nazev)
                {
                    output<<filmy[i].nazev<<"  "<<filmy[i].rok<<"  "<<filmy[i].zanr<<"  "<<filmy[i].puvod<<"  "<<filmy[i].delka<<"  "<< endl;;
                    output << "<br />Hraji: "<<endl;
                    for(unsigned int j = 0; j<filmy[i].id_hercu.size(); j++)
                    {
                        for(unsigned int k = 0; k < herci.size(); k++)
                            if(filmy[i].id_hercu[j] == herci[k].id)
                            {
                                if(j != 0)
                                    output << ", ";
                                output<<herci[k].jmeno<<" "<<herci[k].prijmeni;
                                break;
                            }
                    }
                    output<<"<br />";
                }
            }
            output<<"</p>";
            output.close();
        }
    }
}

//funkce pro výpis informací o herci
void Vypis_herec_volba(vector<Film> &filmy, vector<Herec> &herci)
{

    //dotaz zda uživatel chce zadat ID
     cout<<endl;
    string volba;
    cout<<"Chcete vyhledavat dle ID? ano/ne"<<endl;
    cin >> volba;
    if(volba == "ano")
    {
        int zadane_id;
        cout<<"Zadejte ID herce:";
        cin>>zadane_id;
        cout<<endl;
         cout<<endl;

        cout<<"Jmeno | Prijmeni | Datum narozeni | Misto narozeni"<<endl;
        cout<<"--------------------------------------------------"<<endl;

        //ověřování shod se zadaným ID a dále výpis informací o herci
        for(unsigned int i = 0; i<herci.size(); i++)
        {

            if(herci[i].id == zadane_id)
            {
                cout<<herci[i].jmeno<<"  "<<herci[i].prijmeni<<"  "<<herci[i].datum_nar<<"  "<<herci[i].misto_nar<<"  "<< endl;
                cout << "Hral v: "<<endl;
                //prohcázení struktury zda se ID herce uvedeného u filmu shoduje s ID herce ve struktuře herců
                //pokud ano dojde na jeho výpis
                for(unsigned int j = 0; j<herci[i].id_filmu.size(); j++)
                {
                    for(unsigned int k = 0; k < filmy.size(); k++)
                    if(herci[i].id_filmu[j] == filmy[k].id)
                    {
                        if(j != 0)
                            cout << ", ";
                        cout<<filmy[k].nazev;
                        break;
                    }
                }
                cout<<endl;
            }
        }
         cout<<endl;
        //uložení do souboru
       cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
        string volba;
        cin >> volba;

        if(volba == "ano")
        {


            ofstream output("../vystupnidata/Vypis_Informaci_o_herci.html");
            output<<"<p>";
            output<<"<b>Jmeno | Prijmeni | Datum narozeni | Misto narozeni</b><br>"<< endl;

            for(unsigned int i = 0; i<herci.size(); i++)
            {

                if(herci[i].id == zadane_id)
                {
                    output<<herci[i].jmeno<<"  "<<herci[i].prijmeni<<"  "<<herci[i].datum_nar<<"  "<<herci[i].misto_nar<<"  ";
                    output << "<br />Hral v: "<<endl;
                    for(unsigned int j = 0; j<herci[i].id_filmu.size(); j++)
                    {
                        for(unsigned int k = 0; k < filmy.size(); k++)
                        if(herci[i].id_filmu[j] == filmy[k].id)
                        {
                            if(j != 0)
                                output << ", ";
                            output<<filmy[k].nazev;
                            break;
                        }
                    }
                    output<<endl;
                }
            }
            output<<"</p>";
            output.close();
        }
    }
    else
    {

        //pokud uživatel zadá, že nechce zadat a vyhledávat dle ID, probíhá automaticky vyhledávání dle jména herce, které zadá uživatel
        //dále je postup stejný jako u vyhledávání dle zadanáho ID jenom místo ID používáme jméno a příjmení herce
        //po ověření proběhne výpis a uložení do souboru
         cout<<endl;
        cout<<"Probehne vyhledavani dle jmena a prijemni herce."<<endl;

        string zadane_jmeno;
        string zadane_prijmeni;
        cout<<"Zadejte jmeno herce:";
        cin>>zadane_jmeno;
        cout<<"Zadejte prijmeni herce:";
        cin>>zadane_prijmeni;
        cout<<endl;
         cout<<endl;

        cout<<"Jmeno | Prijmeni | Datum narozeni | Misto narozeni"<<endl;
        cout<<"--------------------------------------------------"<<endl;

        for(unsigned int i = 0; i<herci.size(); i++)
        {
            if(herci[i].jmeno == zadane_jmeno && herci[i].prijmeni == zadane_prijmeni)
            {
                cout<<herci[i].jmeno <<"  "<<herci[i].prijmeni<<"  "<<herci[i].datum_nar<<"  "<<herci[i].misto_nar<<"  "<< endl;
                cout << "Hral v: "<<endl;
                for(unsigned int j = 0; j<herci[i].id_filmu.size(); j++)
                {
                    if(herci[i].id_filmu[j] == filmy[i].id)
                    {
                        if(j != 0)
                            cout << ", ";
                        cout<<filmy[i].nazev;
                        break;
                    }
                }
                cout<<endl;
            }
        }

         cout<<endl;
        cout<<"Chcete provest export do HTML souboru? ano/ne"<<endl;
        string volba;
        cin >> volba;

        if(volba == "ano")
        {
            ofstream output("../vystupnidata/Vypis_Informaci_o_herci.html");
            output<<"<p>";
            output<<"<b>Jmeno | Prijmeni | Datum narozeni | Misto narozeni </b><br />"<< endl;

            for(unsigned int i = 0; i<herci.size(); i++)
            {
                if(herci[i].jmeno == zadane_jmeno && herci[i].prijmeni == zadane_prijmeni)
                {
                    output<<herci[i].jmeno<<"  "<<herci[i].prijmeni<<"  "<<herci[i].datum_nar<<"  "<<herci[i].misto_nar<<"  ";
                    output << "<br />Hral v: "<<endl;
                    for(unsigned int j = 0; j<herci[i].id_filmu.size(); j++)
                    {
                        if(herci[i].id_filmu[j] == filmy[i].id)
                        {
                            if(j != 0)
                                output << ", ";
                            output<<filmy[i].nazev;
                            break;
                        }
                    }
                    output<<"<br />";
                }
            }
            output<<"</p>";
            output.close();
        }
    }
}

