#ifndef DIFFERENTPUSHS_H
#define DIFFERENTPUSHS_H

#include "List.h"

ErrorNumbers listPushBefore(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file);
ErrorNumbers listPushAfter(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file);
ErrorNumbers listPushHead(ListInfo* my_list, ListElem_t value, FILE* log_file);
ErrorNumbers listPushTail(ListInfo* my_list, ListElem_t value, FILE* log_file);
static ErrorNumbers listPush(ListInfo* my_list, ListElem_t value, int element_Before, int element_after);

#endif // DIFFERENTPUSHS_H
