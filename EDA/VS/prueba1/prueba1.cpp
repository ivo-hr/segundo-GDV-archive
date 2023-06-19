#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Resolución del problema
// Orden del coste si las palabras son de misma longitud (caso peor):
//  Sera de 0(n^2) (coste cuadrático), ya que se realiza un bucle anidado
// 
// Orden del coste si las palabras son de distinta longitud (caso mejor):
//  Sera de 0(1) (complejidad lineal), ya que solo se realiza una comparación
bool anagramas(const string& cad1, const string& cad2) {
	
	bool toReturn = true;
	

	int wrdSz = cad1.size();
	int scndWrdLngth = cad2.size();
	
	if (wrdSz != scndWrdLngth) {
		toReturn = false;
	}

	else {

		vector <bool> paired(wrdSz);

		for (int i = 0; i < paired.size(); i++) {

			paired.at(i) = false;
		}

		for (int i = 0; i < wrdSz; i++) {
			
			bool stopLooking = false;

			for (int j = 0; j < wrdSz; j++) {

				if (!stopLooking) {

					if (cad1[i] == cad2[j] && !paired[j]) {

						paired.at(j) = true;

						stopLooking = true;
					}
				}
				
			}
		}

		for (int i = 0; i < paired.size(); i++) {

			if (!paired[i]) {

				toReturn = false;
			}
		}

		return toReturn;
	}
	
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