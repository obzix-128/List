#ifndef DIFFERENTGET_H
#define DIFFERENTGET_H

#include "List.h"

ErrorNumbers listGet(ListInfo* my_list, int element_number, ListElem_t* value, FILE* log_file);
ErrorNumbers findElement(ListInfo* my_list, int* element_number, ListElem_t value);

#endif // DIFFERENTGET_H
