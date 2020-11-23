/*
 ============================================================================
 Name        : parcial2_labo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Controller.h"
#include "utn.h"
int main(void) {

	setbuf(stdout,NULL);
    int menu;
    LinkedList* listaClientes = ll_newLinkedList();
    LinkedList* listaAfiches = ll_newLinkedList();
    controller_loadFromText("clientes.txt", listaClientes);
  //  controller_loadAficheFromText("ventas.txt", listaAfiches);
	do
	{
		if(!utn_getNumero(&menu, "\n1. Agregar cliente"
				"\n2. Vender afiches"
				"\n3. Modificar venta"
				"\n4. Cobrar venta"
				"\n5. Generar informe de cobros"
				"\n6. Generar informe de deudas"
				"\n7. Generar estadisticas"
				"\n8. Salir","\nError, reintente", 1, 8,2))
		{
			switch(menu)
			{
				case 1:

					if(!controller_addCliente(listaClientes))
						{
						controller_saveAsText("clientes.txt", listaClientes);
						}
					break;
				case 2:
					if(!controller_addAfiche(listaAfiches, listaClientes))
					{
						controller_saveAficheAsText("ventas.txt",listaAfiches);
					}
					break;
				case 3:
					controller_ListCliente(listaClientes);
					break;
				case 4:
					controller_loadAficheFromText("ventas.txt", listaAfiches);
					controller_ListAfiche(listaAfiches);
					break;
			}

		}
	}while(menu !=8);

	return EXIT_SUCCESS;
}
