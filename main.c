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
	int usados;
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
	int votos;
};

struct NodoMesa
{
	struct Mesa *datosMesa;
	struct NodoMesa *sig;
};

struct Mesa
{
	int PadronMesa;
	char *LocalVotacion;
	int CantVotantesEnMesa;
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

/* Funciones ElecciC3n */
struct NodoEleccion *nuevoNodoEleccion();
struct Eleccion *crearEleccion();
void agregarNodoEleccion(struct SistemaVotacion *sistema, struct NodoEleccion *nodo);
void agregarEleccion(struct SistemaVotacion *sistema);
void listarElecciones(struct SistemaVotacion *sistema);
void calcularParticipacion(struct Eleccion *eleccion);
void contarVotosPorCandidato(struct Eleccion *eleccion);

/* Funciones Candidato  */
struct TodosCandidatos *crearArregloCandidatos();
struct Candidato *crearCandidato();
void arregloFijo(struct TodosCandidatos *arreglo, int tamano);
void agregarCandidato(struct TodosCandidatos *lista);
void buscarCandidato(struct TodosCandidatos *lista, char *rut);
void compactarArreglo(struct TodosCandidatos *lista);
void eliminarCandidato(struct TodosCandidatos *lista, char *rut);
void modificarCandidato(struct TodosCandidatos *lista, char *rut);
void mostrarCandidato(struct TodosCandidatos *lista);
void ordenarCandidatosBurbuja(struct TodosCandidatos *lista);
void menuCandidatos(struct TodosCandidatos *lista);
void ingresoDeDatosCandidatos(struct Candidato *espacio);

/* Funciones Mesa */
struct NodoMesa *crearNodoMesa();
struct Mesa *crearMesa();
void agregarNodoMesa(struct Eleccion *eleccion, struct NodoMesa *nuevo);
struct Mesa *buscarMesa(struct Eleccion *eleccion, int numeroBuscado);
void agregarMesa(struct Eleccion *eleccion, int numeroPadron);
void listarMesas(struct Eleccion *eleccion);
int eliminarMesa(struct Eleccion *eleccion, int numeroBuscado);
void menuMesa(struct Eleccion *eleccion);

/* Funciones Votante */
struct NodoVotante *nuevoNodoVotante();
struct Votante *crearVotante();
struct NodoVotante* minimoNodo(struct NodoVotante* nodo);
void agregarNodoVotante(struct NodoVotante **raiz, struct NodoVotante *nuevo);
struct NodoVotante* buscarNodoVotante(struct NodoVotante *raiz, char *rut);
void agregarVotante(struct NodoVotante **raiz);
int buscarVotante(struct NodoVotante *raiz, char *rut);
struct NodoVotante* eliminarVotante(struct NodoVotante *raiz, char *rut);
void modificarVotante(struct NodoVotante *raiz, char *rut);
void mostrarVotantes(struct NodoVotante *raiz);
void liberarArbolVotantes(struct NodoVotante *raiz);
void menuVotantes(struct Mesa *mesa);


/*FUNCIONES SISTEMA INICIAL Y DE FUNCIONALIDAD*/

struct SistemaVotacion *nuevoSistema()
{
	struct SistemaVotacion *nueva;

	nueva = (struct SistemaVotacion *) malloc (sizeof(struct SistemaVotacion));
	//QUITAR ESTA LINEA
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

struct NodoEleccion *nuevoNodoEleccion()
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

