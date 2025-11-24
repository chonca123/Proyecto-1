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

struct Mesa
{
    int PadronMesa;  
    struct NodoVotante *votantes;  // lista interna, empieza NULL
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

//FUNCIONES SISTEMA INICIAL

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

void cargarDatosMesa(struct Mesa *mesa)
{
    printf("Ingrese el numero de padron de la mesa: ");
    scanf("%d", &mesa->PadronMesa);

    mesa->votantes = NULL;
}

void mensajeMesaAgregada()
{
    printf("La mesa fue agregada correctamente.\n");
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

void mensajeMesaEliminada()
{
    printf("La mesa fue eliminada correctamente.\n");
}

void mensajeMesaNoExiste()
{
    printf("No existe ninguna mesa con ese numero de padron.\n");
}

int modificarDenuncia(struct nodo_Denuncias *lista, int RUC, 
                      const char *nuevoTipo, const char *nuevaDescripcion, int nuevaFecha)
{
    struct nodo_Denuncias *nodo;

    if (lista == NULL || nuevoTipo == NULL || nuevaDescripcion == NULL)
    {
        imprimir_modificacion_fallida(RUC);
        return -1;
    }

    nodo = buscarDenuncia(lista, RUC);

    if (nodo == NULL)
    {
        imprimir_modificacion_fallida(RUC);
        return -1;
    }

    strncpy(nodo->Denuncias->Tipo_denunciante, nuevoTipo, 
            sizeof(nodo->Denuncias->Tipo_denunciante) - 1);
    nodo->Denuncias->Tipo_denunciante[sizeof(nodo->Denuncias->Tipo_denunciante) - 1] = '\0';
    
    strncpy(nodo->Denuncias->descripcion, nuevaDescripcion, 
            sizeof(nodo->Denuncias->descripcion) - 1);
    nodo->Denuncias->descripcion[sizeof(nodo->Denuncias->descripcion) - 1] = '\0';

    nodo->Denuncias->fecha = nuevaFecha;

    imprimir_modificacion_exitosa(RUC, nuevoTipo, nuevaDescripcion, nuevaFecha);

    return 1;
}

void imprimir_modificacion_exitosa(int RUC, const char *nuevoTipo, const char *nuevaDescripcion, int nuevaFecha)
{
    printf("Modificacion exitosa para RUC %d\n", RUC);
    printf("Nuevo tipo: %s\n", nuevoTipo);
    printf("Nueva descripcion: %s\n", nuevaDescripcion);
    printf("Nueva fecha: %d\n", nuevaFecha);
}

void imprimir_modificacion_fallida(int RUC)
{
    printf("ERROR: No se encontro denuncia con el RUC %d.\n", RUC);
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
    int opcion;
    int numero;
    int nuevoNumero;
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

        switch(opcion) 
        {
            case 1:
                printf("Ingrese el numero de padron de la nueva mesa: ");
                scanf("%d", &numero);

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
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 0);
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

void agregarNodoVotante(struct NodoVotante **raiz, struct NodoVotante *nuevo)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = nuevo;
        return;
    }
    else
    {
        //orden por edad
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







//Ingreso de datos para el sistema
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

void ingresoDeDatosEleccion(struct Eleccion *nodo)
{
    int numero;
    
    printf("Ingrese numero de vuelta de esta eleccion\n");
    scanf("%d", &numero);
}

void ingresoDeDatosCandidatos(struct Candidato *espacio)
{
    int 
    char aux[200];
    
    printf("Ingrese el rut del candidato\n");
    scanf(" %[^\n]", espacio->rut);
    
    printf("Ingrese el nombre del candidato\n");
    scanf(" %[^\n]", aux);
    
    espacio->NombreCandidato = (char *) malloc ((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->NombreCandidato, aux);
    
    printf("Ingrese la nacionalidad del candidato\n");
    scanf(" %[^\n]", espacio->nacionalidad);
    
    printf("Ingrese la edad del candidato\n");
    scanf("%d", &espacio->edad);
    
    printf("Ingrese el partido politico del candidato\n");
    scanf(" %[^\n]", aux);
    
    espacio->PartidoPolitico = (char *) malloc ((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->PartidoPolitico, aux);
    
    printf("Ingrese el programa de gobierno del candidato\n");
    scanf(" %[^\n]", aux);
    
    espacio->ProgramaGobierno = (char *) malloc ((strlen(aux) + 1) * sizeof(char));
    strcpy(espacio->ProgramaGobierno, aux);
    
    printf("Ingrese un 1 si su candidato tiene antecedentes o un 0 si no los tiene\n");
    scanf("%d", &espacio->delitos);
}

//esto tiene el ingreso si se deja esos datos de vocales estaticos, sino, se borra
void ingresoDeDatosMesa()
{
    
}

void ingresoDeDatosVotante(struct Votante *estructura)
{
    char aux[200];
    
    printf("Ingrese el nombre del votante\n");
    scanf(" %[^\n]", aux);
    
    estructura->Nombre = (char *) malloc ((strlen(aux) + 1) * sizeof(char));
    strcpy(estructura->Nombre, aux);
    
    printf("Ingrese la edad del votante\n");
    scanf("%d", estructura->edad);
    
    printf("Ingrese la nacionalidad del votante\n");
    scanf(" %[^\n]", estructura->Nacionalidad);
    
    printf("Ingrese el rut del votante\n");
    scanf(" %[^\n]", estructura->rut);
    
    printf("Ingrese el pais de residencia del votante\n");
    scanf(" %[^\n]", estructura->paisResidencia);
}



//MENUS
//sera necesario el de sistema??
void menuSistemaVotacion()
{
    int numero
    
    do
    {
        printf("Usted accedió al menú sistema de votacion\n");
        printf("Seleccione la opción que desee\n");
        printf("1. crear un sistema\n");
        printf("2. buscar un sistema\n");
        printf("3. eliminar un sistema\n");
        printf("4. Modificar un sistema\n");
        printf("5. Mostrar la informacion del sistema\n");
        printf("0. Salir del menú sistema\n");
        
        scanf("%d", &numero);
        
        switch (numero)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Usted ha salido del menú sistema\n");
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero)
}

void menuElecciones()
{
    int numero
    
    do
    {
        printf("Usted accedió al menú elecciones\n");
        printf("Seleccione la opción que desee\n");
        printf("1. agregar una eleccion\n");
        printf("2. buscar una eleccion\n");
        printf("3. eliminar una eleccion\n");
        printf("4. Modificar una eleccion\n");
        printf("5. Mostrar la informacion de la eleccion\n");
        printf("0. Salir del menú elecciones\n");
        
        scanf("%d", &numero);
        
        switch (numero)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Usted ha salido del menú elecciones\n");
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero)
}

void menuCandidatos()
{
    int numero
    
    do
    {
        printf("Usted accedió al menú candidatos\n");
        printf("Seleccione la opción que desee\n");
        printf("1. agregar un candidato\n");
        printf("2. buscar un candidato\n");
        printf("3. eliminar un candidato\n");
        printf("4. Modificar un candidato\");
        printf("5. Mostrar la informacion de los candidatos\n");
        printf("0. Salir del menú candidatos\n");
        
        scanf("%d", &numero);
        
        switch (numero)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Usted ha salido del menú candidatos\n");
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero)
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
                eliminarVotante(&(mesa->votantes), aux);
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
            
            default:
                printf("Ingrese una opción valida\n");
                break;
        }
    } while (numero != 0);
}




int main()
{
    //Va o no sistema??
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
        printf("1. SistemaVotacion\n");
        printf("2. Eleccion\n");
        printf("3. Candidato\n");
        printf("4. Mesa\n");
        printf("5. Votante\n");
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
                menuSistemaVotacion();
                break;
            case 2:
                menuElecciones();
                break;
            case 3:
                menuCandidatos();
                break;
            case 4:
                menuMesa();
                break;
            case 5:
                menuVotantes();
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != (-1));           
    return 0;
}
