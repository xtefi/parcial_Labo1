/*
 * informes.h
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include "avisos.h"
#include "clientes.h"

int info_printPubs(Customer* arrayCust, int custLen, Publication* arrayPub, int pubLen);
int info_paused(Publication* arrayPub, int pubLen);
int info_printOneCustByPubliID(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust, int idPubli);
int info_printCustAndPubs(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust);
int info_clientWithHighestPubli(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust);

#endif /* INFORMES_H_ */
