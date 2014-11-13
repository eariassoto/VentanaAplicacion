#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include "ArbolN.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
static const char CLASE='C';
static const char ATRIBUTO='A';
static const char METODO='M';
static const char CICLO='B';
static const char INSTRUCCION='I';
static const char LLAMADO_METODO='L';
class Analizador
{
public:
    Analizador();
    ~Analizador();
    ArbolN arbolAnalizador;

    void analizarCodigo(const char*);
    char actualizarActual(char, int);

    string conseguirHileraClase (string,int);
    string conseguirHileraMetodo(string,int);
    string conseguirHileraCiclo (string,int);
    string conseguirHileraAtributo(string,int);
    string conseguirHileraLinea_Llamado(string, int);

    Nodo* agregarClase_Atributo(pair<char,string>);

    void imprimirArbol(Nodo*);


protected:
private:
};

#endif // ANALIZADOR_H
