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
    

    void analizarCodigo(const char*);
    char actualizarActual(char, int);

    string conseguirHileraClase (string,int);
    string conseguirHileraMetodo(string,int);
    string conseguirHileraCiclo (string,int);
    string conseguirHileraAtributo(string,int);
    string conseguirHileraLinea_Llamado(string, int);

    Nodo* agregarClase_Atributo(pair<char,string>);

    void imprimirArbol(Nodo*);
    
    //agregado emma
    ArbolN obtenerArbol();
    string generarAnalisis();
    string analizarAtributosMetodos(Nodo*);
    string analizarProfundidadCodigo();
    string analizarMaximoAnidamiento(Nodo*);

private:
    ArbolN arbolAnalizador;
};

#endif // ANALIZADOR_H
