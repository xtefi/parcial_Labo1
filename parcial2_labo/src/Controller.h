int controller_buscaIdLibre(LinkedList* pArrayListClientes);
int controller_ordenaId(void* pCliente1, void* pCliente2);
int controller_loadFromText(char* path , LinkedList* pArrayListClientes);
int controller_addCliente(LinkedList* pArrayListClientes);
int controller_ListCliente(LinkedList* pArrayListClientes);
int controller_sortCliente(LinkedList* pArrayListClientes);
int controller_saveAsText(char* path , LinkedList* pArrayListClientes);
int controller_retornaIdCliente(LinkedList* pArrayListClientes);

int controller_addAfiche(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
int controller_loadAficheFromText(char* path , LinkedList* pArrayListAfiches);
int controller_saveAficheAsText(char* path , LinkedList* pArrayListAfiches);
int controller_printAfiche(LinkedList* pArrayListAfiches);
int controller_retornaIdAfiche(LinkedList* pArrayListAfiches);
int controller_editAfiche(LinkedList* pArrayListAfiches);

void controller_cobrarVentas(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
int controller_filtraListaAfichesConClientes(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
int controller_filtraCobradas(char* path,LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
int controller_filtraSinCobrar(char* path,LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes);
