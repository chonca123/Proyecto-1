#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha 
{
    int dia;
    int mes;
    int anio;
};

struct SistemaVotacion    
{
    struct NodoEleccion *elecciones;
    char *convocatoria;            
    struct Fecha registroCandidaturas;    
    struct Fecha FechaInicioCampana;
    struct Fecha FechaVotacion;
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
    struct Candidato **Candidatos;    
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
    int delitos;                
};

struct NodoMesa
{
    struct Mesa *datosMesa;
    struct NodoMesa *sig;
};

struct Mesa
{
    int PadronMesa;  
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


//FUNCIONES SISTEMA INICIAL

struct SistemaVotacion *nuevoSistema() 
{
    struct SistemaVotacion *nueva;
    
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


void agregarEleccion(struct SistemaVotacion *sistema)
{
    struct NodoEleccion *nuevoNodo;
    struct Eleccion *nuevaEleccion;

    nuevoNodo = nuevoNodoEleccion();
    nuevaEleccion = crearEleccion();

    if (nuevoNodo == NULL || nuevaEleccion == NULL)
    {
        printf("ERROR al crear la eleccion.\n");
        return;
    }

    printf("Ingrese numero de vuelta (1 o 2): ");
    scanf("%d", &nuevaEleccion->NumeroVuelta);
    getchar();

    nuevoNodo->datosEleccion = nuevaEleccion;
    agregarNodoEleccion(sistema, nuevoNodo);

    printf("Eleccion agregada correctamente.\n");
}

void listarElecciones(struct SistemaVotacion *sistema)
{
    struct NodoEleccion *rec = sistema->elecciones;

    if (rec == NULL)
    {
        printf("No hay elecciones registradas.\n");
        return;
    }

    printf("\n----- LISTA DE ELECCIONES -----\n");
    while (rec != NULL)
    {
        printf("Numero de vuelta: %d\n", rec->datosEleccion->NumeroVuelta);
        rec = rec->sig;
    }
}





//FUNCIONES DE MESA 

struct NodoMesa *crearNodoMesa()
{
    struct NodoMesa *nuevo;
    
    nuevo = (struct NodoMesa *) malloc (sizeof(struct NodoMesa));
    if (nuevo == NULL)
    {
        return NULL;
    }
    nuevo->datosMesa = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

struct Mesa *crearMesa()
{
    struct Mesa *nuevo;

    nuevo = (struct Mesa *) malloc(sizeof(struct Mesa));
    if (nuevo == NULL)
    {
        return NULL;
    }
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

void mensajeMesaAgregada()
{
    printf("La mesa fue agregada correctamente.\n");
}

void cargarDatosMesa(struct Mesa *mesa)
{
    printf("Ingrese el numero de padron de la mesa: ");
    scanf("%d", &mesa->PadronMesa);

    mesa->votantes = NULL;
}


void agregarMesa(struct Eleccion *eleccion)
{
    struct NodoMesa *nuevoNodo;
    struct Mesa *nuevaMesa;

    nuevoNodo = crearNodoMesa();
    if (nuevoNodo == NULL)
    {
        return;
    }
    
    nuevaMesa = crearMesa();
    if (nuevaMesa == NULL)
    {
        free(nuevoNodo);
        return;
    }

    cargarDatosMesa(nuevaMesa);

    nuevoNodo->datosMesa = nuevaMesa;

    agregarNodoMesa(eleccion, nuevoNodo);
    mensajeMesaAgregada();
}


struct Mesa *buscarMesa(struct Eleccion *eleccion, int numeroBuscado)
{
    struct NodoMesa *rec;

    rec = eleccion->listaMesas;

    while (rec != NULL)
    {
        if (rec->datosMesa->PadronMesa == numeroBuscado)
        {
            return rec->datosMesa;
        }

        rec = rec->sig;
    }

