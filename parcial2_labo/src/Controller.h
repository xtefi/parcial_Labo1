int controller_buscaIdLibre(LinkedList* pArrayListClientes);
int controller_ordenaId(void* pCliente1, void* pCliente2);
int controller_loadFromText(char* path , LinkedList* pArrayListClientes);
int controller_loadFromBinary(char* path , LinkedList* pArrayListClientes);
int controller_addCliente(LinkedList* pArrayListClientes);
int controller_editCliente(LinkedList* pArrayListClientes);
int controller_removeCliente(LinkedList* pArrayListClientes);
int controller_ListCliente(LinkedList* pArrayListClientes);
int controller_sortCliente(LinkedList* pArrayListClientes);
int controller_saveAsText(char* path , LinkedList* pArrayListClientes);
int controller_saveAsBinary(char* path , LinkedList* pArrayListClientes);
int controller_retornaIdCliente(LinkedList* pArrayListClientes);

int controller_addAfiche(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
int controller_loadAficheFromText(char* path , LinkedList* pArrayListAfiches);
int controller_saveAficheAsText(char* path , LinkedList* pArrayListAfiches);
int controller_ListAfiche(LinkedList* pArrayListAfiches);

