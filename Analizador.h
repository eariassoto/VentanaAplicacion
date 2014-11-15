#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include "ArbolAnalisis.h"
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
static const char IF_ELSE= 'F';

class Analizador
{
public:
    Analizador();
    ~Analizador();


    void analizarCodigo(const char*);
    char actualizarActual(char actual,int contadorLlaves,bool estoyRestando, char idPadre);

    string conseguirHileraIf_Else(string hilera,int indice);
    string conseguirHileraClase (string,int);
    string conseguirHileraMetodo(string,int);
    string conseguirHileraCiclo (string,int);
    string conseguirHileraAtributo(string,int);
    string conseguirHileraLinea_Llamado(string, int);

    void imprimirArbol(Nodo*);

    //agregado emma
    ArbolAnalisis obtenerArbol();
    string generarAnalisis();
    string analizarAtributosMetodos(Nodo*);
    string analizarProfundidadCodigo();
    string analizarMaximoAnidamiento(Nodo*);
    string analizarMetodosMorfosis(Nodo*);

    /**
    agregado maria
    */

    string usoAtributosMetodos(Nodo*);
    string conseguirUltimaParte(string);
    string usoAtributosTotal(Nodo*);
    int nodosUsanAtributos(ArbolAnalisis, Nodo*);
    string frecuenciaUsoMetodos(Nodo*);

    /**
    EXTRA
    */

    string metodosRecursivos(Nodo*);
    string metodosConHerencia(Nodo*);
    
    /**
    Metodo misterioso
    */

    string complejidadMetodos(Nodo*);
    
private:
    ArbolAnalisis arbolAnalizador;
};

#endif // ANALIZADOR_H
