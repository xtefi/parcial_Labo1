#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
   LinkedList* this=NULL;
   this= (LinkedList*)malloc(sizeof(LinkedList));
   if(this != NULL)
   {
	   this->size= 0;
	   this->pFirstNode= NULL;
   }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux= -1;
    if(this != NULL)
    {
    	returnAux= this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode= NULL;
    if(this != NULL && nodeIndex < ll_len(this) && nodeIndex >= 0)
    {
        pNode= this->pFirstNode;
        for(int i=0; i<nodeIndex; i++)
        {
            pNode= pNode -> pNextNode;
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nuevoNodo=(Node*)malloc(sizeof(Node)); //creo un nuevo nodo

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
    	nuevoNodo->pElement = pElement;  //apunto mi nuevo nodo a la direc pElement
    	if(nodeIndex == 0)
    	{
     			nuevoNodo->pNextNode = this->pFirstNode;  //hago que mi nuevo nodo sea cabeza
    			this->pFirstNode = nuevoNodo;             // muevo la cabeza para que apunte a mi nuevo nodo
    	}
    	else if(nodeIndex == ll_len(this) && this->pFirstNode != NULL) // agrego el nodo a la ult pos
    	{
    		Node* ultimoNodo = getNode(this, nodeIndex-1);
    		ultimoNodo->pNextNode = nuevoNodo;
    		nuevoNodo->pNextNode =NULL;
    	}
    	else if(nodeIndex < ll_len(this) && nodeIndex > 0 && this->pFirstNode != NULL)
    	{
    		Node* auxNodo = getNode(this, nodeIndex);
    		nuevoNodo->pNextNode = auxNodo->pNextNode;  //  Make next of new node as next of prev_node
    		auxNodo->pNextNode = nuevoNodo; // move the next of prev_node as new_node
       	}
    	this->size = ll_len(this)+1;
    	returnAux= 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}
/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int limite = ll_len(this);
    if(this != NULL)
    {
    	addNode(this, limite, pElement);
    	returnAux= 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNodo;
    int limite = ll_len(this);

    if(this != NULL && index >= 0 && index < limite && limite > 0)
    {
    	auxNodo = getNode(this, index);
    	if(auxNodo != NULL)
    	{
    		returnAux = auxNodo->pElement;
    	}
    }
    return returnAux;
}
/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNodo;
    int limite = ll_len(this);

    if(this != NULL && index >= 0 && index < limite && limite > 0)
    {
    	auxNodo = getNode(this, index);
    	auxNodo->pElement = pElement;
    	returnAux = 0;
    }
    return returnAux;
}
/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxNodo;
    int limite = ll_len(this);

    if(this != NULL && index >= 0 && index < limite && limite > 0)
    {
    	auxNodo = getNode(this, index);
    	if(index == 0)
    	{
    		this->pFirstNode = auxNodo->pNextNode;
    		free(auxNodo);
    	}
    	else
    	{
    		Node* anterior = getNode(this, index -1);
    		anterior->pNextNode= auxNodo->pNextNode;
    		free(auxNodo);
    	}
    	returnAux = 0;
    	this->size--;
    }
    return returnAux;
}
/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	for(int i=0 ; i<=ll_len(this) ; i++)
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }
    return returnAux;
}
/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux=0;
    }
    return returnAux;
}
/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* auxNodo;
    if(this != NULL)
    {
    	for(int i=0 ; i<=ll_len(this);i++)
    	{
    		auxNodo=getNode(this,i);
    		if(auxNodo->pElement==pElement)
    		{
    			returnAux=i;
    		}
    	}
    }
    return returnAux;
}
/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL && this->size == 0)
    {
    	returnAux = 1;
    }
    if(this != NULL && this->size > 0)
    {
    	returnAux = 0;
    }
    return returnAux;
}
/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index>=0 && index <= ll_len(this))
    {
    	addNode(this, index, pElement);
    	returnAux=0;
    }
    return returnAux;
}
/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* elemento;
    if(this != NULL && index>=0 && index<= ll_len(this))
    {
    	elemento=ll_get(this, index);
    	returnAux= elemento;
    	ll_remove(this, index);
    }
    return returnAux;
}
/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux=0;
    	if(ll_indexOf(this,pElement) !=-1)
    	{
    		returnAux=1;
    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* elemento;
    if(this != NULL && this2 != NULL)
    {
    	returnAux=1;
    	for(int i=0 ; i<=ll_len(this) ;i++)
    	{
    		elemento=ll_get(this2,i);
    		if(ll_contains(this, elemento)==0)
    		{
    			returnAux=0;
    			break;
    		}
    	}
    }
    return returnAux;
}
/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* elemento;
    if(this != NULL && from>=0 && to<=ll_len(this) && from<to)
    {
    	cloneArray=ll_newLinkedList();
    	for(int i=from; i<=to; i++)
    	{
    		elemento=ll_get(this,i);
       		ll_add(cloneArray, elemento);
       	}
    }
    return cloneArray;
}
/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    void* pElement;
    if(this !=NULL)
    {
    	cloneArray=ll_newLinkedList();
    	for(int i=0; i<=ll_len(this); i++)
    	{
    		pElement = ll_get(this, i);
    		ll_add(cloneArray, pElement);
    	}
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pElemento1;
    void* pElemento2;
    int swap;
    if(this != NULL)
    {
    	swap=0;
    	for(int i=0; i<=ll_len(this); i++)
		{
    		pElemento1=ll_get(this,i);   //guardo el elemento de la lista
    		pElemento2=ll_get(this,i+1); //guardo el elemento que le sigue a elemento1
			if(swap==1 && (((pFunc(pElemento1,pElemento2) > 0) && order == 1) || ( (pFunc(pElemento1,pElemento2) < 0) && order == 0)))
			{
				 ll_set(this, i, pElemento1);
				 ll_set(this, i+1, pElemento2);
				 swap=1;
			}
			else
			{
				continue;
			}
		}
    	returnAux=0;
    }

    return returnAux;

}
/** \brief trae los elementos del array y ejecuta una funcion por parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux=-1;
	if(this !=NULL)
	{
		for(int i=0; i<=ll_len(this); i++)
		{
			pFunc(ll_get(this,i));
			returnAux=0;
		}
	}
	return returnAux;
}

/** \brief trae los elementos del array filtrados en base al criterio dado
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (NULL) si hubo Error
                              nueva lista filtrada si salio OK
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	LinkedList* elemetosFiltrados=NULL;
	void* pElement;
	if(this != NULL && pFunc != NULL)
	{
		elemetosFiltrados=ll_newLinkedList();
		for(int i=0; i<=ll_len(this); i++)
		{
			pElement=ll_get(this,i);
			if(pFunc(pElement)==1)
			{
				ll_add(elemetosFiltrados, pElement);
			}
		}
	}
	return elemetosFiltrados;
}

/** \brief obtiene calculos dados
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (NULL) si hubo Error
                              nueva lista filtrada si salio OK
 */
int ll_reduceFloat(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux=-1;
	return returnAux;
}

int ll_reduceInt(LinkedList* this, int (*pFunc)(void*))
{
	int acumulador=0;
	void* pElement;

	if(this != NULL && pFunc != NULL)
	{
		for(int i=0 ; i<ll_len(this); i++)
		{
			pElement=ll_get(this,i);
			acumulador+=pFunc(pElement);
		}
	}

	return acumulador;
}
