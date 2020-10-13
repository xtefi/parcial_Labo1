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
	int flag=0;
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
	cli_hardcode(arrayCust,QTY_CUSTOMER, 2,&auxIdCustomer,"Leonard","McCoy", "27331339515");
	cli_hardcode(arrayCust,QTY_CUSTOMER, 3,&auxIdCustomer,"Hikaru","Sulu", "27331339516");
	cli_hardcode(arrayCust,QTY_CUSTOMER, 4,&auxIdCustomer,"James Tiberuis","Kirk", "27331339517" );
	cli_hardcode(arrayCust,QTY_CUSTOMER, 5,&auxIdCustomer,"Mr","Spock", "27331339518");

	pub_hardcode(arrayPub,QTY_PUBLICATION, 0, &auxIdPubli, 3, 1, "To boldly go");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 1, &auxIdPubli, 2, 7, "where no man");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 2, &auxIdPubli, 2, 12, "has gone before");
	pub_hardcode(arrayPub,QTY_PUBLICATION, 3, &auxIdPubli, 2, 11, "Starship Enterprise");

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
										"9. Salir", "Error, opcion invalida, reintente: \n", 1, 9, 3))
		{
			switch(menu)
			{
				case 1:
/*done	    1) Alta de cliente: Se da de alta un cliente con nombre, apellido, y cuit.
		       Se generará un ID único para este cliente que se imprimirá por pantalla */
					auxIndexCustomer=cli_findEmptySlot(arrayCust,QTY_CUSTOMER);
					if(cli_addNew(arrayCust, QTY_CUSTOMER, &auxIdCustomer, auxIndexCustomer)==0)
					{
						printf("\nCliente cargado exitosamente\n");
						flag=0;
					}
					break;

				case 2:
/* done		 2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá
		        cambiar el nombre, el apellido y el cuit. */
					if(flag == 0)
					{
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

					}
					else
					{
						printf("\nError, no hay clientes cargados. Intente con la opcion 1 del menu");
					}
					break;

				case 3:
/* Done		3) Baja de cliente: Se ingresa el ID del cliente y se listarán todas
		       las publicaciones de dicho cliente. Luego se preguntará si se quiere
			   confirmar la eliminación, la cual implicará la eliminación de todas
			   las publicaciones y del cliente. */
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
/* Done		 4) Publicar: Permitirá crear un nuevo aviso. Se pedirán los siguientes
				datos: ID de cliente, número de rubro, texto del aviso (64 caracteres).
				Se generará automáticamente un identificador numérico para el aviso y
				se imprimirá en pantalla.*/
					if(flag == 0)
					{
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
					}
					break;


				case 5:
/* done		 5) Pausar publicación: Se pedirá el ID de la publicación y se imprimirá
			    la información del cliente al que pertenece, luego se pedirá
				confirmación para cambiarse de estado y se cambiará al estado "pausada".*/
					pub_printActive(arrayPub, QTY_PUBLICATION);
					if(!utn_getNumero(&auxIdPubli, "\nIngrese ID de la publicacion a pausar: ", "Error, reintente: ", 0, 999, 1))
					{
						info_printOneCustByPubliID(arrayPub, QTY_PUBLICATION, arrayCust, QTY_CUSTOMER, auxIdPubli);
						utn_getNombre(answer, 2,"\nElija S para eliminar, N para salir: ", "Error, respuesta debe ser S o N", 1);
						if(*answer == 's' || *answer == 'S')
						{
							pub_pause(arrayPub, QTY_PUBLICATION, auxIdPubli);
							printf("Publicacion pausada");
						}
					}
					break;

				case 6:
/*Done		  6) Reanudar publicación: Se pedirá el ID de la publicación y se imprimirá
				 la información del cliente al que pertenece, luego se pedirá confirmación
				 para cambiarse de estado y se cambiará al estado "activa".*/

					if(pub_printInactive(arrayPub, QTY_PUBLICATION) == 0 &&
					   !utn_getNumero(&auxIdPubli, "\nIngrese ID de la publicacion a reanudar: ", "Error, reintente: ", 0, 999, 1) &&
					   pub_findById(arrayPub, QTY_PUBLICATION, auxIdPubli) >= 0)
					{
						info_printOneCustByPubliID(arrayPub, QTY_PUBLICATION, arrayCust, QTY_CUSTOMER, auxIdPubli);
						utn_getNombre(answer, 2,"\nElija S para eliminar, N para salir: ", "Error, respuesta debe ser S o N", 1);
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
/*Done		  7) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus
			  	 datos junto con la cantidad de avisos activos que posee. */
					info_printCustAndPubs(arrayPub, QTY_PUBLICATION,arrayCust, QTY_CUSTOMER);
					break;

				case 8: /*8) Informar: Un submenú con las siguientes opciones:
						   a) Cliente con más avisos.
			b listo		   b) Cantidad de avisos pausados.
						   c) Rubro con mas avisos. */
					do{
						if(!utn_getNumero(&subMenu, "\nIngrese opcion: "
													"\n1) Cliente con mas avisos"
													"\n2) Cantidad de avisos pausados"
													"\n3) Rubro con mas avisos"
													"\n4) Salir", "Error", 1, 4, 1))
						{
							switch(subMenu)
							{
								case 1:
									info_clientWithHighestPubli(arrayPub, QTY_PUBLICATION,  arrayCust, QTY_CUSTOMER);
									break;
								case 2:
									info_paused(arrayPub, QTY_PUBLICATION);
									break;
								case 3:
									break;
							}//switch subMenu
						}//if

					}while(subMenu != 4);

					break; // case 8
				}// switch menu
		}//if get menu
	}while(menu != 9);

	return EXIT_SUCCESS;
}
