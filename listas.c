#include <stdio.h>
#include <malloc.h>

//   Estructuras de datos
struct Nodo {
  unsigned short num;
  struct Nodo *sig;
};

typedef struct Nodo *puntero;

//    Funciones
void buscar(puntero xp) {
  int num;
  printf("Ingrese el número que quiere buscar: ");
  scanf("%d", &num);
  while (( xp != NULL) && (xp->num != num)) // Bucle para buscar de elemento en elemento hasta el final.
    xp = xp->sig;
  if (xp == NULL) // Se llegó al final de la lista y aún no se encontró.
    printf("El número no está en la lista.");
  else // No se llegó al final de la lista.
    printf("El número se encontró en la lista.");
}

void recorrer(puntero xp) {
  printf("Listado de datos: \n");
  while (xp != NULL) { // Mientras no se llegue al final de la lista.
    printf("%d\n", xp->num);
    xp = xp->sig; // Siguiente elemento.
  }
}

void insertar(puntero *xp) {
  puntero nuevo;
  nuevo = (puntero) malloc (sizeof(struct Nodo));
  printf("Inserte el valor del nuevo elemento: ");
  scanf("%hu", &nuevo->num);
  nuevo->sig = *xp; // El siguiente es NULL.
  *xp = nuevo; // El actual es el nuevo.
}

void crear(puntero *xp) {
  *xp = NULL;
}

int main() {
  puntero cabeza;
  int option = -1;
  crear(&cabeza);

  while (option != 0) {
    printf("\nIngrese una elección: \n");
    printf("0: Salir.\n");
    printf("1: Cargar elemento.\n");
    printf("2: Mostrar lista.\n");
    printf("3: Buscar elemento.\n");
    printf(">> ");
    scanf("%d", &option);
    switch(option) {
      case 0:
        break;
      case 1:
        insertar(&cabeza);
        break;
      case 2:
        recorrer(cabeza);
        break;
      case 3:
        buscar(cabeza);
        break;
      default:
        printf("Opción inválida: %d\n", option);
        break;
    }
  }
  
  return 0;
}