	if (sistema->elecciones == NULL)
	{
		sistema->elecciones = nodo;
	}
	else
	{
		rec = sistema->elecciones;
		while (rec->sig != NULL)
		{
			rec = rec->sig;
		}
		rec->sig = nodo;
	}
}


void agregarEleccion(struct SistemaVotacion *sistema)
{
	struct NodoEleccion *nuevoNodo;
	struct Eleccion *nuevaEleccion;
	int tamano;

	nuevoNodo = nuevoNodoEleccion();
	nuevaEleccion = crearEleccion();

	if (nuevoNodo == NULL || nuevaEleccion == NULL)
	{
		printf("ERROR al crear la eleccion.\n");
		return;
	}

	printf("Ingrese numero de vuelta: ");
	scanf("%d", &nuevaEleccion->NumeroVuelta);
	getchar();

	printf("Ingrese la cantidad mC!xima de candidatos permitidos para esta elecciC3n: ");
	scanf("%d", &tamano);
	getchar();
	nuevaEleccion->listaCandidatos = crearArregloCandidatos();
	arregloFijo(nuevaEleccion->listaCandidatos, tamano);

	nuevoNodo->datosEleccion = nuevaEleccion;
	agregarNodoEleccion(sistema, nuevoNodo);

	printf("Eleccion agregada correctamente.\n");
}

void participacion()
{
	printf("\n==== PARTICIPACION ELECTORAL ====\n");
}

void error1()
{
	printf("ERROR: No hay mesas registradas para calcular la participaciC3n.\n");
}

void imprimirDetalleMesa(struct Mesa *mesa)
{
	printf("Mesa %d (Local: %s): %d votantes\n", mesa->PadronMesa, mesa->LocalVotacion, mesa->CantVotantesEnMesa);
}

void imprimirTotales(int totalMesas, int totalVotantes)
{
	printf("--------------------------------\n");
	printf("Total de mesas revisadas: %d\n", totalMesas);
	printf("Total de votantes registrados: %d\n", totalVotantes);
	printf("================================\n");
}

void calcularParticipacion(struct Eleccion *eleccion)
{
	struct NodoMesa *rec;
	int totalMesas = 0;
	int totalVotantes = 0;

	rec = eleccion->listaMesas;
	if (rec == NULL)
	{
		error1();
		return;
	}

	participacion();

	while (rec != NULL)
	{
		totalMesas++;
		totalVotantes += rec->datosMesa->CantVotantesEnMesa;

		imprimirDetalleMesa(rec->datosMesa);

		rec = rec->sig;
	}

	imprimirTotales(totalMesas, totalVotantes);
}

void imprimirErrorCandidatos()
{
	printf("ERROR: No hay candidatos registrados para contar votos.\n");
}

void imprimirEncabezadoResultados()
{
	printf("\n==== RESULTADOS PRELIMINARES DE LA ELECCION ====\n");
	printf("%-20s | %-15s | %s\n", "Candidato", "Partido", "Votos Totales");
	printf("--------------------------------------------------\n");
}

void imprimirDetalleCandidato(struct Candidato *candidato)
{
	printf("%-20s | %-15s | %d\n", candidato->NombreCandidato, candidato->PartidoPolitico, candidato->votos);
}

void imprimirPieResultados()
{
	printf("==================================================\n");
}

void contarVotosPorCandidato(struct Eleccion *eleccion)
{
	int i;
	struct TodosCandidatos *lista = eleccion->listaCandidatos;

	if (lista == NULL || lista->usados == 0)
	{
		imprimirErrorCandidatos();
		return;
	}

	imprimirEncabezadoResultados();

	for (i = 0; i < lista->usados; i++)
	{
		if (lista->Candidatos[i] != NULL)
		{
			imprimirDetalleCandidato(lista->Candidatos[i]);
		}
	}
	imprimirPieResultados();
}

void imprimirErrorElecciones()
{
    printf("No hay elecciones registradas.\n");
}

void imprimirEncabezadoElecciones()
{
    printf("----- LISTA DE ELECCIONES -----\n");
}

//OJO
void imprimirDetalleEleccion(struct Eleccion *eleccion)
{
    printf("Numero de vuelta: %d\n", eleccion->NumeroVuelta); 
}

void listarElecciones(struct SistemaVotacion *sistema)
{
	struct NodoEleccion *rec = sistema->elecciones;

	if (rec == NULL)
	{
		imprimirErrorElecciones();
		return;
	}

	imprimirEncabezadoElecciones();
	while (rec != NULL)
	{
		imprimirDetalleEleccion(rec->datosEleccion);
		rec = rec->sig;
	}
}

/*FUNCIONES DE MESA*/

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

