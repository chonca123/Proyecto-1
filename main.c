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
    char *convocatoria;            //la convocatoria tiene el nombre de lo que se va a realizar
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
    int delitos;                //variable para confirmar si tiene delitos o no
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

//usar strlen para calcular el tamaño exacto del ingreso dinamico al agregar, se escanenan con auxiliares antes de todo


struct SistemaVotacion *nuevoSistema() 
{
    struct SistemaVotacion *nueva;
    
    //el malloc esta bien porque se devuelve un *, si estuviera en el main, no seria necesario, al igual que si estuviera como * en el main, ahi tambien se usa malloc
    //junto a su uso en los nodos
    nueva = (struct SistemaVotacion *) malloc (sizeof(struct SistemaVotacion));
    printf("Sistema iniciado con valores en 0\n");
    nueva->elecciones = NULL;
    nueva->convocatoria = NULL;

    nueva->registroCandidaturas.dia = 0;
    nueva->registroCandidaturas.mes = 0;
    nueva->registroCandidaturas.anio = 0;

    nueva->FechaInicioCampana.dia = 0;
    nueva->FechaInicioCampana.mes = 0;
    nueva->FechaInicioCampana.anio = 0;

    nueva->FechaVotacion.dia = 0;
    nueva->FechaVotacion.mes = 0;
    nueva->FechaVotacion.anio = 0;

    return nueva;
}

//estos creados son solo modelos sobre los que yo a futuro puedo generar estructuras como las listas o los arreglos

//para crear un nuevo nodo de la lista eleccion
//retorno un puntero que apunta a ese nuevo nodo creado, por lo que despues lo puedo pasar para ingresar datos sin recorrer
struct NodoEleccion *nuevoNodoEleccion(struct SistemaVotacion *sistema)   //no estoy modificando nada, estoy agregando
{
    struct NodoEleccion *nuevo;
    
    nuevo = (struct NodoEleccion *) malloc (sizeof(struct NodoEleccion));
    nuevo->datosEleccion = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

struct Eleccion *crearEleccion()
{
    struct Eleccion *nuevo;
    
    nuevo = (struct Eleccion *) malloc (sizeof(struct Eleccion));
    nuevo->NumeroVuelta = 0;
    nuevo->listaCandidatos = NULL;
    nuevo->listaMesas = NULL;
    
    return nuevo;
}

struct TodosCandidatos *crearArregloCandidatos()
{
    struct TodosCandidatos *nuevo;
    
    nuevo = (struct TodosCandidatos *) malloc (sizeof(struct TodosCandidatos));   //creo un struct que mas adelante contendra un arreglo
    nuevo->Candidatos = NULL;      //no tengo el arreglo todavia
    nuevo->totalCandidatos = 0;
    
    return nuevo;
}

struct Candidato *crearCandidato()
{
    struct Candidato *nuevo;
    
    nuevo = (struct Candidato *) malloc (sizeof(struct Candidato));
    
    nuevo->NombreCandidato = NULL;
    nuevo->edad = 0;
    nuevo->PartidoPolitico = NULL;
    nuevo->ProgramaGobierno = NULL;
    nuevo->delitos = 0;
    
    return nuevo;
}

struct NodoMesa *crearNodoMesa()
{
    struct NodoMesa *nuevo;
    
    nuevo = (struct NodoMesa *) malloc (sizeof(struct NodoMesa));
    nuevo->datosMesa = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

struct Mesa *crearMesa()
{
    struct Mesa *nuevo;
    
