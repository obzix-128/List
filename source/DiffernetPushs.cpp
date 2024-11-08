#include "../include/DifferentPushs.h"
#include "../include/Verificator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers listPushHead(ListInfo* my_list, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file));

    CHECK_ERROR(listPush(my_list, value, 0, my_list->next[0]));

    CHECK_ERROR(listDump(my_list, log_file));

    return check_error;
}

ErrorNumbers listPushTail(ListInfo* my_list, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;
    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file));

    CHECK_ERROR(listPush(my_list, value, my_list->prev[0], 0));

    CHECK_ERROR(listDump(my_list, log_file));

    return check_error;
}

ErrorNumbers listPushBefore(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;
    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file));

    CHECK_ERROR(listPush(my_list, value, element_number, my_list->next[element_number]));

    CHECK_ERROR(listDump(my_list, log_file));

    return check_error;
}

ErrorNumbers listPushAfter(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;
    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file));

    CHECK_ERROR(listPush(my_list, value, my_list->prev[element_number], element_number));

    CHECK_ERROR(listDump(my_list, log_file));

    return check_error;
}

static ErrorNumbers listPush(ListInfo* my_list, ListElem_t value, int element_Before, int element_after)
{
    int empty_cell = my_list->free;
    my_list->free = my_list->next[empty_cell];

    my_list->data[empty_cell] = value;
    my_list->next[empty_cell] = my_list->next[element_Before];
    my_list->next[element_Before] = empty_cell;
    my_list->prev[empty_cell] = my_list->prev[element_after];
    my_list->prev[element_after] = empty_cell;

    my_list->size += 1;

    return _NO_ERROR;
}
