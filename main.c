#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SistemaVotacion {
    struct NodoElectoral *elecciones;
    char convocatoria[1000];  
    struct Fecha FechaInicioCampana;
    struct Fecha FechaVotacion;
};


struct NodoElectoral {
    struct Elecciones *Elecciones;
    struct NodoElectoral *sig;
};

struct Elecciones {
    int NunmeroVuelta[1];
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
};

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
    struct Votante *votantes;
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

struct Fecha {
    int dia;
    int mes;
    int anio;
};



//FUNCIONES SISTEMA VOTACIONES 
struct SistemaVotacion *NuevaVotacion() {
    struct SistemaVotacion *Nueva;

    Nueva = malloc(sizeof(struct SistemaVotacion));
    if (Nueva == NULL)
        return NULL;

    Nueva->elecciones = NULL;

    Nueva->convocatoria[0] = '\0';

    Nueva->FechaInicioCampana.dia = 0;
    Nueva->FechaInicioCampana.mes = 0;
    Nueva->FechaInicioCampana.anio = 0;

    Nueva->FechaVotacion.dia = 0;
    Nueva->FechaVotacion.mes = 0;
    Nueva->FechaVotacion.anio = 0;

    return Nueva;
};

void IngresarDatosVotacion(struct SistemaVotacion *sistema) {
    printf("Ingrese mensaje de convocatoria:\n");
    scanf(" %[^\n]", sistema->convocatoria);  

    printf("Ingrese fecha inicio campaña (dia mes año): ");
    scanf("%d %d %d", 
        &sistema->FechaInicioCampana.dia,
        &sistema->FechaInicioCampana.mes,
        &sistema->FechaInicioCampana.anio
    );

    printf("Ingrese fecha de votación (dia mes año): ");
    scanf("%d %d %d", 
        &sistema->FechaVotacion.dia,
        &sistema->FechaVotacion.mes,
        &sistema->FechaVotacion.anio
    );
}







//propuesta de structs con cambios
//con variables de nombre distinto

struct SistemaVotacion 
{
    struct NodoEleccion *elecciones;
    char   *convocatoria;            //la convocatoria tiene el nombre de lo que se va a realizar
    struct Fecha registroCandidaturas;    //se agrega la fecha del registro
    struct Fecha FechaInicioCampana;
    struct Fecha FechaVotacion;
};

struct Fecha 
{
    int dia;
    int mes;
    int anio;
};

struct NodoEleccion 
{
    struct Eleccion *datosEleccion;
    struct NodoEleccion *sig;
};

struct Eleccion 
{
    int NumeroVuelta;          //es un entero no un arreglo
    struct TodosCandidatos *listaCandidatos;
    struct NodoMesa *listaMesas;
};

struct TodosCandidatos 
{
    struct Candidato **Candidatos;    //** porque es un arreglo de punteros a candidatos
    int totalCandidatos;            //se agrega el largo del array
};

struct Candidato
{
    char Rut[15];                //el rut es un char
    char *NombreCandidato;
    char Nacionalidad[25];
    int  edad;                  //edad es un numero
    char *PartidoPolitico;
    char *ProgramaGobierno;
    int  delitos;                //variable para confirmar si tiene delitos o no
};

struct NodoMesa
{
    struct Mesa *datosMesa;
    struct NodoMesa *sig;
};

struct Vocales
{
    char *nombre;
    int edad;
    char rut[15];
};

struct NodoVocal
{
    struct Vocales *datosVocal;
    struct NodoVocal *sig;
};

struct Mesa
{
    struct NodoVocal *listaVocales;          //lista interna que contiene los vocales de la mesa, porque pueden haber varios
    struct NodoVotante *votantes;  
};

 struct NodoVotante
 {
    struct Votante *datosVotante;
    struct NodoVotante *izq, *der;
};

struct Votante
{
    struct Candidato *voto;
    char *Nombre;
    int  Edad;               //edad es un numero
    char Nacionalidad[25];
    char rut[15];
    char paisResidencia[25];
};

//el padron mesa no va, porque corresponden a todos los votantes habilitados a votar, y esto es el arbol
//uso de char estaticos donde el tamaño varia mucho y no se conoce
//usar strlen para calcular el tamaño exacto del ingreso dinamico al agregar, se escanenan con auxiliares antes de todo
