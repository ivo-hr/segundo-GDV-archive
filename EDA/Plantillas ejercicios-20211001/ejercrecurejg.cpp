#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

//ENRIQUE JUAN GAMBOA

// función que resuelve el problema
int resolver(vector<int> const& v1, vector<int> const& v2, int ini, int fin) {

    //Punto en el que se dividirán los vectores
    int midSort = (ini + fin) / 2;

    //En cuanto ya no se pueda dividir mas el vector quedará la posición que falta
    if (ini == fin){
        return ini;
    }
    
    //Recursor para ir dividiendo el vector hasta que se cumpla la cond. anterior
        //Si el número en pos. de división de v2 es menor que el de v1,miramos a la izq. del recorrido actual
    if (v1[midSort] != v2[midSort]) {
        return resolver(v1, v2, ini, midSort);                                                                                                                                      // Me olvidé de los  return :(
    }
        //Si es igual, a la dcha.
    else return resolver(v1, v2, midSort+1, fin);

}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    long long int numElementos;
    cin >> numElementos;
    vector<int> v1(numElementos);
    vector<int> v2(numElementos - 1);
    for (int& e : v1) cin >> e;
    for (int& e : v2) cin >> e;
    int sol = resolver(v1, v2, 0, v1.size()-1);
    cout << v1[sol] << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("input2.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect cin to casos.txt
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
#endif

    return 0;
}
