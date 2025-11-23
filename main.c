#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*solo comentarios asi en turbo C*/

struct SistemaVotacion 
{
    struct NodoEleccion *elecciones;
    char *convocatoria;            
    struct Fecha registroCandidaturas;    
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
    int NumeroVuelta;          
    struct TodosCandidatos *listaCandidatos;
    struct NodoMesa *listaMesas;
};

struct TodosCandidatos 
{
    struct Candidato **Candidatos;    //** porque es un arreglo de punteros a candidatos
    int totalCandidatos;            
};

struct Candidato
{
    char Rut[15];                
    char *NombreCandidato;
    char Nacionalidad[25];
    int edad;                  
    char *PartidoPolitico;
    char *ProgramaGobierno;
    int delitos;                //variable para confirmar si tiene delitos o no
};

struct NodoMesa
{
    struct Mesa *datosMesa;
    struct NodoMesa *sig;
};

//los struct Vocales y NodoVocal no estan en el dibujo, son extras, aunque no se si se puede hacer
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
    int idVotante;
    struct Votante *datosVotante;
    struct NodoVotante *izq, *der;
};

struct Votante
{
    struct Candidato *voto;
    char *Nombre;
    int edad;               
    char Nacionalidad[25];
    char rut[15];
    char paisResidencia[25];
};


//usar strlen para calcular el tamaño exacto del ingreso dinamico al agregar, se escanenan con auxiliares antes de todo

//SIStema votacion 

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

//estos creados son los modelos vacios de cada estructura, listos para recibir datos

//retorno un puntero que apunta a ese nuevo nodo creado, por lo que despues lo puedo pasar para ingresar datos sin recorrer
struct NodoEleccion *nuevoNodoEleccion()   //no estoy modificando nada, estoy agregando
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


void agregarNodoEleccion(struct SistemaVotacion *sistema, struct NodoEleccion *nodo)
{
    struct NodoEleccion *rec;
    //esto va en su propia funcion para insertar elecciones
    if (sistema->elecciones == NULL)
    {
        sistema->elecciones = nodo;
    }
    else
    {
        rec = sistema->elecciones;
        while (rec->sig != NULL)     //con esto se detiene en el ultimo nodo
        {
            rec = rec->sig;    //va aqui, para llegar al final y luego insertarlo
        }
        rec->sig = nodo;
    }
}

//FUNCIONES CANDIDATO 

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
    
    nuevo->rut[0] = '\0';
    nuevo->NombreCandidato = NULL;
    nuevo->nacionalidad[0] = '\0';
    nuevo->edad = 0;
    nuevo->PartidoPolitico = NULL;
    nuevo->ProgramaGobierno = NULL;
    nuevo->delitos = 0;
    
    return nuevo;
}

int contadorParaCandidatos()
{
    int edad, delito, contador = 0, bandera;
    char nacionalidad[25];
    
    while (1)
    {
        printf("Ingrese edad del candidato");
        scanf("%d", &edad);
        if (edad >= 35)
        {
            printf("ingrese nacionalidad del candidato");
            scanf(" %[^\n]", nacionalidad);
            
            if (strcmp(nacionalidad, "Chile") == 0 || strcmp(nacionalidad, "Chilena") == 0)   //y si lo ingresa con mayusculas en medio??
            {
                printf("Ingrese un 1 si el candidato no cuenta con antecedentes");
                scanf("%d", &delito);
                
                if (delito == 1)
                {
                    contador += 1;
                    printf("Su candidato ha sido aceptado");
                }
            }
        }
        printf("Su candidato no cumple con las condiciones para postularse");
        printf("Ingrese un 0 si no desea agregar mas candidatos");
        scanf("%d", &bandera);
        if (bandera == 0)
        {
            return contador;
        }
    }
}
//previo a esto, confirmar si un candidato puede entrar o no a la lista
void arregloFijo(struct TodosCandidatos *arreglo, int tamano)
{
    int i;
    
    arreglo->Candidatos = (struct Candidato **) malloc (tamano * sizeof(struct Candidato *));
    arreglo->totalCandidatos = tamano;
    
    for (i = 0; i < tamano; i++)
    {
        arreglo->Candidatos[i] = crearCandidato();   //le doy espacios vacios a donde se ingresan los datos
    }
    
}

