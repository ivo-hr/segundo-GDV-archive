//VJ37 Paula Morillas Alonso
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <unordered_map>

using namespace std;


using Pelicula = string;
using Actor = string;

//Un unordered map que guarda el nombre del actor y los minutos que ha aparecido en pantalla en esa película
using InfoPeli = unordered_map<Actor, int>;

/*Un unordered map que guarda el nombre de la película. 
Tiene como clave el nombre de la pelicula y como valor el unordered_map de actores*/
using RepartosPeliculas = unordered_map<Pelicula, InfoPeli>;



//Nombre de la película y el número de veces que ha aparecido en el último año
using RepeticionesPelicula = unordered_map<Pelicula, int>;
//Nombre del actor y el número de minutos que ha aparecido en total en el último año
using MinutosActores = unordered_map<Actor, int>;

//Pair con el nombre de la mejor peli hasta el momento, guarda la película que ha tenido mas emisiones y cúantas emisiones ha tenido
using MejorPeli = pair<Pelicula, int>;



//El coste deberá ser O(numPeliculas * numActores) porque se recorren todas las peliculas y todos los actores que tiene cada una de ellas
//En el peor caso O(numMaxPeliculas * numMaxActores) 
void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas) {
    Pelicula peli; int numActores;
    Actor actor; int minutos;
    for (int i = 0; i < numPeliculas; ++i) {
        cin >> peli; cin >> numActores;

            for (int j = 0; j < numActores; ++j) {
                cin >> actor >> minutos;
                
                
                /*Busca en el unordered_ map de RepartosPeliculas, y sitúa la película. 

                Después accede al unordered_map de InfoPelis y sitúa el actor correspondiente.

                Por último iguala el número de minutos de aparición de ese actor al número de minutos 
                de aparción proporcionado por la entrada. 

                Al utilizar el operador [], si no existe aun ese elemento en el u_map, se inserta/crea*/

                peliculas[peli][actor] = minutos;
            }
    }
}


/*El coste dependerá de las emisiones que haya, asi como cuantos actores haya en cada una de las peliculas ya que para cada pelicula
se recorren todos sus actores asi que el coste sera del orden de O(numEmisiones* numActoresEmsion). */

void procesarEmisiones(RepartosPeliculas const& repartos, vector<string> const& secEmisiones) {
    
    //Variables de los alias definidos anteriormente
    RepeticionesPelicula repeticionesPeli;
    MinutosActores minusActores;
    MejorPeli mejorPelicula;

    //Variable que lleva el conteo de el numero máximo de minutos que ha aparecido un actor hasta el momento
    int mayoresMinutos=0; 

    //Vector de actores que han aparecido el mismo tiempo en pantalla
    vector<Actor> mejoresActores; 

    int numEmisiones = secEmisiones.size();

    
    for (int i = 0; i < numEmisiones; i++)
    {
        //Guarda la pelicula actual de la secuencia de emisiones
        Pelicula peliculaAct = secEmisiones[i];

        /*Si la peli ya ha aparecido anteriormente, se busca y se le suma una reproducción al total, 
        si no, se añade y se añade una reproducción*/

        int repsDeEstaPeli= repeticionesPeli[peliculaAct] += 1;

        /*Si aun no hay mejor peli o la peli actual tiene mas repeticiones que la que era mejor hasta el momento, 
        se actualizan los valores de la mejor película*/

        if (mejorPelicula.first == "" || repsDeEstaPeli >= mejorPelicula.second) 
        {
            mejorPelicula = { peliculaAct, repsDeEstaPeli };
        }
        
           
        //Con un iterador apuntamos al unordered_map de actores que han aparecido en esa peli
        auto peliAct_It = repartos.find(peliculaAct)->second;

        //Con este iterador apuntamos inicialmente al primer actor de unordered_map de peliculas 
        auto actores_It = peliAct_It.begin();
      
        while (actores_It!=peliAct_It.end())
        {
            Actor actorActual = actores_It->first;

            /*A los minutos totales de este actor (guardados en minActores) les sumamos los minutos que 
            ha aparecido en la pelicula que estamos procesando*/
            int minsEsteActor = minusActores[actorActual] += actores_It->second;

            //Si este actor ha aparecido mas minutos que el mejor actor hasta el momento, actualizamos el valor del mejor actor
            if (minsEsteActor > mayoresMinutos) 
            {

                mayoresMinutos = minsEsteActor; 

                //Vaciamos el vector que guarda el mejor actor
                mejoresActores.clear();

                //Añadimos el que es el nuevo mejor actor
                mejoresActores.push_back(actorActual);
            }
            else if (minsEsteActor == mayoresMinutos)
            {
                /*Si el actor actual tiene los mismos minutos de pantalla que el mejor actor actual, 
                se añade junto al mejor actor al vector de los mejores actores*/
                mejoresActores.push_back(actorActual);
            }

            //Avanzamos el iterador
            actores_It++;
        }
        
    }
    

    //Escribe las reproducciones en todo el año de la mejor película y nombre de la mejor película
    cout << mejorPelicula.second << " " << mejorPelicula.first<<endl;

    //Escribe el numero de minutos que ha aparecido en pantalla el mejor actor (o los mejores actores) del año
    cout << mayoresMinutos << " ";
    
    //Varios actores coinciden en el número de minutos que han aparecido
    if (mejoresActores.size() > 1)
    {   
        //Ordenados en orden ascendente
        sort(mejoresActores.begin(), mejoresActores.end());

        //Escribir sus nombres con espacios entre ellos
        for (int i = 0; i < mejoresActores.size(); i++)
        {
            cout << mejoresActores[i]<<" ";
        }
    }
    else 
    {
        cout << mejoresActores[0]; //Escribe el nombre del mejor actor
    }
    cout << endl;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPelis, numEmisiones;
    cin >> numPelis;
    if (numPelis == 0)
        return false;

    // Lectura de los repartos de las peliculas
    RepartosPeliculas repartos;
    leerRepartos(numPelis, repartos);

    // Lectura de la secuencia de peliculas emitidas en vector<string>
    cin >> numEmisiones;
    vector<string> secEmisiones(numEmisiones);
    for (string& s : secEmisiones) cin >> s;

    procesarEmisiones(repartos, secEmisiones);

    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
//#ifndef DOMJUDGE
//    std::ifstream in("input3.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
//#endif

    while (resuelveCaso());

//    // Para restablecer entrada. Comentar para acepta el reto
//#ifndef DOMJUDGE // para dejar todo como estaba al principio
//    std::cin.rdbuf(cinbuf);
//#endif

    return 0;
}
