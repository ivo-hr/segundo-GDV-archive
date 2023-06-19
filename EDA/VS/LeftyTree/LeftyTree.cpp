
#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;


//es de coste lineal n, ya que recorro todos los nodos
bool isLefty(bintree<char> const& tree, int& descendants) {

	if (tree.empty()) {
		descendants = 0;
		return true;
	}
	else if (tree.left().empty() && tree.right().empty()) {
		descendants = 1;
		return true;
	} 
	else {

		int desL, desR;

		bool isLeftyL = isLefty(tree.left(), desL);
		bool isLeftyR = isLefty(tree.right(), desR);

		descendants = desL + desR + 1;

		bool globalLeft = desL > (desL + desR) / 2;

		return isLeftyL && isLeftyR && globalLeft;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<char> tree;
	tree = leerArbol('.');
	
	int descendants = 0;

	if (isLefty(tree, descendants)) 
		cout << "SI" << endl;
	else 
		cout << "NO" << endl;

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