void ingresoDeDatosCandidatos(struct Candidato *nodo)
{
    
}


//FUNCIONES DE MESA 

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

void agregarNodoMesa(struct Eleccion *eleccion, struct NodoMesa *nuevo)
{
    struct NodoMesa *rec;
    
    if (eleccion->listaMesas == NULL)
    {
        eleccion->listaMesas = nuevo;
    }
    else
    {
        rec = eleccion->listaMesas;
        while (rec->sig != NULL)
        {
            rec = rec->sig;
        }
        rec->sig = nuevo;
    }
}


//FUNCIONES VOTANTE 

struct NodoVotante *nuevoNodoVotante()
{
    struct NodoVotante *nuevo;
    nuevo = (struct NodoVotante *) malloc (sizeof(struct NodoVotante));
    nuevo->idVotante = 0;
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
    nuevo->nacionalidad[0] = '\0';
    nuevo->rut[0] = '\0';
    nuevo->paisResidencia[0] = '\0';
    return nuevo;
}


//datos para el sistema
void ingresoDeDatos(struct SistemaVotacion *sistema) 
{
    //para usarlo como auxiliar y no desperdiciar memoria cuando quede todo guardado. este auxiliar se destruye al salir de la funcion
    char linea[200];
    
    printf("Ingrese el nombre de la convocatoria:\n");
    scanf(" %[^\n]", linea);    //esto no compila en turbo C
    
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



void menuDeIngresoDeDatos(struct SistemaVotacion *sistema)
{
    int numero, contadorParaCandidatos, i;
    struct NodoEleccion *nodoNuevoEleccion;   //puntero a ese nodo que voy a agregar, el creado en 0
    struct Eleccion *nuevaEleccion;
    struct TodosCandidatos *nuevoArreglo;
    struct nodoMesa *nuevoNodoMesa;
    struct Mesa *nuevaMesa;
    struct NodoVocal *nuevoNodoVocal;
    struct Vocales *nuevoVocal;
    struct NodoVotante *nuevoNodoVotante;
    struct Votante *nuevoVotante;
    
    
    //considerar que el arreglo de candidatos debe estar definido desde antes del escrutino, de modo que permita el ingreso de datos, pero luego no cambie mas (a menos que se elimine algo)    
    
    //estos serian los agregar en el fondo. los iniciales, despues en la segunda parte se puede agregar mas, junto a quitar, mostrar, ...
    while (1)
    {
        printf("Ingreso de los datos previo a las votaciones\n");
        printf("1. Ingreso de una nueva eleccion\n");
        printf("2. Ingreso de candidatos\n");
        printf("3. Ingreso de mesas\n");
        printf("5. Ingreso de votantes\n");
        printf("0. Finalizar el ingreso de datos para su elección\n");
        
        scanf("%d", &numero);
        switch (numero)    
        {
            //considerar primer caso y los siguentes de las estructuras, porque se une en tiempo de ejecucion, no en una estructura base
            //considerar en caso de que una opcion ya se haya agregado y no se pueda modificar, la nueva eleccion por ejemplo
            
            case 1:
                nodoNuevoEleccion = nuevoNodoEleccion();   //esto crea la lista eleccion, esto tiene solo punteros, por eso no tiene un ingreso de datos
                
                nuevaEleccion = crearEleccion();
                ingresoDeDatosEleccion(nuevaEleccion);
                nodoNuevoEleccion->datosEleccion = nuevaEleccion;
                agregarNodoEleccion(sistema, nodoNuevoEleccion);   //para unir al sistema en caso de no haber nada o agregar a la lista existente
                printf("Se agrego una nueva elección\n");
                break;
                
            case 2:
                if (nuevaEleccion == NULL)
                {
                    printf("Error: se debe crear una nueva elección previamente\n");
                    break;
                }
                nuevoArreglo = crearArregloCandidatos();     //estructura que contiene los datos vacios
                nuevaEleccion->listaCandidatos = nuevoArreglo;
                
                contadorParaCandidatos = contarCuantosSeran();  //para confirmar si el candidato cumple con los requisitos o no (al agregar uno nuevo)
                if (contadorParaCandidatos > 0)
                {
                    //se generan los candidatos que componen el arreglo, junto al tamaño del arreglo en si, porque el modelo se genero antes en crearArreglo
                    arregloFijo(nuevaEleccion->listaCandidatos, contadorParaCandidatos);
                    
                    for (i = 0; i < contadorParaCandidatos; i++)
                    {
                        ingresoDeDatosCandidatos(nuevoArreglo->Candidatos[i]);  //aqui se hace el ingreso de datos
                    }
                }
                break;
                
            case 3:
                if (nuevaEleccion == NULL)
                {
                    printf("Error: se debe crear una nueva elección previamente\n");
                    break;
                }
                nuevoNodoMesa = crearNodoMesa();
                nuevaMesa = crearMesa();
                
                ingresoDeDatosMesa(nuevaMesa);
                nuevoNodoMesa->datosMesa = nuevaMesa;
                agregarNodoMesa(nuevaEleccion, nuevoNodoMesa);
                break;
                
            case 4:
                if (nuevaMesa == NULL)
                {
                    printf("Error: se debe crear una mesa previamente\n");
                    break;
                }
                nuevoNodoVocal = crearNodoVocal();
                nuevoVocal = crearVocal();
                ingresoDeDatosVocal(nuevoVocal);
                nuevoNodoVocal->datosVocal = nuevoVocal;
                agregarNodoVocal(nuevaMesa, nuevoNodoVocal);
                break;
            
            case 5:
                if (nuevaMesa == NULL)
                {
                    printf("Error: se debe crear una nueva mesa previamente\n");
                    break;
                }
                nuevoNodoVotante = crearNodoVotante();
                nuevoVotante = crearVotante();
                ingresoDeDatosVotante(nuevoVotante);
                nuevoNodoVotante->datosVotante = nuevoVotante;
                agregarNodoVotante(nuevaMesa->votantes, nuevoNodoVotante);
                break;
                
            case 0:
                printf("Ha finalizado el ingreso de sus datos\n");
                return;    //no se si funciona en turbo C
            
            default:
                printf("Número invalido\n");
                break;
        }    
    }
}

void menuModificacionDeDatos(struct SistemaVotacion *sistema)
{
    //TODAS ESTAS OPCIONES PARA MANIPULAR DATOS
    
    /*printf("si la eleccion es nueva, ingrese el numero \n");
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
    printf("si necesita mostrar los datos de un votante, ingrese el numero \n");*/
}

void menuOperaciones(struct SistemaVotacion *sistema)
{
    //AQUI OPCIONES PARA OPERACIONES DEL SISTEMA (CONTEO DE VOTOS POR EJ.)
}





//el switch ingresa un dato ingresado por el ususario y segun lo que quiera hace la funcion que necesita

int main()
{
    struct SistemaVotacion *sistema;
    //creo primero una estructura por una de forma independiente para luego unir en tiempo de ejecucion a medida que el usuario ingrese informacion
    
    printf("Bienvenido al sistema de votaciones de SERVEL\n");
    printf("Para comenzar, ingrese los siguentes datos que identifiquen al sistema de votaciones\n");
    sistema = nuevoSistema();
    if (sistema == NULL) printf("No se pudo crear el sistema") return 1;
    ingresoDeDatos(sistema);  //aqui por ejemplo hay un ingreso de datos (del sistema general asi que se hace una sola vez, iniciado el sistema, solo este caso)

    //posteriormente ingreso datos (solicitar al ususario)
    //se divide el menu en fases (funciones), primero para el ingreso de datos iniciales (agregado inicial) y creacion del sistema (antes de la votacion), y luego para su modificacion
    menuDeIngresoDeDatos(sistema);
    menuModificacionDeDatos(sistema);
    menuOperaciones(sistema);
    
    return 0;
}
