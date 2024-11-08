#ifndef WORKWITHLOGFILE_H
#define WORKWITHLOGFILE_H

#include "List.h"

ErrorNumbers openLogFile(FILE** log_file, const char** log_file_name);

ErrorNumbers listDump(ListInfo* my_list, FILE* dump_file);
ErrorNumbers buildGraphs(ListInfo* my_list, FILE* log_file);

#endif // WORKWITHLOGFILE_H
