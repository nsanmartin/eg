#include <string>
#include <iostream>
#include <chrono>
#include <list>

#include "ConcurrentHashMap.hpp"

using namespace std;

struct args {
    list<string>* archivos;
    atomic<int>* archivos_usados;
};

entrada maximum(unsigned int p_archivos, unsigned int p_maximos,
                list<string> archs) ;
void* procesar_archivos(struct args *argumentos);
struct args*
new_args(list<string>* archs, atomic<int>* archivos_usados);

inline int next_file(std::atomic<int>* archivos_usados) {
    return archivos_usados->fetch_add(1, std::memory_order_relaxed);
}
    
int main(int argc, char ** argv) {
    if (argc < 2) {
        cout << "Filenames missing" << endl;
        exit(0);
    }
    list<string> archivos;
    for (int i= 1; i < argc; i++)
        archivos.push_back(argv[i]);
    cout << "steady_clock "
         << chrono::steady_clock::period::num << endl
         << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha
         << chrono::steady_clock::is_steady << endl << endl;

    auto start_clock = chrono::steady_clock::now();
    entrada e = maximum(2, 5, archivos);
	auto end_clock = chrono::steady_clock::now();
	auto delta_clock = end_clock - start_clock;
    cout << "Time: "
         << chrono::duration <double, milli>
         (delta_clock).count() << " ms"
         << endl;

    cout << e.first << " " << e.second << endl;
    return 0;
}

entrada maximum(unsigned int p_archivos, unsigned int p_maximos,
                list<string> archs) {
    std::atomic<int> archivos_usados;
    archivos_usados.store(0, std::memory_order_relaxed);

    pthread_t threads[p_archivos];
    for (int i = 0; i < p_archivos; i++) {
         pthread_create(
             &threads[i], NULL,
             (void* (*)(void*))procesar_archivos,
             (void*) new_args(&archs, &archivos_usados));
    }
    // Esperamos a que terminen todos los threads.
    ConcurrentHashMap mapa_total;
    for (int i = 0; i < p_archivos; i++) {
        ConcurrentHashMap* mapa_actual;
        pthread_join(threads[i], (void**) &mapa_actual);
        mapa_total.concat(*mapa_actual);
        //agregar_mapa(&mapa_total, mapa_actual);
        // Hay que destruir el mapa aca
        delete mapa_actual;
    }
    return mapa_total.maximum(p_maximos);
}

void* procesar_archivos(struct args *argumentos) {
    ConcurrentHashMap* map = new ConcurrentHashMap();
    list<string>* archivos = argumentos->archivos;
    atomic<int>* archivos_usados
        = argumentos->archivos_usados;

    int cant_archivos = archivos->size();
    int indx_next_file;
    while ((indx_next_file = next_file (archivos_usados))
           < archivos->size()) {
            std::list<std::string>::iterator it
                = std::next((*archivos).begin(),
                            indx_next_file);
            //std::string arch = *it;
            std::ifstream file(*it, std::fstream::in);
            map->add_words(file);
            file.close();
            //count_words_and_add_to_map(*map, arch);
    }
    free(argumentos);
    pthread_exit((void*) map);
}
 
struct args*
new_args(list<string>* archs, atomic<int>* archivos_usados) {
     struct args *argumentos = (args*) malloc (sizeof(struct args));
     argumentos->archivos = archs;
        argumentos->archivos_usados = archivos_usados;
        return argumentos;
}
