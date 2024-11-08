#include "../include/ErrorHandler.h"
#include "../include/List.h"
#include "../include/CtorAndDtor.h"
#include "../include/DifferentPushs.h"
#include "../include/DifferentPop.h"
#include "../include/Verificator.h"
#include "../include/WorkWithLogFile.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 2;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_NUMBER_OF_ARG_ERROR, __PRETTY_FUNCTION__);
        return _NUMBER_OF_ARG_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    FILE* log_file = NULL;
    CHECK_ERROR(openLogFile(&log_file, &argv[1]));

    struct ListInfo my_list = {};
    CHECK_ERROR(listCtor(&my_list, log_file));

    CHECK_ERROR(listPushHead(&my_list, 10, log_file));
    CHECK_ERROR(listPushHead(&my_list, 20, log_file));
    CHECK_ERROR(listPushHead(&my_list, 30, log_file));
    CHECK_ERROR(listPushHead(&my_list, 40, log_file));
    CHECK_ERROR(listPushHead(&my_list, 50, log_file));
    CHECK_ERROR(listPushBefore(&my_list, 1, 5, log_file));
    CHECK_ERROR(listPushAfter(&my_list, 5, 60, log_file));
    CHECK_ERROR(listPushAfter(&my_list, 3, 35, log_file));

    int elem_pop = 0;
    CHECK_ERROR(listPop(&my_list, 4, &elem_pop, log_file));

    CHECK_ERROR(findElement(&my_list, &elem_pop, 50));

    printf("%d\n", elem_pop);

    CHECK_ERROR(listDtor(&my_list, log_file));

    printf("DONE\n");

    fclose(log_file);

    return 0;
}
