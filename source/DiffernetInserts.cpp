#include "../include/DifferentInserts.h"
#include "../include/Verificator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"
static ErrorNumbers listInsert(ListInfo* my_list, ListElem_t value, int element_Before,
                               int element_after); //TODO: Куда девать?


ErrorNumbers listInsertHead(ListInfo* my_list, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    CHECK_ERROR(listInsert(my_list, value, 0, my_list->next[0]));

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, my_list->next[0], _INSERTING_CELL));

    return check_error;
}

ErrorNumbers listInsertTail(ListInfo* my_list, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    CHECK_ERROR(listInsert(my_list, value, my_list->prev[0], 0));

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, my_list->prev[0], _INSERTING_CELL));

    return check_error;
}

ErrorNumbers listInsertBefore(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    CHECK_ERROR(listInsert(my_list, value, element_number, my_list->next[element_number]));

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, my_list->next[element_number],
                         _INSERTING_CELL));

    return check_error;
}

ErrorNumbers listInsertAfter(ListInfo* my_list, int element_number, ListElem_t value, FILE* log_file)
{
    ErrorNumbers check_error = _NO_ERROR;
    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    CHECK_ERROR(listInsert(my_list, value, my_list->prev[element_number], element_number));

    CHECK_ERROR(listVerificator(my_list));
    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, my_list->prev[element_number], _INSERTING_CELL));

    return check_error;
}

static ErrorNumbers listInsert(ListInfo* my_list, ListElem_t value, int element_before, int element_after)
{
    int empty_cell = my_list->free;
    my_list->free = my_list->next[empty_cell];

    my_list->data[empty_cell] = value;
    my_list->next[empty_cell] = my_list->next[element_before];
    my_list->next[element_before] = empty_cell;
    my_list->prev[empty_cell] = my_list->prev[element_after];
    my_list->prev[element_after] = empty_cell;

    my_list->size += 1;

    return _NO_ERROR;
}
