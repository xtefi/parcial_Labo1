#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NOMBRE_LEN 51
#define CUIT_LEN 12

typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    char apellido[NOMBRE_LEN];
    char cuit[CUIT_LEN];
}Cliente;

Cliente* cliente_new();
Cliente* cliente_newParametros(char* idStr,char* nombreStr,char* apellidoStr, char* cuitStr);
Cliente* cli_newParametrosBin(Cliente this);
int cli_Add(Cliente* this[]);
void cli_delete(Cliente* this);

int cli_setId(Cliente* this,int id);
int cli_getId(Cliente* this,int* id);
int cli_setIdTxt(Cliente* this,char* id);
int cli_getIdTxt(Cliente* this,char* id);

int cli_setNombre(Cliente* this,char* nombre);
int cli_getNombre(Cliente* this,char* nombre);

int cli_setApellido(Cliente* this,char* apellido);
int cli_getApellido(Cliente* this,char* apellido);

int cli_setCuit(Cliente* this,char* cuit);
int cli_getCuit(Cliente* this,char* apellido);

int cli_ordenaNombre(void* this1, void* this2);

#endif // employee_H_INCLUDED
