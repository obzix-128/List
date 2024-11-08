#include "../include/DifferentGet.h"
#include "../include/Verificator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers listGet(ListInfo* my_list, int element_number, ListElem_t* value, FILE* log_file)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(value, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);

    if(element_number <= 0 &&
       element_number > my_list->capacity &&
       my_list->prev[element_number] == -1)
    {
        return _LIST_GET_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, element_number, _DELETING_CELL));

    *value = my_list->data[element_number];
    my_list->data[element_number] = -1;

    my_list->prev[my_list->next[element_number]] = my_list->prev[element_number];
    my_list->next[my_list->prev[element_number]] = my_list->next[element_number];

    my_list->next[element_number] = my_list->free;
    my_list->free = element_number;

    my_list->prev[element_number] = -1;

    my_list->size -= 1;

    CHECK_ERROR(listVerificator(my_list));

    CHECK_ERROR(listDump(my_list, log_file, __PRETTY_FUNCTION__, -1, _STATUS_IS_UNCHANGED));

    return check_error;
}

ErrorNumbers findElement(ListInfo* my_list, int* element_number, ListElem_t value)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    CHECK_ERROR(listVerificator(my_list));

    for(int i = 1; i < my_list->capacity; i++)
    {
        if(my_list->data[i] == value)
        {
            *element_number = i;

            CHECK_ERROR(listVerificator(my_list));

            return check_error;
        }
    }
    fprintf(stdout, "An element with this value could not be found\n");

    CHECK_ERROR(listVerificator(my_list));

    return check_error;
}
