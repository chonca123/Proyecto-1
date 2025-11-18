#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SistemaVotacion {
    struct NodoEleccion *Eleccionee;
    char convocatoria[1000];
    int FechaInicioCampana[12];
    int FechaVotacion[12];
};

struct NodoElectoral {
    struct Elecciones *Elecciones;
    struct NodoElectoral *sig;
};

struct Elecciones {
    struct TodosCandidatos *Candidatos;
    struct NodoMesa *ant;
};

struct TodosCandidatos {
    struct Candidato*Candidato;
};

struct Candidato{
    int Rut[12];
    char NombreCandidato[256];
    char Nacionalidad[25];
    int edad[3];
    char PartidoPolitico[50];
    char ProgramaGobierno[1000];
}

struct NodoMesa{
    struct Mesa*Mesa;
    struct NodoMesa*sig;
};

struct Mesa{
    char NombreVocales[216];
    int PadronMesa[20];
    struct NodoVotante*votantes;  
};

 struct NodoVotante{
    struct Votante;
    struct nodo_imputado *izq;
    struct nodo_imputado *der;
};

struct votante{
    struct Candidato*Candidatos;
    char Nombre[100];
    int Edad[3];
    char Nacionalidad[10];
    int RUT[10];
    char PadronMesa[20];
};
  
