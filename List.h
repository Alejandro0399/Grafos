#ifndef LIST_H_
#define LIST_H_

typedef struct  strList * List;
typedef void * Type;
typedef enum {False, True}bool;

List list_create(void(*destructor)(void*));

void list_destroy(List);
int  list_size(List);
void list_add(List, Type);
Type list_getdata(List, int p);
void list_set(List, Type, int p);
Type list_remove(List, int p);
void print(List);

#endif /* LIST_H_ */
