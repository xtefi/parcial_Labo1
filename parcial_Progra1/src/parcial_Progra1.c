/*
 ============================================================================
 Name        : parcial_Progra1.c
 Author      : Estefania
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "clientes.h"
#include "avisos.h"
#include "informes.h"
#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define QTY_CUSTOMER 100
#define QTY_PUBLICATION 1000

int main(void) {
	setbuf(stdout,NULL);

	int menu;
	char answer[2];
	int subMenu;
	Customer arrayCust[QTY_CUSTOMER];
	int auxIdCustomer;
	int auxIndexCustomer;
	Publication arrayPub[QTY_PUBLICATION];
	int auxIdPubli;
	int auxIndexPubli;


	if(cli_initArray(arrayCust, QTY_CUSTOMER)==0 && pub_initArray(arrayPub, QTY_PUBLICATION)==0)
	{
		printf("Arrays inicializados correctamente\n");
	}

	cli_hardcode(arrayCust,QTY_CUSTOMER, 0,&auxIdCustomer,"Monrgomery","Scott", "27331339514");
	cli_hardcode(arrayCust,QTY_CUSTOMER, 1,&auxIdCustomer,"Leonard","McCoy", "27331339515");
	cli_hardcode(arrayCust,QTY_CUSTOMER, 2,&auxIdCustomer,"Hikaru","Sulu", "27331339516");
	cli_hardcode(arrayCust,QTY_CUSTOMER, 3,&auxIdCustomer,"James Tiberuis","Kirk", "27331339517" );
	cli_hardcode(arrayCust,QTY_CUSTOMER, 4,&auxIdCustomer,"Mr","Spock", "27331339518");

	pub_hardcode(arrayPub,QTY_PUBLICATION, 0, &auxIdPubli, 0, 1, "To boldly go");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 1, &auxIdPubli, 2, 7, "where no man");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 2, &auxIdPubli, 2, 12, "has gone before");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 3, &auxIdPubli, 1, 11, "Starship Enterprise");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 4, &auxIdPubli, 1, 11, "Space");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 5, &auxIdPubli, 1, 11, "The last frontier");

	do
	{
		if(!utn_getNumero(&menu, "\n**Ingrese una opcion del menu**\n"
										"1. Alta de cliente\n"
										"2. Modificar datos de cliente\n"
										"3. Baja de cliente\n"
										"4. Publicar\n"
										"5. Pausar publicacion\n"
										"6. Reanudar publicacion\n"
										"7. Imprimir clientes\n"
										"8. Informes\n"
										"9. Salir\n", "Error, opcion invalida, reintente: \n", 1, 9, 3))
		{
			switch(menu)
			{
				case 1:
					auxIndexCustomer=cli_findEmptySlot(arrayCust,QTY_CUSTOMER);
					if(cli_addNew(arrayCust, QTY_CUSTOMER, &auxIdCustomer, auxIndexCustomer)==0)
					{
						printf("\nCliente cargado exitosamente\n");
					}
					break;

				case 2:
					cli_printArray(arrayCust, QTY_CUSTOMER);
					if(!utn_getNumero(&auxIdCustomer, "\nIngrese ID del cliente a modificar: ", "\nError, solo numeros: ", 0, QTY_CUSTOMER,1))
					{
						if(cli_update(arrayCust, QTY_CUSTOMER, auxIdCustomer)==0)
							{
								printf("Cliente actualizado correctamente.\n");
							}
						else if(cli_update(arrayCust, QTY_CUSTOMER, auxIdCustomer)!=0)
							{
								printf("\nError, ID invalido\n");
							}
					}
					break;

				case 3:
					cli_printArray(arrayCust, QTY_CUSTOMER);
					if(!utn_getNumero(&auxIdCustomer, "Ingrese ID de cliente para dar de baja: ", "Error, no esta dentro del rango, reintente", 0, 999, 2) &&
						cli_findById(arrayCust, QTY_CUSTOMER,auxIdCustomer) != -1)
					{
						pub_printByCustId(arrayPub, QTY_PUBLICATION,auxIdCustomer);
						printf("Desea elimiar este cliente y todas sus publicaciones?");
						utn_getNombre(answer, 2,"\nElija S para eliminar, N para salir: ", "Error, respuesta debe ser S o N", 1);
						if(*answer == 's' || *answer == 'S')
						{
							pub_eraseByCustId(arrayPub, QTY_PUBLICATION,auxIdCustomer);
							cli_remove(arrayCust, QTY_CUSTOMER, auxIdCustomer);
							printf("Se ha dado de baja al cliente");
						}
					}
					else
					{
						printf("Error, ID invalido");
					}
					break;

				case 4:
					cli_printArray(arrayCust, QTY_CUSTOMER);
					auxIndexPubli=pub_findEmptySlot(arrayPub, QTY_PUBLICATION);
					if(auxIndexPubli >=0 &&
					   utn_getNumero(&auxIdCustomer, "\nIngrese ID de cliente para publicar: ", "Error, reintente", 0, 999, 1) == 0 &&
					   cli_findById(arrayCust, QTY_CUSTOMER,auxIdCustomer) >= 0)
					{
						pub_addNew(arrayPub, QTY_PUBLICATION, auxIndexPubli, &auxIdPubli, auxIdCustomer);
					}
					else
					{
						printf("Error, no existe cliente con ese ID");
					}

					break;

				case 5:
					pub_printActive(arrayPub, QTY_PUBLICATION);
					if(!utn_getNumero(&auxIdPubli, "\nIngrese ID de la publicacion a pausar: ", "Error, reintente: ", 0, 999, 1) &&
						pub_findById(arrayPub, QTY_PUBLICATION, auxIdPubli) != -1)
					{
						printf("\nEsta publicacion pertenece a: \n");
						info_printOneCustByPubliID(arrayPub, QTY_PUBLICATION, arrayCust, QTY_CUSTOMER, auxIdPubli);
						utn_getNombre(answer, 2,"\nElija S para confirmar, N para salir: ", "Error, respuesta debe ser S o N", 1);
						if(*answer == 's' || *answer == 'S')
						{
							pub_pause(arrayPub, QTY_PUBLICATION, auxIdPubli);
							printf("Publicacion pausada");
						}
					}
					break;

				case 6:
					if(pub_printInactive(arrayPub, QTY_PUBLICATION) == 0 &&
					   !utn_getNumero(&auxIdPubli, "\nIngrese ID de la publicacion a reanudar: ", "Error, reintente: ", 0, 999, 1) &&
					   pub_findById(arrayPub, QTY_PUBLICATION, auxIdPubli) != -1)
					{
						printf("\nEsta publicacion pertenece a: \n");
						info_printOneCustByPubliID(arrayPub, QTY_PUBLICATION, arrayCust, QTY_CUSTOMER, auxIdPubli);
						utn_getNombre(answer, 2,"\nElija S para confirmar, N para salir: ", "Error, respuesta debe ser S o N", 1);
						if(*answer == 's' || *answer == 'S')
						{
							pub_unPause(arrayPub, QTY_PUBLICATION, auxIdPubli);
							printf("Publicacion activada");
						}
					}
					else
					{
						printf("error, no hay publicaciones pausadas o el ID es invalido\n");
					}
					break;

				case 7:
					info_printCustAndPubs(arrayPub, QTY_PUBLICATION,arrayCust, QTY_CUSTOMER);
					break;

				case 8:
					do{
						if(!utn_getNumero(&subMenu, "\nIngrese opcion: "
													"\n1) Cliente con mas avisos"
													"\n2) Cantidad de avisos pausados"
													"\n3) Rubro con mas avisos"
													"\n4) Cliente con más avisos activos"
													"\n5) Cliente con más avisos pausados."
													"\n6) Salir", "Error, reintente:", 1, 6, 1))
						{
							switch(subMenu)
							{
								case 1:
									info_mostPublish(arrayPub, QTY_PUBLICATION,  arrayCust, QTY_CUSTOMER);
									break;
								case 2:
									info_paused(arrayPub, QTY_PUBLICATION);
									break;
								case 3:
									info_maxRubro(arrayPub, QTY_PUBLICATION,  arrayCust, QTY_CUSTOMER);
									break;
								case 4:
									info_activePub(arrayPub, QTY_PUBLICATION,  arrayCust, QTY_CUSTOMER);
									break;
								case 5:
									info_pausedPub(arrayPub, QTY_PUBLICATION,  arrayCust, QTY_CUSTOMER);
									break;
							}//switch subMenu
						}//if

					}while(subMenu != 6);
					break; // case 8

				case 9:
					break;
				}// switch menu
		}//if get menu
	}while(menu != 9);

	return EXIT_SUCCESS;
}
