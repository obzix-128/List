#include "../include/ErrorHandler.h"
#include "../include/List.h"
#include "../include/CtorAndDtor.h"
#include "../include/DifferentInserts.h"
#include "../include/DifferentGet.h"
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

    char choto[10] = {'o', 'p', 'a', '\n'};

    CHECK_ERROR(listInsertHead(&my_list, choto, log_file));

    CHECK_ERROR(listDtor(&my_list, log_file));

    printf("DONE\n");

    fclose(log_file);

    return 0;
}
