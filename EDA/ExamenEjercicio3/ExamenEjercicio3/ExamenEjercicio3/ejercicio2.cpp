//////Paula Morillas Alonso DNI: 12447478Q Lab: 2 Puesto:17
////// El código funciona sin problemas tanto con los inputs introducidos mediante el archivo txt como con los casos del juez
//////VJ37
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include "bintree_eda.h"
//using namespace std;
//
//template <class T>
//bool esHoja(bintree<T> const& tree)
//{
//    if (tree.empty()) return false;
//    else if (tree.left().empty() && tree.right().empty()) return true;
//    else return false;
//
//}
//template <class T>
//void singularesRecursion(bintree<T> const& tree, int& sumaAnt, int& sumaHijos, int& nodosSing)
//{
//    if (tree.empty())
//    {
//        sumaHijos = 0;
//
//    }
//    else if (esHoja(tree))
//    {
//        sumaHijos = tree.root();
//
//        //Corrección respecto al examen
//        if (0 == sumaAnt) ++nodosSing;
//    }
//    else
//    {
//        int sumaHijosIzq, sumaHijosDer, sumaAntDer, sumaAntIzq;
//
//        sumaAnt += tree.root();
//        singularesRecursion(tree.left(), sumaAnt, sumaHijosIzq, nodosSing);
//        singularesRecursion(tree.right(), sumaAnt, sumaHijosDer, nodosSing);
//
//        sumaAnt -= tree.root();
//        sumaHijos = sumaHijosIzq + sumaHijosDer;
//        if (sumaHijos == sumaAnt)
//        {
//            ++nodosSing;
//        }
//        sumaHijos += tree.root();
//    }
//
//
//}
//
//template<class T>
//int singulares(bintree<T> const& tree)
//{
//
//    if (tree.empty())
//    {
//        return 0;
//    }
//    else if (esHoja(tree))
//    {
//        return 1;
//    }
//    else
//    {
//        int sumaAnt = 0, sumaHijos, nodosSing = 0;
//        singularesRecursion(tree, sumaAnt, sumaHijos, nodosSing);
//        return nodosSing;
//    }
//}
//
//
//
//// Resuelve un caso de prueba, leyendo de la entrada la
//// configuración, y escribiendo la respuesta
//void resuelveCaso() {
//    // leer los datos de la entrada
//    bintree<int> tree;
//    tree = leerArbol(-1);
//    cout << singulares(tree) << endl;
//}
//
//
////#define DOMJUDGE
//int main() {
//    // Para la entrada por fichero.
//    // Comentar para acepta el reto
////#ifndef DOMJUDGE
////    std::ifstream in("input2.txt");
////    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
////#endif
//
//    int numCasos;
//    std::cin >> numCasos;
//    for (int i = 0; i < numCasos; ++i)
//        resuelveCaso();
//
//    ////    // Para restablecer entrada. Comentar para acepta el reto
//    //#ifndef DOMJUDGE // para dejar todo como estaba al principio
//    //    std::cin.rdbuf(cinbuf);
//    //    //system("PAUSE");
//    //#endif
//
//    return 0;
//}