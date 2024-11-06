#include <stdio.h>
#include <string.h>

struct Persona {
	int cod;
	char name[50];
	unsigned short edad;
};

void carga(FILE *file) {
	struct Persona ps;
	char name[50];
	unsigned short edad;
	int cod;

	printf("Ingrese el nombre de la persona (FIN para terminar): ");
	scanf("%s", name);
	printf("%s\n", name);
	while (strcmp("FIN", name) != 0) {
		printf("Ingrese la edad de la persona: ");
		scanf("%hu", &edad);

		// Calcular posición
		long pos = ftell(file); // Indicar posición del puntero
		cod = (int)(pos / sizeof(struct Persona)) + 1; // Dividir la posición actual por el tamaño del struct (0 / 56 = 0, 56 / 56 = 1, 112 / 56 = 2)
		printf("Código: %d | Pos: %ld\n", cod, pos);

		// Guardar datos en ps
		ps.edad = edad;
		ps.cod = cod;
		strcpy(ps.name, name);
		
		// Guardar persona.
		fwrite(&ps, sizeof(ps), 1, file);

		printf("Ingrese el nombre de la persona (FIN para terminar): ");
		scanf("%s", name);
	}
}

void mostrar(FILE *file) {
	struct Persona ps;
	rewind(file); // Volver al principio
	while (fread(&ps, sizeof(ps), 1, file)) {
		printf("Persona: %s | Edad: %d\n", ps.name, ps.edad); // Mostrar cada registro guardado en el archivo.
	}
}

void mostrar_por_cod(FILE *file) {
	struct Persona ps;
	int cod;
	printf("Ingrese el código de la persona (desde 1): ");
	scanf("%d", &cod);
	fseek(file, (cod - 1) * sizeof (struct Persona), SEEK_SET); // Ubicar el puntero en: desde el principio, código * el tamaño del registro
	fread(&ps, sizeof (ps), 1, file); // Leer el registro
	printf("Codigo: %d | Nombre: %s | Edad: %d\n", ps.cod, ps.name, ps.edad);
}

int main() {
	FILE *file = fopen("Personas.dat", "w+");
	carga(file);
	mostrar(file);
	mostrar_por_cod(file);
	fclose(file);
	return 0;
}
