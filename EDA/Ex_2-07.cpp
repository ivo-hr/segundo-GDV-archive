// Sara Isabel García Moral
// VJ22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema
//a=1, b=2, k=0 por tanto a=b^k y es un allgoritmo con coste logaritmico O(log n)
int resolver(vector<int>v, int i, int f)
{
    if (i == f) return v[i];
    else 
    {
        int med = (i + f) / 2;
        if (v[i] > v[med + 1]) return resolver(v, med + 1, f);
        else return resolver(v, i, med);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int tam;
    cin >> tam;
    if (!cin)
        return false;
    vector<int>v(tam);
    for (int i = 0; i < tam; i++) cin >> v[i];

    // escribir sol
    cout << resolver(v, 0, tam - 1) << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 
    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}