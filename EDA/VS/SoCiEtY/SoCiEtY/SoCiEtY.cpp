#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

using Estado = string;
using Partido = string;

struct stateInfo {
	unordered_map < Partido, int > party; 
	
	int senators;

	Partido winnerParty;
	int winnerPts;
};

class ConteoVotos {

private:

	unordered_map<Estado, stateInfo> state;
	

public:

	void nuevo_estado(const Estado& nombre, int num_compromisarios) {

		unordered_map<Estado, stateInfo>::iterator i = state.find(nombre);

		if (i == state.end()) {
			stateInfo thisStateInfo;
			thisStateInfo.party.insert({ "", 0 });
			thisStateInfo.senators = num_compromisarios;
			thisStateInfo.winnerParty = "";

			state.insert({ nombre, thisStateInfo });
		}
		else throw domain_error("Estado ya existente");
	}

	void sumar_votos(const Estado& estado, const Partido& partido, int num_votos) {

		unordered_map<Estado, stateInfo>::iterator i = state.find(estado);

		if (i == state.end()) throw domain_error("Estado no encontrado");
		else {

			int currPts = i->second.party[partido] += num_votos;
			
			if (currPts > i->second.winnerPts) {
				i->second.winnerPts = currPts;
				i->second.winnerParty = partido;
			}
		}
	}

	Partido ganador_en(const Estado& estado) const {
		
		unordered_map<Estado, stateInfo>::const_iterator i = state.find(estado);

		if (i == state.end()) throw domain_error("Estado no encontrado");

		else {
			return i->second.winnerParty;
		}
	}

	vector<pair<Partido, int>> resultados() const {
		vector<pair<Partido, int>> results;
		map<Partido, int> winners;
		unordered_map<Estado, stateInfo>::const_iterator i = state.begin();

		while (i != state.end()) {
			winners[i->second.winnerParty] += i->second.senators;
			++i;
		}

		auto j = winners.begin();

		while (j != winners.end()) {
			results.push_back({ j->first, j->second });
			++j;
		}

		return results;
	}

};


bool resuelveCaso() {
	string comando;
	cin >> comando;
	if (!cin) return false;

	ConteoVotos elecciones;

	while (comando != "FIN") {
		try {
			if (comando == "nuevo_estado") {
				Estado estado;
				int num_compromisarios;
				cin >> estado >> num_compromisarios;
				elecciones.nuevo_estado(estado, num_compromisarios);
			}
			else if (comando == "sumar_votos") {
				Estado estado;
				Partido partido;
				int num_votos;
				cin >> estado >> partido >> num_votos;
				elecciones.sumar_votos(estado, partido, num_votos);
			}
			else if (comando == "ganador_en") {
				Estado estado;
				cin >> estado;
				Partido ganador = elecciones.ganador_en(estado);
				cout << "Ganador en " << estado << ": " << ganador << "\n";
			}
			else if (comando == "resultados") {
				for (const auto& par : elecciones.resultados()) {
					cout << par.first << " " << par.second << "\n";
				}
			}
		}
		catch (std::exception& e) {
			cout << e.what() << "\n";
		}
		cin >> comando;
	}

	cout << "---\n";
	return true;
}
#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