    nuevo = (struct Mesa *) malloc (sizeof(structMesa));
    nuevo->listaVocales = NULL;
    nuevo->votantes = NULL;
    return nuevo;
}

struct NodoVocal *crearNodoVocal()
{
    struct NodoVocal *nuevo;
    nuevo = (struct NodoVocal *) malloc (sizeof(struct NodoVocal));
    nuevo->datosVocal = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

struct Vocales *crearVocal()
{
    struct Vocales *nuevo;
    nuevo = (struct Vocales *) malloc (sizeof(struct Vocales));
    nuevo->nombre = NULL;
    nuevo->edad = 0;
    return nuevo;
}

struct NodoVotante *nuevoNodoVotante()
{
    struct NodoVotante *nuevo;
    nuevo = (struct NodoVotante *) malloc (sizeof(struct NodoVotante));
    nuevo->datosVotante = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

struct Votante *crearVotante()
{
    struct Votante *nuevo;
    nuevo = (struct Votante *) malloc (sizeof(struct Votante));
    nuevo->voto = NULL;
    nuevo->Nombre = NULL;
    nuevo->edad = 0;
    return nuevo;
}











//esto va en su propia funcion para insertar elecciones
if (sistema->elecciones == NULL)
    {
        sistema->elecciones = nuevo;
    }
    else
    {
        rec = sistema->elecciones;
        while (rec->sig != NULL)     //con esto se detiene en el ultimo nodo
        {
            rec = rec->sig;    //va aqui, para llegar al final y luego insertarlo
        }
        rec->sig = nuevo;
    }
    return nuevo;






//datos para el sistema
void ingresoDeDatos(struct SistemaVotacion *sistema) 
{
    //para usarlo como auxiliar y no desperdiciar memoria cuando quede todo guardado. este auxiliar se destruye al salir de la funcion
    char linea[200];
    
    printf("Ingrese el nombre de la convocatoria:\n");
    scanf(" %[^\n]", linea);
    
    sistema->convocatoria = (char *) malloc ((strlen(linea) + 1) * sizeof(char));
    strcpy(sistema->convocatoria, linea);
    
    printf("Ingrese fecha del registro de la candidatura (dia, mes y año)\n");
    scanf("%d %d %d", &sistema->registroCandidaturas.dia, &sistema->registroCandidaturas.mes, &sistema->registroCandidaturas.anio);

    printf("Ingrese fecha inicio campaña (dia, mes y año): \n");
    scanf("%d %d %d", &sistema->FechaInicioCampana.dia, &sistema->FechaInicioCampana.mes, &sistema->FechaInicioCampana.anio);

    printf("Ingrese fecha de votación (dia, mes y año): \n");
    scanf("%d %d %d", &sistema->FechaVotacion.dia, &sistema->FechaVotacion.mes, &sistema->FechaVotacion.anio);
}


//al ingresar datos yo puedo decir que cree una estructura (ingreso de datos en tiempo de ejecucion)










//el switch ingresa un dato ingresado por el ususario y segun lo que quiera hace la funcion que necesita

int main()
{
    struct SistemaVotacion *sistema;
    struct NodoEleccion *nodoNuevoEleccion;   //puntero a ese nodo que voy a agregar, el creado en 0
    struct Eleccion *nuevaEleccion;
    struct TodosCandidatos *nuevoArreglo;
    struct Candidato *nuevoCandidato;
    struct nodoMesa *nuevoNodoMesa;
    struct Mesa *nuevaMesa;
    struct NodoVocal *nuevoNodoVocal;
    struct Vocales *nuevoVocal;
    struct NodoVotante *nuevoNodoVotante;
    struct Votante *nuevoVotante;
    
    
    
    int numero;
    
    //usar while para un menu que se repite
    //considerar que el arreglo de candidatos debe estar definido desde antes del escrutino, de modo que permita el ingreso de datos, pero luego no cambie mas (a menos que se elimine algo)
    //para esto, se divide el menu por fases, primero todo lo que va antes de la votacion, y luego todo lo que pueda ocurrir al momento y despues
    
    
    
    //creo primero una estructura por una de forma independiente para luego unir
    
    
    sistema = nuevoSistema();
    if (sistema == NULL)
    {
        printf("No se pudo crear el sistema");
        return 1;
    }
    ingresoDeDatos(sistema);  //aqui por ejemplo hay un ingreso de datos
    
    
    
    
    
    
    
    nodoNuevoEleccion = nuevoNodoEleccion(sistema);    //primero le doy memoria con malloc y lo dejo con datos en 0 o NULL, ademas de asignarlo a la estructura
    nuevaEleccion = crearEleccion();   //esto crea y deja los valores en 0, despues se ingresan datos
    nuevoArreglo = crearArregloCandidatos();     //estructura que contiene un arreglo
    nuevoCandidato = crearCandidato();
    nuevoNodoMesa = crearNodoMesa();
    nuevaMesa = crearMesa();
    nuevoNodoVocal = crearNodoVocal();
    nuevoVocal = crearVocal();
    nuevoNodoVotante = crearNodoVotante();
    nuevoVotante = crearVotante();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //se puede dejar el menu en una funcion, o dividirlo en funciones (las fases del menu)
    printf("Bienvenido a este programa de sistema de votaciones\n");
    printf("si la eleccion es nueva, ingrese el numero \n");
    printf("si necesita eliminar una eleccion, ingrese el numero \n");
    printf("si necesita buscar una eleccion, ingrese el numero \n");
    printf("si necesita modificar una eleccion, ingrese el numero \n");
    printf("si necesita mostrar los datos de una eleccion, ingrese el numero \n");
    printf("si necesita agregar un candidato, ingrese el numero \n");
    printf("si necesita eliminar un candidato, ingrese el numero \n");
    printf("si necesita buscar un candidato, ingrese el numero \n");
    printf("si necesita modificar un candidato, ingrese el numero \n");
    printf("si necesita mostrar los datos de un candidato, ingrese el numero \n");
    printf("si necesita agregar una mesa, ingrese el numero \n");
    printf("si necesita eliminar una mesa, ingrese el numero \n");
    printf("si necesita buscar una mesa, ingrese el numero \n");
    printf("si necesita modificar una mesa, ingrese el numero \n");
    printf("si necesita mostrar los datos de una mesa, ingrese el numero \n");
    printf("si necesita agregar un votante, ingrese el numero \n");
    printf("si necesita eliminar un votante, ingrese el numero \n");
    printf("si necesita buscar un votante, ingrese el numero \n");
    printf("si necesita modificar un votante, ingrese el numero \n");
    printf("si necesita mostrar los datos de un votante, ingrese el numero \n");
    
    
    //aqui van funciones con finalidad (calcular ganancia por ejemplo, minimo 2)
    printf("");
    printf("");
    printf("");
    
    
    scanf("%d", &numero);
    
    switch (numero)    //aqui va lo que ingresa el ususario
    {
        case 1:
            break;
        
        case 2:
            break;
        
        case 3:
            break;
            
        case 4:
            break;
        
        default:
            break;      //si se puede el break
        
    }
    return 0;
}
