#ifndef DIFFERENTPOP_H
#define DIFFERENTPOP_H

#include "List.h"

ErrorNumbers listPop(ListInfo* my_list, int element_number, ListElem_t* value, FILE* log_file);
ErrorNumbers findElement(ListInfo* my_list, int* element_number, ListElem_t value);

#endif // DIFFERENTPOP_H
