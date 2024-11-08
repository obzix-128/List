#include "../include/CtorAndDtor.h"
#include "../include/WorkWithLogFile.h"
#include "../include/ErrorHandler.h"


ErrorNumbers listCtor(ListInfo* my_list, FILE* log_file)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    my_list->capacity = MIN_LIST_SIZE;
    my_list->size = 0;

    my_list->data = (ListElem_t*) calloc(my_list->capacity, sizeof(ListElem_t));
    CHECK_NULL_ADDR_ERROR(my_list->data, _CALLOC_ERROR);

    const int EMPTY_CELL = -1;
    for(int i = 0; i < my_list->capacity; i++)
    {
        my_list->data[i] = EMPTY_CELL;
    }
    *my_list->data = POISON_VALUE;

    my_list->next = (int*) calloc(my_list->capacity, sizeof(int));
    CHECK_NULL_ADDR_ERROR(my_list->next, _CALLOC_ERROR);

    my_list->next[0] = 0;
    for(int i = 1; i < my_list->capacity; i++)
    {
        my_list->next[i] = i + 1;
    }
    my_list->next[my_list->capacity - 1] = 0;

    const int FIRST_FREE_CELL = 1;
    my_list->free = FIRST_FREE_CELL;

    my_list->prev = (int*) calloc(my_list->capacity, sizeof(int));
    CHECK_NULL_ADDR_ERROR(my_list->prev, _CALLOC_ERROR);

    for(int i = 0; i < my_list->capacity; i++)
    {
        my_list->prev[i] = EMPTY_CELL;
    }
    *my_list->prev = 0;

    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    return check_error;
}

ErrorNumbers listDtor(ListInfo* my_list, FILE* log_file)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    my_list->capacity = 0;
    my_list->size = 0;
    my_list->free = 0;

    memset(my_list->data, POISON_VALUE, sizeof(ListElem_t) * my_list->capacity);
    memset(my_list->next, POISON_VALUE, sizeof(ListElem_t) * my_list->capacity);
    memset(my_list->prev, POISON_VALUE, sizeof(ListElem_t) * my_list->capacity);

    free(my_list->data);
    free(my_list->next);
    free(my_list->prev);

    my_list->data = NULL;
    my_list->next = NULL;
    my_list->prev = NULL;

    my_list->capacity = POISON_VALUE;

    return check_error;
}
