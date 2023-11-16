#include "pa2m.h"
#include "src/hash.h"
#include "src/hash_estructura_privada.h"
#include <stdlib.h>

bool funcion_bool(const char *clave, void *valor, void *aux)
{
	if (!aux)
		return true;

	return *((int *)valor) < *((int *)aux);
}

void pruebas()
{
	pa2m_nuevo_grupo(
		"\n======================== CREAR HASH ========================");
	hash_t *hash_capacidad0 = hash_crear(0);
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(
		hash && hash->capacidad == 10,
		"Se prueba crear el hash con una capacidad inicial mayor a 3");
	pa2m_afirmar(
		hash_capacidad0 && hash_capacidad0->capacidad == 3,
		"Se prueba crear el hash con una capacidad inicial menor a 3");
	hash_destruir(hash_capacidad0);





	pa2m_nuevo_grupo(
		"\n======================== INSERTAR ========================");
	void *elemento = (void *)1;
	void *anterior = NULL;
	hash_t *hash_nulo = hash_insertar(NULL, "clave1", elemento, &anterior);
	pa2m_afirmar(!hash_nulo, "Insertar en hash nulo devuelve NULL");
	hash_t *hash_clave_nula =
		hash_insertar(hash, NULL, elemento, &anterior);
	pa2m_afirmar(!hash_clave_nula, "Insertar con clave nula devuelve NULL");
	hash_destruir(hash_nulo);
	hash_destruir(hash_clave_nula);

	hash = hash_insertar(hash, "clave0", NULL, &anterior);
	pa2m_afirmar(
		hash_contiene(hash, "clave0") && hash->cantidad == 1,
		"Insertar con clave valida y elemento nulo inserta correctamente");
	hash = hash_insertar(hash, "clave1", elemento, &anterior);
	pa2m_afirmar(
		hash_contiene(hash, "clave1") && hash->cantidad == 2,
		"Insertar con clave valida y elemento valido inserta correctamente");

	void *elemento2 = (void *)2;
	hash = hash_insertar(hash, "clave2", elemento2, &anterior);
	void *elemento3 = (void *)3;
	hash = hash_insertar(hash, "clave3", elemento3, &anterior);
	void *elemento4 = (void *)4;
	hash = hash_insertar(hash, "clave4", elemento4, &anterior);
	void *elemento5 = (void *)5;
	hash = hash_insertar(hash, "clave5", elemento5, &anterior);
	void *elemento6 = (void *)6;
	hash = hash_insertar(hash, "clave6", elemento6, &anterior);
	pa2m_afirmar(hash_contiene(hash, "clave2") &&
			     hash_contiene(hash, "clave3") &&
			     hash_contiene(hash, "clave4") &&
			     hash_contiene(hash, "clave5") &&
			     hash_contiene(hash, "clave6") &&
			     hash->cantidad == 7,
		     "se prueban insertar varios elementos");

	void *elemento7 = (void *)7;
	hash = hash_insertar(hash, "clave7", elemento7, &anterior);
	void *elemento8 = (void *)8;
	hash = hash_insertar(hash, "clave8", elemento8, &anterior);
	pa2m_afirmar(
		hash_contiene(hash, "clave8") && hash->cantidad == 9 &&
			hash->capacidad == 20,
		"luego de insertar varios elementos, se rehashea correctamente");

	void *elemento_actualizado = (void *)100;
	hash_insertar(hash, "clave8", elemento_actualizado, &anterior);
	pa2m_afirmar(hash_obtener(hash, "clave8") == elemento_actualizado &&
			     anterior == elemento8,
		     "se prueba actualizar un elemento");






	pa2m_nuevo_grupo(
		"\n======================== ELIMINAR ========================");
	void *elemento_eliminado = hash_quitar(NULL, "clave11");
	pa2m_afirmar(!elemento_eliminado,
		     "Eliminar en hash nulo devuelve NULL");
	elemento_eliminado = hash_quitar(hash, NULL);
	pa2m_afirmar(!elemento_eliminado,
		     "intentar eliminar una clave nula devuelve NULL");
	elemento_eliminado = hash_quitar(hash, "aaaaaaaaaaa");
	pa2m_afirmar(
		!elemento_eliminado,
		"intentar eliminar un elemento con clave inexistente devuelve NULL");
	elemento_eliminado = hash_quitar(hash, "clave2");
	pa2m_afirmar(
		elemento_eliminado == elemento2 && hash->cantidad == 8,
		"se puede eliminar un elemento y la cantidad de elementos disminuye");
	elemento_eliminado = hash_quitar(hash, "clave2");
	pa2m_afirmar(
		elemento_eliminado == NULL,
		"si se intenta eliminar un elemento ya eliminado, devuelve NULL");






	pa2m_nuevo_grupo(
		"\n======================== OBTENER ========================");
	void *elemento_obtenido = hash_obtener(NULL, "clave11");
	pa2m_afirmar(!elemento_obtenido, "obtener en hash nulo devuelve NULL");
	elemento_obtenido = hash_obtener(hash, NULL);
	pa2m_afirmar(!elemento_obtenido,
		     "intentar obtener una clave nula devuelve NULL");
	elemento_obtenido = hash_obtener(hash, "aaaaaaaaaaa");
	pa2m_afirmar(
		!elemento_obtenido,
		"intentar obtener un elemento con clave inexistente devuelve NULL");
	elemento_obtenido = hash_obtener(hash, "clave4");
	pa2m_afirmar(elemento_obtenido == elemento4,
		     "se puede obtener un elementoe");
	elemento_obtenido = hash_obtener(hash, "clave4");
	pa2m_afirmar(elemento_obtenido == elemento4,
		     "si se intenta obtener un elemento ya obtenido");






	pa2m_nuevo_grupo(
		"\n======================== CONTENER ========================");
	pa2m_afirmar(!hash_obtener(hash, "clave11"),
		     "obtener en hash nulo devuelve NULL");
	pa2m_afirmar(!hash_obtener(hash, NULL),
		     "intentar obtener una clave nula devuelve NULL");
	pa2m_afirmar(
		!hash_obtener(hash, "aaaaaaaaaaa"),
		"intentar obtener un elemento con clave inexistente devuelve NULL");
	pa2m_afirmar(hash_obtener(hash, "clave4") == elemento4,
		     "se puede obtener un elemento");






	pa2m_nuevo_grupo(
		"\n======================== CANTIDAD ========================");
	pa2m_afirmar(hash_cantidad(NULL) == 0,
		     "la cantidad de elementos de un hash nulo es 0");
	hash_t *hash_vacio = hash_crear(0);
	pa2m_afirmar(hash_cantidad(hash_vacio) == 0,
		     "la cantidad de elementos de un hash vacio es 0");
	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "la cantidad de elementos de un hash es correcta");
	hash_destruir(hash_vacio);
	hash_destruir(hash);






	pa2m_nuevo_grupo(
		"\n======================== ITERADOR INTERNO ========================");
	hash = hash_crear(3);

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;

	hash = hash_insertar(hash, "1", &valor1, NULL);
	hash = hash_insertar(hash, "2", &valor2, NULL);
	hash = hash_insertar(hash, "3", &valor3, NULL);
	pa2m_afirmar(hash_con_cada_clave(NULL, funcion_bool, elemento2) == 0,
		     "iterar en un hash nulo devuelve 0");
	pa2m_afirmar(
		hash_con_cada_clave(hash, NULL, elemento2) == 0,
		"iterar en un hash valido con una funcion nula devuelve 0");
	pa2m_afirmar(
		hash_con_cada_clave(hash, NULL, elemento2) == 0,
		"iterar en un hash valido con una funcion nula devuelve 0");
	pa2m_afirmar(
		hash_con_cada_clave(hash, funcion_bool, NULL) == 3,
		"iterar en un hash valido con una funcion valida y aux nulo funciona");
	int aux = 10;
	pa2m_afirmar(hash_con_cada_clave(hash, funcion_bool, &aux) == 3,
		     "se puede iterar el hash en su totalidad");
	pa2m_afirmar(
		hash_con_cada_clave(hash, funcion_bool, &elemento2) == 1,
		"se puede iterar el hash y que se detenga cuando la funcion devuelve false");

	hash_destruir(hash);
}

int main()
{
	pruebas();

	return pa2m_mostrar_reporte();
}
