#include "../include/Verificator.h"


ErrorNumbers listVerificator(ListInfo* my_list)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_list->data, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_list->next, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(my_list->prev, _NULL_ADDRESS_ERROR);

    if(my_list->capacity <= 0)
    {
        return _VER_FOUND_ERROR;
    }

    if(my_list->size > my_list->capacity || my_list->size < 0)
    {
        return _LIST_SIZE_ERROR;
    }

    if(my_list->free > my_list->capacity || my_list->free <= 0)
    {
        return _LIST_FREE_ERROR;
    }

    int cell_value = 0;
    int counter = 0;
    do
    {
        if(cell_value != my_list->prev[my_list->next[cell_value]])
        {
            return _NOT_MIRRORED_ERROR;
        }

        cell_value = my_list->next[cell_value];

        counter++;

        if(counter >= my_list->capacity)
        {
            return _LOOP_ERROR;
        }

    } while(cell_value != 0);

    return _NO_ERROR;
}
