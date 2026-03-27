#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

class Tablica
{
public:
    int m = 10;
    int l = 1;
    int ilosc = 0;
    int licz = 0;
    int a = 0;
    int b = 0;
    clock_t start = 0, stop = 0;
    double czas = 0;

    void dodaj()
    {
        while ((m <= 9 && m >= 2) != true)
        {
            cout << "podaj wielkość pola planszy w przedziale od 2 do 9: ";
            cin >> m;
        }
    }

    void include(vector<vector<char>> &in)
    {

        in.resize(m);
        for (int i = 0; i < in.size(); i++)
        {
            in[i].resize(m);
        }

        for (int i = 0; i < in.size(); i++)
        {
            for (int j = 0; j < in[i].size(); j++)
            {
                in[i][j] = 35;
            }
        }
    }

    void podmien(vector<vector<char>> &in)
    {
        for (int i = 0; i < m * 2; i++)
        {
            static mt19937 generator(random_device{}());
            uniform_int_distribution<int> distribution(0, m - 1);
            a = distribution(generator);
            b = distribution(generator);
            in[a][b] = 38;
        }
    }
    void zlicz(vector<vector<char>> &in)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (in[i][j] == 38)
                {
                    ilosc++;
                }
                else
                {
                    ilosc = ilosc;
                }
            }
        }
    }
    void statki(vector<vector<char>> &in)
    {
        int x, y;

        cout << endl;
        cout << "Masz do zgadnięcia jeszcze " << ilosc - licz << " Wypisz pozycje x y : ";
        cin >> y >> x;
	#ifdef _WIN32
    		system("cls");
	#else
    		system("clear");
	#endif
        if (x == 0 || y == 0)
        {
            cout << "Wypisz pozycje x y jeszcze raz w poprawnym miejscu zamiast w 0 0: " << endl
                 << endl;
        }
        else if (x > m || y > m)
        {
            cout << "Wypisz pozycje x y jeszcze raz w poprawnym miejscu zamiast większe od rozmiaru planszy: " << endl
                 << endl;
        }
        else
        {
            x--;
            y--;

            if (in[x][y] == 38)
            {
                cout << "Gratulacje trafiłeś cel.";
                cout << endl;
                in[x][y] = 36;
            }
            else if (((x >= 0 && x < m) && (y < m && y >= 0)) && in[x][y] == 35)
            {
                cout << "Nie trafiłeś w cel.";
                cout << endl;
                in[x][y] = 33;
            }
            else if (in[x][y] == 36 || in[x][y] == 33)
            {
                cout << "To pole już atakowałeś";
                cout << endl;
            }
            else
            {
                cout << "Nie trafiłeś w tablice";
                cout << endl;
            }
            cout << endl;
        }
    }
    void print(vector<vector<char>> &in)
    {
        l = 1;
        for (int i = 0; i <= m; i++)
        {
            if (i == 0)
            {
                for (int k = 0; k <= m; k++)
                {
                    cout << k << " ";
                }
            }
            else
            {
                for (int j = 0; j <= m; j++)
                {
                    if (j == 0)
                    {
                        cout << l << " ";
                        l++;
                    }
                    else
                    {
                        if (in[i - 1][j - 1] != 38)
                        {
                            cout << in[i - 1][j - 1] << " ";
                        }
                        else
                        {
                            cout << "# ";
                        }
                    }
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    void koniec(vector<vector<char>> &in)
    {

        if (czas == 0)
        {
            start = clock();
        }
        else
        {
        }

        licz = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (in[i][j] == 36)
                {
                    licz++;
                }
                else
                {
                    licz = licz;
                }
            }
        }
        if (ilosc == licz)
        {
            stop = clock();
            czas = (double)(stop - start) / CLOCKS_PER_SEC;
            cout << endl
                 << "Wygrałeś w statki na planszy " << m << " na " << m << " w czsie " << czas << " sekund." << endl;
            cout << "Gratuluje twojej wygranej w statki!!!!!!!!!!!!!!!!!!!" << endl;
            exit(0);
        }
        czas++;
    }
};

int main()
{

    // polskie znaki
    setlocale(LC_ALL, "polish");

    vector<vector<char>> b1;
    Tablica tab;
    tab.dodaj();
    tab.include(b1);
    cout << endl;
    tab.print(b1);
    tab.podmien(b1);
    tab.zlicz(b1);

    while (true)
    {
        tab.statki(b1);
        tab.print(b1);
        tab.koniec(b1);
    }

    return 0;
}
