#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Resolución del problema
// Orden del coste si las palabras son de misma longitud (caso peor):
//  Sera de O(n) (coste lineal), siendo n la longitud del abecedario o de las palabras, la que sea más grande.
// 
// Orden del coste si las palabras son de distinta longitud (caso mejor):
//  Sera de O(1) (complejidad lineal), ya que solo se realiza una comparación.
bool anagramas(const string& cad1, const string& cad2) {

	bool toReturn = true;
	
	if (cad1.length() != cad2.length()) {

		toReturn = false;
	}
	else {
		
		vector<int> w1(26, 0), w2(26, 0);

		for (char c : cad1) {
			w1[c - 'a']++;
		}

		for (char c : cad2) {
			w2[c - 'a']++;
		}

		toReturn = w1 == w2;
	}

	return toReturn;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	string word1, word2;
	cin >> word1 >> word2;
	cout << (anagramas(word1, word2) ? "SI" : "NO") << endl;
}


//#define DOMJUDGE
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
	system("PAUSE");
#endif

	return 0;
}