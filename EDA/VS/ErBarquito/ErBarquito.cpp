#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

//coste n (n = Nº elem del arbol), lineal
int NavigatableStreams(bintree<int> const& tree, int&navStreams) {

	if (tree.empty()) return 0;
	if (tree.left().empty() && tree.right().empty()) return 1;

	int riverFlow = NavigatableStreams(tree.left(), navStreams) + NavigatableStreams(tree.right(), navStreams) - tree.root();
	if (riverFlow > 2) navStreams++;
	else if (riverFlow < 0) riverFlow = 0;

	return riverFlow;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	bintree<int> arb;
	arb = leerArbol(-1); // -1 es la repr. de arbol vacio
	
	int solution = 0;
	int navStr = NavigatableStreams(arb, solution);


	//eliminación del caudal raíz si se ha sumado, por si acaso
	if (navStr > 2 && solution > 0) solution--;

	cout << solution << endl;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}