	nuevo->PadronMesa = 0;
	nuevo->LocalVotacion = NULL;
	nuevo->CantVotantesEnMesa = 0;
	nuevo->votantes = NULL;
	return nuevo;
}

void errorNodoMesa()
{
    printf("ERROR: No se puede agregar mesa.\n");
}

void agregarNodoMesa(struct Eleccion *eleccion, struct NodoMesa *nuevo)
{
	struct NodoMesa *rec;

	if (eleccion == NULL || nuevo == NULL)
	{
		errorNodoMesa();
		return;
	}


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

void errorExisteMesa()
{
    printf("ERROR: Ya existe una mesa con ese numero de padron.\n");
}

void errorCrearMesa()
{
    printf("ERROR: No se pudo crear la mesa.\n");
}

void ingreseMesa()
{
    printf("Ingrese local de votaciC3n:\n");
}

void errorMemoriaMesa()
{
    printf("ERROR: No se pudo asignar memoria para el local de votacion.\n");
}

void errorNodo2Mesa()
{
    printf("ERROR: No se pudo crear el nodo para la mesa.\n");
}

void agregarMesa(struct Eleccion *eleccion, int numeroPadron)
{
	struct NodoMesa *nuevoNodo;
	struct Mesa *nuevaMesa;
	char aux[200];

	if (eleccion == NULL)
	{
		return;
	}

	if (buscarMesa(eleccion, numeroPadron) != NULL)
	{
		errorExisteMesa();
		return;
	}

	nuevaMesa = crearMesa();
	if (nuevaMesa == NULL)
	{
	    errorCrearMesa();
		return;
	}

	nuevaMesa->PadronMesa = numeroPadron;

	ingreseMesa();
	fgets(aux, sizeof(aux), stdin);
	aux[strcspn(aux, "\n")] = '\0';

	nuevaMesa->LocalVotacion = malloc(strlen(aux) + 1);
	if (nuevaMesa->LocalVotacion == NULL) 
	{
		errorMemoriaMesa();
		free(nuevaMesa);
		return;
	}
	strcpy(nuevaMesa->LocalVotacion, aux);

	nuevoNodo = crearNodoMesa();
	if (nuevoNodo == NULL)
	{
		errorNodo2Mesa();
		free(nuevaMesa->LocalVotacion);
		free(nuevaMesa);
		return;
	}

	nuevoNodo->datosMesa = nuevaMesa;

	agregarNodoMesa(eleccion, nuevoNodo);

	mensajeMesaAgregada();
}

struct Mesa *buscarMesa(struct Eleccion *eleccion, int numeroBuscado)
{
	struct NodoMesa *rec;

	if (eleccion == NULL || eleccion->listaMesas == NULL)
	{
		return NULL;
	}


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

void liberarArbolVotantes(struct NodoVotante *raiz)
{
	if (raiz == NULL) return;

	liberarArbolVotantes(raiz->izq);
	liberarArbolVotantes(raiz->der);

	free(raiz->datosVotante->Nombre);
	free(raiz->datosVotante);
	free(raiz);
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

			liberarArbolVotantes(rec->datosMesa->votantes);
			free(rec->datosMesa->LocalVotacion);
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

void errorMesasRegistradas()
{
    printf("No hay mesas registradas.\n");
}

void imprimirEncabezadoMesas()
{
    printf("----- LISTA DE MESAS -----\n");
}

void imprimirDetalleMesaPadron(struct Mesa *mesa)
{
    printf("Mesa Padron: %d\n", mesa->PadronMesa);
}

void listarMesas(struct Eleccion *eleccion)
{
	struct NodoMesa *rec;

	rec = eleccion->listaMesas;

	if (rec == NULL)
	{
	    errorMesasRegistradas();
		return;
	}

	imprimirEncabezadoMesas();
	while (rec != NULL)
	{
		imprimirDetalleMesaPadron(rec->datosMesa);
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
				agregarMesa(eleccion, numero);
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




/*FUNCION INICIAL DE INGRESO DE DATOS */

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
	getchar();

	printf("Ingrese fecha de inicio de campaC1a (dia mes anio):\n");
	scanf("%d %d %d", &sistema->FechaInicioCampana.dia, &sistema->FechaInicioCampana.mes, &sistema->FechaInicioCampana.anio);
	getchar();

	printf("Ingrese fecha de votaciC3n (dia mes anio):\n");
	scanf("%d %d %d",&sistema->FechaVotacion.dia, &sistema->FechaVotacion.mes, &sistema->FechaVotacion.anio);
	getchar();

	printf("Datos del Sistema cargados correctamente.\n");
}



/*FUNCION DEL INGRESO DE DATOS DE CANDIDATOS */

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

	printf("Ingrese el partido polC-tico del candidato:\n");
	fgets(aux, 200, stdin);
	aux[strcspn(aux, "\n")] = '\0';
	espacio->PartidoPolitico = (char *) malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(espacio->PartidoPolitico, aux);

	printf("Ingrese el programa de gobierno:\n");
	fgets(aux, 200, stdin);
	aux[strcspn(aux, "\n")] = '\0';
	espacio->ProgramaGobierno = (char *) malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(espacio->ProgramaGobierno, aux);

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



/*FUNCIONES CANDIDATO*/

struct TodosCandidatos *crearArregloCandidatos()
{
	struct TodosCandidatos *nuevo;

	nuevo = (struct TodosCandidatos *) malloc (sizeof(struct TodosCandidatos));
	nuevo->Candidatos = NULL;
	nuevo->totalCandidatos = 0;
	nuevo->usados = 0;

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
	nuevo->votos = 0;

	return nuevo;
}

void arregloFijo(struct TodosCandidatos *arreglo, int tamano)
{
	int i;

	arreglo->Candidatos = (struct Candidato **) malloc (tamano * sizeof(struct Candidato *));
	arreglo->totalCandidatos = tamano;
	arreglo->usados = 0;

	for (i = 0; i < tamano; i++)
	{
		arreglo->Candidatos[i] = crearCandidato();
	}

}


void agregarCandidato(struct TodosCandidatos *lista)
{
	struct Candidato *nuevo;
	char aux[200];
	int edad, delitos;

	if (lista->usados == lista->totalCandidatos)
	{
		printf("No se pueden agregar mas candidatos.\n");
		return;
	}

	printf("Ingrese edad del candidato: ");
	scanf("%d", &edad);
	getchar();

	if (edad < 35)
	{
		printf("ERROR: Debe tener 35 aC1os o mC!s.\n");
		return;
	}

	printf("Ingrese nacionalidad del candidato: ");
	fgets(aux, 200, stdin);
	aux[strcspn(aux, "\n")] = '\0';

	if (strcmp(aux, "Chile") != 0 && strcmp(aux, "chile") != 0)
	{
		printf("ERROR: Debe ser chileno de nacimiento.\n");
		return;
	}

	printf("Tiene antecedentes? (1=SI / 0=NO): ");
	scanf("%d", &delitos);
	getchar();

	if (delitos != 0)
	{
		printf("ERROR: No puede tener antecedentes.\n");
		return;
	}

	nuevo = lista->Candidatos[lista->usados];

	if (nuevo == NULL)
	{
		nuevo = crearCandidato();
		if (nuevo == NULL)
		{
			printf("ERROR: No se pudo asignar memoria para el nuevo candidato.\n");
			return;
		}
		lista->Candidatos[lista->usados] = nuevo;
	}

	nuevo->edad = edad;

	strcpy(nuevo->Nacionalidad, aux);
	nuevo->delitos = delitos;

	ingresoDeDatosCandidatos(nuevo);

	lista->usados++;
}



void buscarCandidato(struct TodosCandidatos *lista, char *rut)
{
	int i;

	for (i = 0; i < lista->usados; i++)
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

	for (i = 0; i < lista->usados; i++)
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

	lista->usados = j;
}

void eliminarCandidato(struct TodosCandidatos *lista, char *rut)
{
	int i;

	for (i = 0; i < lista->usados; i++)
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
	printf("No se encontrC3 el candidato.\n");
}


void modificarCandidato(struct TodosCandidatos *lista, char *rut)
{
	int i;
	char aux[200];

	for (i = 0; i < lista->usados; i++)
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
	printf("No se encontrC3 ese candidato.\n");
}



void mostrarCandidato(struct TodosCandidatos *lista)
{
	int i;

	for (i = 0; i < lista->usados; i++)
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

/*FUNCION OPCIONAL DE ORDENAMIENTO BURBUJA*/

void ordenarCandidatosBurbuja(struct TodosCandidatos *lista)
{
	int i, j;
	struct Candidato *temp;

	if (lista->usados <= 1)
	{
		printf("No hay suficientes candidatos para ordenar.\n");
		return;
	}

	printf("Ordenando candidatos por RUT (Algoritmo de Burbuja)...\n");

	for (i = 0; i < lista->usados - 1; i++)
	{
		for (j = 0; j < lista->usados - 1 - i; j++)
		{
			if (strcmp(lista->Candidatos[j]->Rut, lista->Candidatos[j + 1]->Rut) > 0)
			{
				temp = lista->Candidatos[j];
				lista->Candidatos[j] = lista->Candidatos[j + 1];
				lista->Candidatos[j + 1] = temp;
			}
		}
	}
	printf("Ordenamiento completado.\n");
}


void menuCandidatos(struct TodosCandidatos *lista)
{
	int numero;
	char aux[15];

	do
	{
		printf("Usted accediC3 al menC: candidatos\n");
		printf("Seleccione la opciC3n que desee\n");
		printf("1. agregar un candidato\n");
		printf("2. buscar un candidato\n");
		printf("3. eliminar un candidato\n");
		printf("4. Modificar un candidato\n");
		printf("5. Mostrar la informacion de los candidatos\n");
		printf("6. Ordenar los candidatos\n");
		printf("0. Salir del menC: candidatos\n");

		scanf("%d", &numero);
		getchar();

		switch (numero)
		{
		case 1:
			agregarCandidato(lista);
			break;

		case 2:
			printf("Ingrese rut del candidato a buscar\n");
			fgets(aux, sizeof(aux), stdin);
			aux[strcspn(aux, "\n")] = '\0';
			buscarCandidato(lista, aux);
			break;

		case 3:
			printf("Ingrese rut del candidato a eliminar\n");
			fgets(aux, sizeof(aux), stdin);
			aux[strcspn(aux, "\n")] = '\0';

			eliminarCandidato(lista, aux);

			printf("B?Desea compactar el arreglo? (1=SC- / 0=No): ");
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
			mostrarCandidato(lista);
			break;


		case 6:
			ordenarCandidatosBurbuja(lista);
			break;

		case 0:
			printf("Usted ha salido del menC: candidatos\n");
			break;

		default:
			printf("Ingrese una opciC3n valida\n");
			break;
		}
	} while (numero != 0);
}

/*FUNCIONES VOTANTES*/

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
	if (*raiz == NULL)
	{
		*raiz = nuevo;
		return;
	}

	if (strcmp(nuevo->datosVotante->rut, (*raiz)->datosVotante->rut) < 0)
	{
		agregarNodoVotante(&(*raiz)->izq, nuevo);
	}
	else if (strcmp(nuevo->datosVotante->rut, (*raiz)->datosVotante->rut) > 0)
	{
		agregarNodoVotante(&(*raiz)->der, nuevo);
	}
	else
	{
		printf("ERROR: Ya existe un votante con ese RUT.\n");
		free(nuevo->datosVotante->Nombre);
		free(nuevo->datosVotante);
		free(nuevo);
	}
}

struct NodoVotante* buscarNodoVotante(struct NodoVotante *raiz, char *rut)
{
	if (raiz == NULL)
	{
		return NULL;
	}

	if (strcmp(rut, raiz->datosVotante->rut) == 0)
	{
		return raiz;
	}
	else if (strcmp(rut, raiz->datosVotante->rut) < 0)
	{
		return buscarNodoVotante(raiz->izq, rut);
	}
	else
	{
		return buscarNodoVotante(raiz->der, rut);
	}
}


void agregarVotante(struct NodoVotante **raiz)
{
	struct NodoVotante *nuevo;
	struct Votante *auxDatos;
	char aux[200];

	auxDatos = crearVotante();

	printf("Ingrese rut del votante:\n");
	fgets(aux, 200, stdin);
	aux[strcspn(aux, "\n")] = '\0';

	if (buscarNodoVotante(*raiz, aux) != NULL)
	{
		printf("ERROR: Ya existe un votante con ese RUT.\n");
		free(auxDatos);
		return;
	}
	strcpy(auxDatos->rut, aux);

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

	printf("Ingrese paC-s de residencia del votante:\n");
	fgets(aux, 200, stdin);
	aux[strcspn(aux, "\n")] = '\0';
	strcpy(auxDatos->paisResidencia, aux);

	nuevo = nuevoNodoVotante();
	nuevo->datosVotante = auxDatos;

	agregarNodoVotante(raiz, nuevo);

	printf("Votante agregado correctamente.\n");
}


int buscarVotante(struct NodoVotante *raiz, char *rut)
{
	if (raiz == NULL)
	{
		return 0;
	}

	if (strcmp(rut, raiz->datosVotante->rut) == 0)
	{
		printf("Nombre votante: %s\n", raiz->datosVotante->Nombre);
		printf("Rut votante: %s\n", raiz->datosVotante->rut);
		printf("Edad votante: %d\n", raiz->datosVotante->edad);
		printf("Nacionalidad votante: %s\n", raiz->datosVotante->Nacionalidad);
		printf("Pais de residencia del votante: %s\n", raiz->datosVotante->paisResidencia);
		return 1;
	}
	else if (strcmp(rut, raiz->datosVotante->rut) < 0)
	{
		return buscarVotante(raiz->izq, rut);
	}
	else
	{
		return buscarVotante(raiz->der, rut);
	}
}

struct NodoVotante* minimoNodo(struct NodoVotante* nodo)
{
	struct NodoVotante* actual;

	actual = nodo;
	while (actual && actual->izq != NULL)
	{
		actual = actual->izq;
	}

	return actual;
}

struct NodoVotante* eliminarVotante(struct NodoVotante *raiz, char *rut)
{
	struct NodoVotante* temp;

	if (raiz == NULL)
	{
		return NULL;
	}

	if (strcmp(rut, raiz->datosVotante->rut) < 0)
	{
		raiz->izq = eliminarVotante(raiz->izq, rut);
	}
	else if (strcmp(rut, raiz->datosVotante->rut) > 0)
	{
		raiz->der = eliminarVotante(raiz->der, rut);
	}
	else
	{
		if (raiz->izq == NULL)
		{
			temp = raiz->der;

			free(raiz->datosVotante->Nombre);
			free(raiz->datosVotante);
			free(raiz);

			return temp;
		}
		else if (raiz->der == NULL)
		{
			temp = raiz->izq;

			free(raiz->datosVotante->Nombre);
			free(raiz->datosVotante);
			free(raiz);

			return temp;
		}

		temp = minimoNodo(raiz->der);

		strcpy(raiz->datosVotante->rut, temp->datosVotante->rut);
		raiz->datosVotante->edad = temp->datosVotante->edad;

		free(raiz->datosVotante->Nombre);
		raiz->datosVotante->Nombre = malloc(strlen(temp->datosVotante->Nombre) + 1);
		strcpy(raiz->datosVotante->Nombre, temp->datosVotante->Nombre);

		strcpy(raiz->datosVotante->paisResidencia, temp->datosVotante->paisResidencia);


		strcpy(raiz->datosVotante->Nacionalidad, temp->datosVotante->Nacionalidad);

		raiz->der = eliminarVotante(raiz->der, temp->datosVotante->rut);
	}

	return raiz;
}



void modificarVotante(struct NodoVotante *raiz, char *rut)
{
	char aux[200];

	if (raiz == NULL)
	{
		printf("No se encontrC3 el votante.\n");
		return;
	}

	if (strcmp(rut, raiz->datosVotante->rut) < 0)
	{
		modificarVotante(raiz->izq, rut);
	}
	else if (strcmp(rut, raiz->datosVotante->rut) > 0)
	{
		modificarVotante(raiz->der, rut);
	}
	else
	{
		printf("Ingrese nuevo nombre: ");
		fgets(aux, sizeof(aux), stdin);
		aux[strcspn(aux, "\n")] = '\0';

		if (raiz->datosVotante->Nombre != NULL)
			free(raiz->datosVotante->Nombre);

		raiz->datosVotante->Nombre = malloc(strlen(aux) + 1);
		strcpy(raiz->datosVotante->Nombre, aux);

		printf("Ingrese nueva edad: ");
		scanf("%d", &raiz->datosVotante->edad);
		getchar();

		printf("Votante modificado correctamente.\n");
	}
}

void mostrarVotantes(struct NodoVotante *raiz)
{
	if (raiz == NULL)
	{
		return;
	}

	mostrarVotantes(raiz->izq);

	printf("========= VOTANTE =========\n");
	printf("RUT: %s\n", raiz->datosVotante->rut);
	printf("Nombre: %s\n", raiz->datosVotante->Nombre);
	printf("Edad: %d\n", raiz->datosVotante->edad);
	printf("Nacionalidad: %s\n", raiz->datosVotante->Nacionalidad);
	printf("PaC-s Residencia: %s\n", raiz->datosVotante->paisResidencia);
	printf("============================\n");

	mostrarVotantes(raiz->der);
}


void menuVotantes(struct Mesa *mesa)
{
	int numero;
	char aux[15];

	do
	{
		printf("Usted accediC3 al menC: votantes\n");
		printf("Seleccione la opciC3n que desee\n");
		printf("1. agregar un votante\n");
		printf("2. buscar un votante\n");
		printf("3. eliminar un votante\n");
		printf("4. Modificar un votante\n");
		printf("5. Mostrar la informacion de los votantes\n");
		printf("0. Salir del menC: votantes\n");

		scanf("%d", &numero);
		getchar();

		switch (numero)
		{
		case 1:
			agregarVotante(&(mesa->votantes));
			break;

		case 2:
			printf("Ingrese el rut del votante buscado\n");
			fgets(aux, sizeof(aux), stdin);
			aux[strcspn(aux, "\n")] = '\0';
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
			printf("Usted ha salido del menC: votantes\n");
			break;

		default:
			printf("Ingrese una opciC3n valida\n");
			break;
		}
	} while (numero != 0);
}




int main()
{
	struct Eleccion *eleccionActual;
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
		printf("5. Reportes y estadisticas\n");
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
			else
			{
				menuVotantes(sistema->elecciones->datosEleccion->listaMesas->datosMesa);
			}
			break;

		case 5:

			if (sistema->elecciones == NULL)
			{
				printf("ERROR: Primero debe crear una elecciC3n.\n");
			}
			else
			{
				eleccionActual = sistema->elecciones->datosEleccion;

				printf("\n--- REPORTES ---\n");
				calcularParticipacion(eleccionActual);
				contarVotosPorCandidato(eleccionActual);
				printf("----------------\n");
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
