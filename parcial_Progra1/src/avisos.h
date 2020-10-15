/*
 * avisos.h
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */

#ifndef AVISOS_H_
#define AVISOS_H_

#define TEXT_LEN 65
#include "clientes.h"
typedef struct
{
	char text[TEXT_LEN];
	int idClient;
	int idPubli;
	int rubro;
	int isPaused;
	int isEmpty;
}Publication;

int pub_initArray(Publication* array, int len);
int pub_findEmptySlot(Publication* array, int len);
int pub_addNew(Publication* array, int len, int index, int* id, int idCust);
int pub_printOne(Publication* array);
int pub_findById(Publication* array, int len, int value);
int pub_pause(Publication* array, int len, int idPubli);
int pub_unPause(Publication* array, int len, int idPubli);
int pub_hardcode(Publication* array,int len, int index, int* idPub, int idCli, int rubro, char* text);
int pub_printArray(Publication* array, int len);
int pub_printActive(Publication* array, int len);
int pub_printInactive(Publication* array, int len);
int pub_printByCustId(Publication* array, int len, int idCust);
int pub_eraseByCustId(Publication* array, int len, int idCust);
int pub_sortArray(Publication* arrayPub, int len);
int pub_contador(Publication* array, int len, int idCustomer);
int pub_contadorRubro(Publication* array, int len, int rubro);

#endif /* AVISOS_H_ */
