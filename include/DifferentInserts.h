#ifndef DIFFERENTINSERTS_H
#define DIFFERENTINSERTS_H

#include "List.h"

ErrorNumbers listInsertBefore(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file);
ErrorNumbers listInsertAfter(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file);
ErrorNumbers listInsertHead(ListInfo* my_list, ListElem_t value, FILE* log_file);
ErrorNumbers listInsertTail(ListInfo* my_list, ListElem_t value, FILE* log_file);

#endif // DIFFERENTINSERTS_H
