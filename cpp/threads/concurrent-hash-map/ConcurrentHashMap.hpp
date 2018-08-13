#ifndef _CONCURRENT_HASH_MAP_H_
#define _CONCURRENT_HASH_MAP_H_

#include <utility>
#include <string>
#include <assert.h>

#include <pthread.h>

#include "AtomicList.hpp"
#include "ConcurrentHashMap.hpp"
#include <atomic>
#include <vector>
#include <mutex>
#include <fstream>
#define N_LETRAS 26

using namespace std;

typedef pair<string, unsigned int> entrada;


struct argumentos {
    entrada *maximo;
    atomic<int> *siguienteLetra;
    Lista<entrada>* _listas;
    pthread_mutex_t* max_mtx;
};

void *find_max(struct argumentos *args);

class ConcurrentHashMap {
public:
    Lista<entrada> _listas[N_LETRAS];
    pthread_mutex_t _mtxs[N_LETRAS];

public:
    ConcurrentHashMap() {
        for (int i = 0; i < N_LETRAS; i++)
            pthread_mutex_init(&_mtxs[i], NULL);
    }

    ConcurrentHashMap(const ConcurrentHashMap& c) {
        for (int i = 0; i < N_LETRAS; i++) {
            _mtxs[i] = c._mtxs[i];
        }
    }
    ConcurrentHashMap(std::ifstream& file) {
        for (int i = 0; i < N_LETRAS; i++)
            pthread_mutex_init(&_mtxs[i], NULL);

        std::string word;
        while (file >> word) 
            addAndInc(word);
    }

    ~ConcurrentHashMap() {
        for (int i = 0; i < N_LETRAS; i++)
            pthread_mutex_destroy(&this-> _mtxs[i]);
    }

    void addAndInc(string key) {
        int letra = hash(key);
        lock(letra);
        entrada *e = find(letra, key);
        if (e == nullptr)
            _listas[letra].push_front(entrada(key, 1));
        else
            e->second++;
        unlock(letra);
    }

    bool member(string key){ return getEntrada(key) != nullptr; }
    entrada maximum(unsigned int nt);
    void add_words(std::ifstream&);
    void concat(ConcurrentHashMap& other);
    /**
       Devuelve la cantidad de veces que se agregó la key.
       La key debe ser member del ConcurrentHashMap.
    */
    int get(string key) { return getEntrada(key)->second; }

    /**
       Devuelve un vector con todos los strings que son
       members de este ConcurrentHashMap.
    */
    vector<string> getKeys() {
        vector<string> keys;
        for (int letra = 0; letra < N_LETRAS; letra++) {
            for (Lista<entrada>::iterator it
                     = _listas[letra].begin();
                 it !=  _listas[letra].end(); ++it) {
                keys.push_back((*it).first);
            }
        }
        return keys;
    }

    // //print muy feo para debuggear,
    // supongo que en la version final va a volar.
    // void printHashMap(){
    //     for(int i=0; i < N_LETRAS; i++){
           
    //         printf("%d-esimaFila \n",i);
    //         for(Lista<entrada>::iterator it
    //                      = _listas[i].begin();
    //             it != _listas[i].end(); ++it){
    //             cout << "(" << (*it).first << ";"
    //                  << (*it).second << ")";
    //         }
    //         cout << endl;
    //     }
    // }

private:
    int hash(string key) {
        assert(key.size() > 0);
        return key[0] - 'a';
    }

    void lock(int letra) {
        pthread_mutex_lock(&_mtxs[letra]);
    }

    void unlock(int letra) {
        pthread_mutex_unlock(&_mtxs[letra]);
    }

    entrada *find (int letra, string key) {
        
        for (Lista<entrada>::iterator it = _listas[letra].begin();
             it != _listas[letra].end() ;
             ++it) {
            if ((*it).first == key)
                return &(*it);
        }
        // No encontramos ninguna entrada que tenga la key.
        return nullptr;
    }

    /**
       Devuelve la entrada correspondiente a la key si existe,
       y nullptr sino.
    */
    entrada* getEntrada(string key) {
        int letra = hash(key);
        return find(letra, key);
    }
};

entrada ConcurrentHashMap::maximum(unsigned int nt) {
    entrada maximo = entrada ("Nada", 0);
    pthread_mutex_t *max_mtx = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    // mutex para actualizar el maximo
    pthread_mutex_init (max_mtx, NULL);
    atomic<int> siguienteLetra;
    siguienteLetra.store(0,memory_order_relaxed);
    //SiguienteLetra se usa para decirle a cada thread en que posicion del arreglo debe
    //buscar
    struct argumentos *args = (argumentos*) malloc (sizeof(struct argumentos));
    args -> maximo = &maximo;
    args -> siguienteLetra = &siguienteLetra;
    args -> _listas = _listas;
    args -> max_mtx = max_mtx;

    for (int letra = 0; letra < N_LETRAS; letra++) {
        lock(letra);
    }
    pthread_t thread[nt];
    for (int i = 0; i < nt; i++) {
        pthread_create(&thread[i], NULL, (void* (*)(void*))find_max , args);
    }
    for (int j = 0; j < nt; j++){
        pthread_join(thread[j], NULL);
    }
    for (int letra = 0; letra < N_LETRAS; letra++) {
        unlock(letra);
    }

    free(args);
    pthread_mutex_destroy(max_mtx);
    free(max_mtx);
    return maximo;
}

inline int fetch_next(argumentos * a) {
    return a -> siguienteLetra ->fetch_add(1, memory_order_relaxed);
}


void *find_max(struct argumentos *args){
    int i;
    while((i = fetch_next(args)) < N_LETRAS){
        //observar que siguienteLetra realiza un add atomica, luego no va a pasar
        //que dos threads se queden con el mismo indice i.
        //Lista<entrada>::iterator it = args -> _listas[i].CrearIt();
        Lista<entrada>::iterator it = args -> _listas[i].begin();
        Lista<entrada>::iterator it_end = args -> _listas[i].end();
        for (; it != it_end; ++it) {
            if ((*it).second > args->maximo->second){
                //para actualizar maximo necesito acceso exclusivo
                pthread_mutex_lock(args -> max_mtx);
                //tengo que preguntar otra vez, porque posiblemente desde que entre
                //al primer if hasta que logre el acceso exclusivo alguien actualizo
                //maximo con un valor que es mejor que el candidato a maximo que yo
                //habia encontrado.
                if((*it).second > args->maximo->second){
                    *(args->maximo) = (*it);
                }
                pthread_mutex_unlock(args -> max_mtx);
            }
        }
    }
    pthread_exit((void*) 0);
}


void ConcurrentHashMap::concat(ConcurrentHashMap& other) {
    for (auto key : other.getKeys()) 
        for (int j = 0; j < other.get(key); j++) 
            addAndInc(key);
}

void ConcurrentHashMap::add_words(std::ifstream& file) {
    std::string word;
    while (file >> word) 
        addAndInc(word);
}

#endif /*_CONCURRENT_HASH_MAP_H_*/
