//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <iterator>
//#include <list>
//#include <iterator>
//using namespace std;
//
///*El coste del algoritmo debe ser lineal al utilizar los iteradores que se ven obligados a 
//recorrer la lista entera o la mayoría de esta. Como pos y lon son variables, y no constantes, 
//el coste dependerá de éstos valores y por lo tanto nunca podría ser un coste constante
//
//En el peor de los casos hay que recorrer todos los elementos de la lista*/
//
//void adelantar(list<char>& lista, int n, int pos, int lon, int k) {
//
//    list<char>::iterator it = lista.begin();
//    list<char>::iterator obj = lista.begin();
//
//    if (!lista.empty() && lon != 0 && k != 0 && pos < n && pos >= 0 && k>0 && k < n && pos - k >= 0)
//    {
//
//        if (pos + lon > n) lon = n - pos;
//
//        for (int i = 0; i < pos; i++) //Lo ejecutamos pos veces. Cuanto mayor sea pos, mayor será el número de veces que se ejecute este bucle
//        {
//            if (i < pos - k) ++obj; //Colocamos este otro iterador en el sitio objetivo al que queremos mover el elemento
//            ++it; //Colocamos el iterador en el elemento inicial
//        }
//        for (int i = 0; i < lon; i++) //Lo ejecutamos lon veces.Cuanto mayor sea lon, mayor será el número de veces que se ejecute este bucle
//        {
//            lista.insert(obj, *it);  //Coloca el elemento en su destino
//            it = lista.erase(it); //se queda con el siguiente elemento y borra el anterior
//
//        }
//
//
//
//    }
//
//}
//
//
//// Resuelve un caso de prueba, leyendo de la entrada la
//// configuración, y escribiendo la respuesta
//void resuelveCaso() {
//    char e;
//    int n, pos, lon, k;
//    list<char> l;
//
//    // leer los datos de la entrada
//    cin >> n >> pos >> lon >> k;
//    for (int i = 0; i < n; ++i) {
//        cin >> e;
//        l.push_back(e);
//    }
//
//    adelantar(l, n, pos, lon, k);
//
//    // Mostrar lista
//    for (char e : l) cout << e << " ";
//    cout << endl;
//}
//
//
////#define DOMJUDGE
//int main() {
//    // Para la entrada por fichero.
//    // Comentar para acepta el reto
////#ifndef DOMJUDGE
////    std::ifstream in("input1.txt");
////    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
////#endif
//
//    int numCasos;
//    std::cin >> numCasos;
//    for (int i = 0; i < numCasos; ++i)
//        resuelveCaso();
//
//    //    // Para restablecer entrada. Comentar para acepta el reto
//    //#ifndef DOMJUDGE // para dejar todo como estaba al principio
//    //    std::cin.rdbuf(cinbuf);
//    //    //system("PAUSE");
//    //#endif
//
//    return 0;
//}

