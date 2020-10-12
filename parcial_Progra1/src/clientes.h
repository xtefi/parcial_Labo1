/*
 * clientes.h
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */

#ifndef CLIENTES_H_
#define CLIENTES_H_

#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define CUIT_SIZE 12

typedef struct
{
	int id;
	char name[NAME_SIZE];
	char lastName[LASTNAME_SIZE];
	char cuit[CUIT_SIZE];
	int isEmpty;
}Customer;

int cli_initArray(Customer* array, int len);
int cli_findEmptySlot(Customer* array, int len);
int cli_addNew(Customer* array, int len, int* id, int index);
int cli_printArray(Customer* array, int len);
int cli_printOne(Customer* array);
int cli_findById(Customer* array, int len, int value);
int cli_remove(Customer* array, int len, int id);
int cli_sortArray(Customer* array, int len);
int cli_sortByName(Customer* array,int len);
int cli_update(Customer* array, int len, int value);
int cli_hardcode(Customer* array,int len, int index, int* id,char* name,char* lastName, char* cuit);

#endif /* CLIENTES_H_ */
