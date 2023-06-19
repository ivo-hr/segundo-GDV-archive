#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T> {
	using Nodo = typename queue<T>::Nodo;

public:

	//El coste es lineal ya que se trata exclusivamente de bucles; es de coste 'n'
	void cuela(const T& a, const T& b) {
		// Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult

		bool isThereA = false;
		Nodo* auxA = this -> prim;

		while (auxA != nullptr && !isThereA){

			if (auxA->elem == a) isThereA = true;
			else auxA = auxA->sig;
		}

		if (isThereA) {

			bool isThereB = false;
			Nodo* auxB = auxA->sig;
			
			while (auxB != nullptr && !isThereB) {

				if (auxB->elem == b) isThereB = true;
				else auxB = auxB->sig;
			}

			if (isThereB) {

				Nodo* antB = auxA;
				Nodo* sigA = auxA->sig;
				while (antB->sig != auxB) antB = antB->sig;

				if (antB != auxA) {
					antB->sig = auxB->sig;
					if (antB->sig == nullptr) {
						this->ult = antB;
					}
					auxA->sig = auxB;
					auxB->sig = sigA;
				}
				
				
				
			}
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, a, b;
	queue_plus<int> q;
	cin >> n;
	if (n == -1) return false;
	while (n != -1) {
		q.push(n);
		cin >> n;
	}
	cin >> a >> b;

	// llamada a metodo
	q.cuela(a, b);

	// escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
	for (int i = 0; i < q.size(); ++i) {
		n = q.front();
		q.pop();
		q.push(n);
	}
	// Ahora imprimimos la cola y de paso la dejamos vacía
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	return true;
}

//#define DOMJUDGE
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
