
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

bool isValid(int bandNo, vector<vector<bool>> consentimientos, vector<int> solution, int k) {  //Valida si se puede usar el grupo

	if (k == 0) return true;

	for (int i = 0; i < k; i++) {  //Por si ha actuado ya
		if (bandNo == solution[i]) return false;
	}

	return consentimientos[bandNo][solution[k-1]]; //Por si consiente actuar antes que el anterior
}

//Gracias Javi por ayudarme con las variables

// función que resuelve el problema
void resolver(int bandNo, vector<vector<int>> beneficios, vector<vector<bool>> consentimientos, 
	vector<int>& solution, int k, int currentBenef, int& bestBenef) {

	//RECURSION
	for (int otherBand = 0; otherBand < bandNo; otherBand++) {

		solution[k] = otherBand; 

		//Si es válida la banda, se coloca
		if (isValid(otherBand, consentimientos, solution, k)) {
			//Se suman los beneficios de la banda dependiendo de cuando actúa
			currentBenef += beneficios[otherBand][k];

			//Asigna el mejor beneficio si el actual lo supera
			if (k == bandNo - 1 && currentBenef > bestBenef) bestBenef = currentBenef;
			//Si no, recursión
			else resolver(bandNo, beneficios, consentimientos, solution, k + 1, currentBenef, bestBenef);

			//Se restan los beneficios de las bandas al actual
			currentBenef -= beneficios[otherBand][k];
		}

	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	vector<vector<int>> beneficios(n, vector<int>(n));
	vector<vector<bool>> consentimientos(n, vector<bool>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> beneficios[i][j];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int b;
			cin >> b;
			consentimientos[i][j] = b;
		}
	vector<int> solution(n);
	int bestBenef = -1;
	resolver(n, beneficios, consentimientos, solution, 0, 0, bestBenef);


	// salida
	if (bestBenef >= 0) cout << bestBenef << endl;
		
	else cout << "NEGOCIA CON LOS ARTISTAS ";
}

//#define DOMJUDGE
int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
//#ifndef DOMJUDGE
//	std::ifstream in("input3.txt");
//	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
//#endif
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
//#ifndef DOMJUDGE // para dejar todo como estaba al principio
//	std::cin.rdbuf(cinbuf);
//	//system("PAUSE");
//#endif

	return 0;
}
