/*
Ejercicio 7
Una consultora contable realiza la liquidación de haberes de los empleados de varias PYMES. Para ello posee un
archivo con información de empleados “EMPLEADOS.dat” de diferentes empresas: Nombre del Empleado, Nombre
de la Empresa, DNI, CUIT y sueldo neto. El archivo está ordenado por nombre de empresa.
Se pide realizar un programa que:

a) Emita un listado ordenado por empresa con la liquidación de haberes de cada empleado. Además, el listado
debe incluir el total a pagar en concepto de sueldo por cada empresa.

b) Generar el archivo “EMPRESAS.dat” que almacena para cada empresa la siguiente información: Nombre, total de
empleados, total pagado en concepto de liquidación.
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Estructuras de datos
struct Empleado {
	char nombre[50];
	int dni, cuit;
	float sueldo_neto;
	struct Empleado *sig;
};

struct Empresa {
	char nombre_empresa[50];
	struct Empleado *empleados;
	struct Empresa *sig;
};

struct Guardar_Empresa {
	char nombre_empresa[50];
	int total_empleados;
	float total_pagado;
};

typedef struct Empresa *puntero1;
typedef struct Empleado *puntero2;

void carga(puntero1 *cabeza) {
	char nombre_empresa[50], nombre_empleado[50];
	printf("Ingrese el nombre de la empresa (FIN para terminar): ");
	fflush(stdin);
	fgets(nombre_empresa, sizeof(nombre_empresa), stdin);
	nombre_empresa[strcspn(nombre_empresa, "\n")] = '\0';
	
	while (strcmp(nombre_empresa, "FIN")) {
		// Crear empresa
		puntero1 nueva_empresa = (puntero1) malloc (sizeof(struct Empresa));
		nueva_empresa->empleados = NULL;
		
		printf("Ingrese el nombre del empleado (FIN para terminar): ");
		fflush(stdin);
		fgets(nombre_empleado, sizeof(nombre_empleado), stdin);
		nombre_empleado[strcspn(nombre_empleado, "\n")] = '\0';
		while (strcmp(nombre_empleado, "FIN")) {
			// Crear empleado
			puntero2 nuevo_empleado = (puntero2) malloc (sizeof(struct Empleado));
			strcpy(nuevo_empleado->nombre, nombre_empleado);
			printf("Ingrese el DNI del empleado: ");
			scanf("%d", &nuevo_empleado->dni);
			printf("Ingrese el CUIT del empleado: ");
			scanf("%d", &nuevo_empleado->cuit);
			printf("Ingrese el importe del empleado: ");
			scanf("%f", &nuevo_empleado->sueldo_neto);
			getchar();
			
			// Agregar empleado
			nuevo_empleado->sig = nueva_empresa->empleados;
			nueva_empresa->empleados = nuevo_empleado;

			printf("Ingrese el nombre del empleado (FIN para terminar): ");
			fgets(nombre_empleado, sizeof(nombre_empleado), stdin);
			nombre_empleado[strcspn(nombre_empleado, "\n")] = '\0';
		}

		// Guardar empresa nueva
		strcpy(nueva_empresa->nombre_empresa, nombre_empresa);
		nueva_empresa->sig = *cabeza;
		*cabeza = nueva_empresa;

		printf("Ingrese el nombre de la empresa (FIN para terminar): ");
		fflush(stdin);
		fgets(nombre_empresa, sizeof(nombre_empresa), stdin);
		nombre_empresa[strcspn(nombre_empresa, "\n")] = '\0';
	}
}

void mostrar(puntero1 cabeza) {
	int cont = 1;
	printf("**********LISTADO DE LIQUIDACIÓN**********\n");
	while (cabeza != NULL) {
		printf("Lista de empleados de %s\n", cabeza->nombre_empresa);
		printf("     DNI     Nombre     Sueldo\n");
		puntero2 c_empleados = cabeza->empleados;
		while (c_empleados != NULL) {
			printf("%d  %d  %s  $%f\n", cont, cabeza->empleados->dni, cabeza->empleados->nombre, cabeza->empleados->sueldo_neto);
			c_empleados = c_empleados->sig;
			cont++;
		}
		cabeza = cabeza->sig;
		cont = 1;
	}
}

void guardar_datos(puntero1 cabeza, FILE *file) {
	struct Guardar_Empresa empresa;
	int empleados = 0;
	float total_importe = 0;
	
	while (cabeza != NULL) {
		strcpy(empresa.nombre_empresa, cabeza->nombre_empresa);
		puntero2 c_empleados = cabeza->empleados;
		while (c_empleados != NULL) {
			empleados++;
			total_importe += c_empleados->sueldo_neto;

			// Siguiente
			c_empleados = c_empleados->sig;
		}
		// Guardar en el struct
		empresa.total_empleados = empleados;
		empresa.total_pagado = total_importe;

		// Resetear
		empleados = 0;
		total_importe = 0;
		cabeza = cabeza->sig;

		fwrite(&empresa, sizeof(empresa), 1, file);
	}
}

void mostrar_archivo(FILE *file) {
	struct Guardar_Empresa empresa;
	rewind(file);
	printf("\n");
	while (fread(&empresa, sizeof(empresa), 1, file)) {
		printf("Empresa: %s\n", empresa.nombre_empresa);
		printf("Empleados: %d\n", empresa.total_empleados);
		printf("Importe total: %0.2f\n", empresa.total_pagado);
	}
}

int main() {
	puntero1 cabeza = NULL;
	carga(&cabeza);
	mostrar(cabeza);

	FILE *file = fopen("EMPRESAS.dat", "w+");
	guardar_datos(cabeza, file);
	mostrar_archivo(file);
	
	fclose(file);
	free(cabeza);
	return 0;
}