    return NULL;
}


void mostrarMesaEncontrada(struct Mesa *mesa)
{
    printf("----- MESA ENCONTRADA -----\n");
    printf("Numero de Padron: %d\n", mesa->PadronMesa);
    printf("Votantes: (se muestran en otra funcion)\n");
}

void mostrarMesaNoEncontrada()
{
    printf("No se encontro ninguna mesa con ese numero de padron.\n");
}

void mensajeMesaNoExiste()
{
    printf("No existe ninguna mesa con ese numero de padron.\n");
}

void mensajeMesaEliminada()
{
    printf("La mesa fue eliminada correctamente.\n");
}

int eliminarMesa(struct Eleccion *eleccion, int numeroBuscado)
{
    struct NodoMesa *rec;
    struct NodoMesa *ant;

    rec = eleccion->listaMesas;
    ant = NULL;

    while (rec != NULL)
    {
        if (rec->datosMesa->PadronMesa == numeroBuscado)
        {
            if (ant == NULL)
            {
                eleccion->listaMesas = rec->sig;
            }
            else
            {
                ant->sig = rec->sig;
            }

            free(rec->datosMesa);
            free(rec);

            mensajeMesaEliminada();
            return 1;
        }

        ant = rec;
        rec = rec->sig;
    }

    mensajeMesaNoExiste();
    return 0;
}


void listarMesas(struct Eleccion *eleccion)
{
    struct NodoMesa *rec;

    rec = eleccion->listaMesas;

    if (rec == NULL)
    {
        printf("No hay mesas registradas.\n");
        return;
    }

    printf("\n----- LISTA DE MESAS -----\n");
    while (rec != NULL)
    {
        printf("Mesa Padron: %d\n", rec->datosMesa->PadronMesa);
        rec = rec->sig;
    }
}

void menuMesa(struct Eleccion *eleccion) 
{
    int opcion, numero, nuevoNumero;
    struct Mesa *mesa;

    do 
    {
        printf("\n----- MENU MESAS -----\n");
        printf("1. Agregar Mesa\n");
        printf("2. Eliminar Mesa\n");
        printf("3. Buscar Mesa\n");
        printf("4. Modificar Mesa\n");
        printf("5. Listar Mesas\n");
        printf("0. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) 
        {
            case 1:
                printf("Ingrese el numero de padron de la nueva mesa: ");
                scanf("%d", &numero);
                getchar();

                if (buscarMesa(eleccion, numero) != NULL)
                {
                    printf("ERROR: Ya existe una mesa con ese numero.\n");
                }
                else
                {
                    agregarMesa(eleccion);
                }
                break;

            case 2:
                printf("Ingrese el numero de padron de la mesa a eliminar: ");
                scanf("%d", &numero);

                eliminarMesa(eleccion, numero);
                break;

            case 3:
                printf("Ingrese el numero de padron a buscar: ");
                scanf("%d", &numero);

                mesa = buscarMesa(eleccion, numero);

                if (mesa != NULL)
                {
                    mostrarMesaEncontrada(mesa);
                }
                else
                {
                    mostrarMesaNoEncontrada();
                }
                break;

            case 4:
                printf("Ingrese el numero actual de la mesa: ");
                scanf("%d", &numero);

                mesa = buscarMesa(eleccion, numero);

                if (mesa == NULL)
                {
                    printf("ERROR: La mesa no existe.\n");
                }
                else
                {
                    printf("Ingrese el nuevo numero de padron: ");
                    scanf("%d", &nuevoNumero);

                    if (buscarMesa(eleccion, nuevoNumero) != NULL)
                    {
                        printf("ERROR: Ese numero ya esta usado.\n");
                    }
                    else
                    {
                        mesa->PadronMesa = nuevoNumero;
                        printf("Modificacion exitosa.\n");
                    }
                }
                break;

            case 5:
                listarMesas(eleccion);
                break;

            case 0:
                printf("Regresando al menu principal\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 0);
}






void ingresoDeDatos(struct SistemaVotacion *sistema) 
{
    char linea[200];

    printf("Ingrese el nombre de la convocatoria:\n");
    fgets(linea, 200, stdin);                
    linea[strcspn(linea, "\n")] = '\0';        

    sistema->convocatoria = (char *) malloc((strlen(linea) + 1) * sizeof(char));
    if (sistema->convocatoria == NULL)
    {
        printf("ERROR: No se pudo reservar memoria para convocatoria.\n");
        return;
    }
    strcpy(sistema->convocatoria, linea);

    printf("Ingrese la fecha del registro de la candidatura (dia mes anio):\n");
    scanf("%d %d %d", &sistema->registroCandidaturas.dia, &sistema->registroCandidaturas.mes, &sistema->registroCandidaturas.anio);
    getchar();  // limpia el ENTER

    printf("Ingrese fecha de inicio de campaña (dia mes anio):\n");
    scanf("%d %d %d", &sistema->FechaInicioCampana.dia, &sistema->FechaInicioCampana.mes, &sistema->FechaInicioCampana.anio);
    getchar();

    printf("Ingrese fecha de votación (dia mes anio):\n");
    scanf("%d %d %d",&sistema->FechaVotacion.dia, &sistema->FechaVotacion.mes, &sistema->FechaVotacion.anio);
    getchar();

    printf("Datos del Sistema cargados correctamente.\n");
}





void ingresoDeDatosCandidatos(struct Candidato *espacio)
{
    char aux[200];

    printf("Ingrese el RUT del candidato:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(espacio->Rut, aux);

    printf("Ingrese el nombre del candidato:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    espacio->NombreCandidato = (char *) malloc ((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->NombreCandidato, aux);

    printf("Ingrese la nacionalidad del candidato:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(espacio->Nacionalidad, aux);

    printf("Ingrese la edad del candidato:\n");
    scanf("%d", &espacio->edad);
    getchar();   // limpia ENTER

    printf("Ingrese el partido político del candidato:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    espacio->PartidoPolitico = (char *) malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->PartidoPolitico, aux);

    printf("Ingrese el programa de gobierno:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    espacio->ProgramaGobierno = (char *) malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->ProgramaGobierno, aux);

    printf("¿Tiene antecedentes? (1 = SÍ / 0 = NO):\n");
    scanf("%d", &espacio->delitos);
    getchar();

    printf("\nCandidato cargado correctamente.\n");
}




void menuElecciones(struct SistemaVotacion *sistema)
{
    int opcion;

    do
    {
        printf("\n----- MENU ELECCIONES -----\n");
        printf("1. Agregar Eleccion\n");
        printf("2. Listar Elecciones\n");
        printf("0. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion)
        {
            case 1:
                agregarEleccion(sistema);   
                break;

            case 2:
                listarElecciones(sistema); 
                break;

            case 0:
                printf("Regresando al menu principal\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 0);
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
    
    nuevo->Rut[0] = '\0';
    nuevo->NombreCandidato = NULL;
    nuevo->Nacionalidad[0] = '\0';
    nuevo->edad = 0;
    nuevo->PartidoPolitico = NULL;
    nuevo->ProgramaGobierno = NULL;
    nuevo->delitos = 0;
    
    return nuevo;
}

void arregloFijo(struct TodosCandidatos *arreglo, int tamano)
{
    int i;
    
    arreglo->Candidatos = (struct Candidato **) malloc (tamano * sizeof(struct Candidato *));
    arreglo->totalCandidatos = tamano;
    
    for (i = 0; i < tamano; i++)
    {
        arreglo->Candidatos[i] = crearCandidato();  
    }
    
}


void agregarCandidato(struct TodosCandidatos *lista, int tamano)
{
    struct Candidato *nuevo;
    char aux[200];
    int edad, delitos;
    
    if (lista->totalCandidatos == tamano)
    {
        printf("No se pueden agregar mas candidatos.\n");
        return;
    }

    printf("Ingrese edad del candidato: ");
    scanf("%d", &edad);
    getchar();

    if (edad < 35)
    {
        printf("ERROR: Debe tener 35 años o más.\n");
        return;
    }

    printf("Ingrese nacionalidad del candidato: ");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';

    if (strcmp(aux, "Chile") != 0 && strcmp(aux, "Chilena") != 0)
    {
        printf("ERROR: Debe ser chileno de nacimiento.\n");
        return;
    }

    printf("¿Tiene antecedentes? (1=SI / 0=NO): ");
    scanf("%d", &delitos);
    getchar();

    if (delitos != 0)
    {
        printf("ERROR: No puede tener antecedentes.\n");
        return;
    }


    nuevo = lista->Candidatos[lista->totalCandidatos];
    nuevo->edad = edad;

    strcpy(nuevo->Nacionalidad, aux);

    printf("Ingrese nombre del candidato: ");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    nuevo->NombreCandidato = malloc(strlen(aux)+1);
    strcpy(nuevo->NombreCandidato, aux);

    printf("Ingrese partido político del candidato: ");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    nuevo->PartidoPolitico = malloc(strlen(aux)+1);
    strcpy(nuevo->PartidoPolitico, aux);

    printf("Ingrese programa de gobierno: ");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    nuevo->ProgramaGobierno = malloc(strlen(aux)+1);
    strcpy(nuevo->ProgramaGobierno, aux);

    lista->totalCandidatos++;
    printf("\nCandidato agregado correctamente.\n");
}



void buscarCandidato(struct TodosCandidatos *lista, char *rut, int largo)
{
    int i;
    
    for (i = 0; i < largo; i++)
    {
        if (lista->Candidatos[i] != NULL)
        {
            if (strcmp(lista->Candidatos[i]->Rut, rut) == 0)
            {
                printf("Rut del candidato: %s\n", lista->Candidatos[i]->Rut);
                printf("Nombre del candidato: %s\n", lista->Candidatos[i]->NombreCandidato);
                printf("Edad del candidato: %d\n", lista->Candidatos[i]->edad);
                printf("Partido politico del candidato: %s\n", lista->Candidatos[i]->PartidoPolitico);
                return;
            }
        }
    }
    printf("No se encontro ese candidato\n");
}

void compactarArreglo(struct TodosCandidatos *lista)
{
    int i, j = 0;

    for (i = 0; i < lista->totalCandidatos; i++)
    {
        if (lista->Candidatos[i] != NULL)
        {
            lista->Candidatos[j] = lista->Candidatos[i];
            j++;
        }
    }

    for (; j < lista->totalCandidatos; j++)
    {
        lista->Candidatos[j] = NULL;
    }
}

void eliminarCandidato(struct TodosCandidatos *lista, char *rut) 
{
    int i;
    
    for (i = 0; i < lista->totalCandidatos; i++)
    {
        if (lista->Candidatos[i] != NULL && strcmp(lista->Candidatos[i]->Rut, rut) == 0)
        {
            free(lista->Candidatos[i]->NombreCandidato);
            free(lista->Candidatos[i]->PartidoPolitico);
            free(lista->Candidatos[i]->ProgramaGobierno);
            free(lista->Candidatos[i]);  

            lista->Candidatos[i] = NULL;  
            printf("Candidato eliminado.\n");
            return;
        }
    }
    printf("No se encontró el candidato.\n");
}


void modificarCandidato(struct TodosCandidatos *lista, char *rut)
{
    int i;
    char aux[200];

    for (i = 0; i < lista->totalCandidatos; i++)
    {
        if (lista->Candidatos[i] != NULL && strcmp(lista->Candidatos[i]->Rut, rut) == 0)
        {
            printf("Ingrese nuevo nombre: ");
            fgets(aux, sizeof(aux), stdin);
            aux[strcspn(aux, "\n")] = '\0';

            if (lista->Candidatos[i]->NombreCandidato != NULL)
            {
                free(lista->Candidatos[i]->NombreCandidato);
            }

            lista->Candidatos[i]->NombreCandidato = (char *) malloc((strlen(aux) + 1) * sizeof (char));
            strcpy(lista->Candidatos[i]->NombreCandidato, aux);

            printf("Ingrese nueva edad: ");
            scanf("%d", &lista->Candidatos[i]->edad);
            getchar();

            printf("Candidato modificado correctamente.\n");
            return;
        }
    }
    printf("No se encontró ese candidato.\n");
}



void mostrarCandidato(struct TodosCandidatos *lista, int largo)
{
    int i;
    
    for (i = 0; i < largo; i++)
    {
        if (lista->Candidatos[i] != NULL)
        {
            if (lista->Candidatos[i]->Rut != NULL)
            {
                printf("Rut del candidato: %s\n", lista->Candidatos[i]->Rut);
                printf("Nombre del candidato: %s\n", lista->Candidatos[i]->NombreCandidato);
                printf("Nacionalidad del candidato: %s\n", lista->Candidatos[i]->Nacionalidad);
                printf("Edad del candidato: %d\n", lista->Candidatos[i]->edad);
                printf("Partido politico del candidato: %s\n", lista->Candidatos[i]->PartidoPolitico);
                printf("Programa de gobierno del candidato: %s\n", lista->Candidatos[i]->ProgramaGobierno);
            }
        }
    }
}


void menuCandidatos(struct TodosCandidatos *lista)
{
    int numero;
    char aux[15];
    
    do
    {
        printf("Usted accedió al menú candidatos\n");
        printf("Seleccione la opción que desee\n");
        printf("1. agregar un candidato\n");
        printf("2. buscar un candidato\n");
        printf("3. eliminar un candidato\n");
        printf("4. Modificar un candidato\n");
        printf("5. Mostrar la informacion de los candidatos\n");
        printf("0. Salir del menú candidatos\n");
        
        scanf("%d", &numero);
        getchar();
        
        switch (numero)
        {
            case 1:
                agregarCandidato(lista, lista->totalCandidatos);
                break;
                
            case 2:
                printf("Ingrese rut del candidato a buscar\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';
                buscarCandidato(lista, aux, lista->totalCandidatos);
                break;
                
            case 3:
                printf("Ingrese rut del candidato a eliminar\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';

                eliminarCandidato(lista, aux);   

                printf("¿Desea compactar el arreglo? (1=Sí / 0=No): ");
                scanf("%d", &numero);
                getchar();

                if (numero == 1)
                {
                    compactarArreglo(lista);
                    printf("Arreglo compactado correctamente.\n");
                }
                break;

            case 4:
                printf("Ingrese rut del candidato a modificar\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';
                modificarCandidato(lista, aux);
                break;
                
            case 5:
                mostrarCandidato(lista, lista->totalCandidatos);
                break;
                
            case 0:
                printf("Usted ha salido del menú candidatos\n");
                break;
                
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero != 0);
}

//FUNCIONES VOTANTES

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
    nuevo->Nacionalidad[0] = '\0';
    nuevo->rut[0] = '\0';
    nuevo->paisResidencia[0] = '\0';
    return nuevo;
}

void agregarNodoVotante(struct NodoVotante **raiz, struct NodoVotante *nuevo)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = nuevo;
        return;
    }
    else
    {
        if ((*raiz)->datosVotante->edad < nuevo->datosVotante->edad)
        {
            agregarNodoVotante(&(*raiz)->izq, nuevo);
        }
        else
        {
            agregarNodoVotante(&(*raiz)->der, nuevo);
        }
    }
}


void agregarVotante(struct NodoVotante **raiz)
{
    struct NodoVotante *nuevo;
    struct Votante *auxDatos;
    char aux[200];

    nuevo = nuevoNodoVotante();  
    auxDatos = crearVotante();   

    printf("Ingrese nombre del votante:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    auxDatos->Nombre = (char *) malloc((strlen(aux)+1) * sizeof(char));
    strcpy(auxDatos->Nombre, aux);

    printf("Ingrese edad del votante:\n");
    scanf("%d", &auxDatos->edad);
    getchar();

    printf("Ingrese nacionalidad del votante:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(auxDatos->Nacionalidad, aux);

    printf("Ingrese rut del votante:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(auxDatos->rut, aux);

    printf("Ingrese pais de residencia del votante:\n");
    fgets(aux, 200, stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(auxDatos->paisResidencia, aux);


    nuevo->datosVotante = auxDatos;
    agregarNodoVotante(raiz, nuevo);

    printf("Votante agregado correctamente.\n");
}


int buscarVotante(struct NodoVotante *raiz, char *rut)
{
    struct NodoVotante *izq, *der;
    
    if (raiz != NULL)
    {
        if (strcmp(raiz->datosVotante->rut, rut) == 0)
        {
            printf("Nombre votante: %s\n", raiz->datosVotante->Nombre);
            printf("Rut votante %s\n", raiz->datosVotante->rut);
            printf("Edad votante: %d\n", raiz->datosVotante->edad);
            printf("Nacionalidad votante: %s\n", raiz->datosVotante->Nacionalidad);
            printf("Pais de residencia del votante: %s\n", raiz->datosVotante->paisResidencia);
            return 1;
        }
        
        if (buscarVotante(raiz->izq, rut))
        {
            return 1;
        }

        return buscarVotante(raiz->der, rut);
    }
    return 0;
}

struct NodoVotante* eliminarVotante(struct NodoVotante *raiz, char *rut)
{
    struct NodoVotante *temp;
    
    if (raiz == NULL)
    {
        return NULL;
    }

    if (strcmp(raiz->datosVotante->rut, rut) == 0)
    {
        if (raiz->izq == NULL && raiz->der == NULL)
        {
            free(raiz->datosVotante->Nombre);   
            free(raiz->datosVotante);
            free(raiz);
            return NULL;
        }

        if (raiz->izq == NULL) {
            temp = raiz->der;
            free(raiz->datosVotante->Nombre);
            free(raiz->datosVotante);
            free(raiz);
            return temp;
        }
        if (raiz->der == NULL) {
            temp = raiz->izq;
            free(raiz->datosVotante->Nombre);
            free(raiz->datosVotante);
            free(raiz);
            return temp;
        }
        
        temp = raiz->der;
        while (temp->izq != NULL)
            temp = temp->izq;

        raiz->datosVotante->edad = temp->datosVotante->edad;
        strcpy(raiz->datosVotante->rut, temp->datosVotante->rut);
        strcpy(raiz->datosVotante->Nacionalidad, temp->datosVotante->Nacionalidad);
        strcpy(raiz->datosVotante->paisResidencia, temp->datosVotante->paisResidencia);
        strcpy(raiz->datosVotante->Nombre, temp->datosVotante->Nombre);

        raiz->der = eliminarVotante(raiz->der, temp->datosVotante->rut);
        return raiz;
    }

    raiz->izq = eliminarVotante(raiz->izq, rut);
    raiz->der = eliminarVotante(raiz->der, rut);
    return raiz;
}

struct NodoVotante* buscarNodoVotante(struct NodoVotante *raiz, char *rut)
{
    struct NodoVotante *aux;
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->datosVotante->rut, rut) == 0)
        return raiz;  

    aux = buscarNodoVotante(raiz->izq, rut);
    if (aux != NULL) 
    {
        return aux;
    }
    return buscarNodoVotante(raiz->der, rut);
}


void modificarVotante(struct NodoVotante *raiz, char *rut)
{
    struct NodoVotante *nodo;  // función que RETORNA el nodo
    char aux[200];


    nodo = buscarNodoVotante(raiz, rut);
    if (nodo == NULL) 
    {
        printf("No se encontró el votante\n");
        return;
    }

    printf("Ingrese nuevo nombre: ");
    fgets(aux, sizeof(aux), stdin);
    aux[strcspn(aux, "\n")] = '\0';

    free(nodo->datosVotante->Nombre);
    nodo->datosVotante->Nombre = malloc(strlen(aux)+1);
    strcpy(nodo->datosVotante->Nombre, aux);

    printf("Ingrese nueva edad: ");
    scanf("%d", &nodo->datosVotante->edad);
    getchar();

    printf("Ingrese nueva nacionalidad: ");
    fgets(aux, sizeof(aux), stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(nodo->datosVotante->Nacionalidad, aux);

    printf("Ingrese nuevo país de residencia: ");
    fgets(aux, sizeof(aux), stdin);
    aux[strcspn(aux, "\n")] = '\0';
    strcpy(nodo->datosVotante->paisResidencia, aux);

    printf("Datos modificados correctamente.\n");
}


void mostrarVotantes(struct NodoVotante *raiz)
{
    if (raiz != NULL)
    {
        mostrarVotantes(raiz->izq);
        printf("Nombre votante: %s\n", raiz->datosVotante->Nombre);
        printf("Rut votante %s\n", raiz->datosVotante->rut);
        printf("Edad votante: %d\n", raiz->datosVotante->edad);
        printf("Nacionalidad votante: %s\n", raiz->datosVotante->Nacionalidad);
        printf("Pais de residencia del votante: %s\n", raiz->datosVotante->paisResidencia);
        mostrarVotantes(raiz->der);
    }
    else
    {
        printf("No hay votantes registrados\n");
    }
}

void menuVotantes(struct Mesa *mesa)
{
    int numero;
    char aux[15];
    
    do
    {
        printf("Usted accedió al menú votantes\n");
        printf("Seleccione la opción que desee\n");
        printf("1. agregar un votante\n");
        printf("2. buscar un votante\n");
        printf("3. eliminar un votante\n");
        printf("4. Modificar un votante\n");
        printf("5. Mostrar la informacion de los votantes\n");
        printf("0. Salir del menú votantes\n");
        
        scanf("%d", &numero);
        getchar();
        
        switch (numero)
        {
            case 1:
                agregarVotante(&(mesa->votantes));   //doble puntero
                break;
            
            case 2:
                printf("Ingrese el rut del votante buscado\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';    //elimina el salto de linea
                buscarVotante(mesa->votantes, aux);
                break;
            
            case 3:
                printf("Ingrese el rut del votante que desea eliminar\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';
                mesa->votantes = eliminarVotante(mesa->votantes, aux);
                break;
            
            case 4:
                printf("Ingrese el rut del votante que desea modificar\n");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';
                modificarVotante(mesa->votantes, aux);
                break;
            
            case 5:
                mostrarVotantes(mesa->votantes);
                break;
            
            case 0:
                printf("Usted ha salido del menú votantes\n");
                break;
            
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero != 0);
}




int main()
{
    struct SistemaVotacion *sistema;
    int opcion;
    
    sistema = nuevoSistema();
    ingresoDeDatos(sistema);
    
    do 
    {
        printf("\n==========================================\n");
        printf("\n================== SERVEL ================\n");
        printf("\n==========================================\n");
        printf("\nBienvenido a nuestra paguina web\n");
        printf("Por favor seleccione la opcion que desea utilizar\n");
        printf("1. Eleccion\n");
        printf("2. Candidato\n");
        printf("3. Mesa\n");
        printf("4. Votante\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) 
        {
            printf("No se ingreso una opcion valida. Terminando el programa.\n");
            break;
        }
        getchar();

        switch(opcion) 
        {
            case 1:
                menuElecciones(sistema);
                break;
            
            case 2:
                if (sistema->elecciones == NULL)
                {
                    printf("ERROR: Primero debe agregar una eleccion.\n");
                }
                else
                {
                    menuCandidatos(sistema->elecciones->datosEleccion->listaCandidatos);
                }
                break;
            
            case 3:
                if (sistema->elecciones == NULL)
                {
                    printf("ERROR: No hay elecciones registradas.\n");
                }
                else if (sistema->elecciones->datosEleccion->listaMesas == NULL)
                {
                    printf("ERROR: No hay mesas registradas en esta eleccion.\n");
                }
                else
                {
                    menuMesa(sistema->elecciones->datosEleccion);
                }
                break;
            
            case 4:
                if (sistema->elecciones == NULL)
                {
                    printf("ERROR: No hay elecciones registradas.\n");
                }
                else if (sistema->elecciones->datosEleccion->listaMesas == NULL)
                {
                    printf("ERROR: No hay mesas registradas.\n");
                }
                else if (sistema->elecciones->datosEleccion->listaMesas->datosMesa->votantes == NULL)
                {
                    printf("ERROR: No hay votantes registrados en esta mesa.\n");
                }
                else
                {
                    menuVotantes(sistema->elecciones->datosEleccion->listaMesas->datosMesa);
                }
                break;
            
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);           
    return 0;
}
