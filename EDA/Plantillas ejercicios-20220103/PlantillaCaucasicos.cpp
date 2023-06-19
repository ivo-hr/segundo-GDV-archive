
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


bool caucasico(vector<int> sec, int n) {
    int mitad = n / 2;
    int[2] numPares = { 0, 0 };

    for (int i = 0; i < sec.length(); i++) {
        if (sec[i] % 2 == 0) {
            if (i <= mitad) {
                numPares[0]++;
            }
            else numPares[1]++;
        }
    }
    return numPares[0] == numPares[1];
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (caucasico(sec, n)? "SI" : "NO") << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}