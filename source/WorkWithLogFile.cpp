#include "../include/WorkWithLogFile.h"
#include "../include/ErrorHandler.h"


ErrorNumbers openLogFile(FILE** log_file, const char** log_file_name)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(log_file_name, _NULL_ADDRESS_ERROR);

    *log_file = fopen(*log_file_name, "w");
    CHECK_NULL_ADDR_ERROR(*log_file, _OPEN_ERROR);

    fprintf(*log_file, "<pre>\n");

    return _NO_ERROR;
}

ErrorNumbers listDump(ListInfo* my_list, FILE* log_file)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(log_file, "my_list [%p]\n", my_list);

    if(my_list->data != NULL)
    {
        fprintf(log_file, "my_list->data [%p]\n", my_list->data);
    }
    else
    {
        fprintf(log_file, "my_list->data [BROKEN ADDRESS]\n");
    }

    fprintf(log_file, "my_list->capacity [%p] = %d\n", &my_list->capacity, my_list->capacity);

    fprintf(log_file, "my_list->size [%p] = %d\n", &my_list->size, my_list->size);

    fprintf(log_file, "my_list->free [%p] = %d\n", &my_list->free, my_list->free);

    if(my_list->capacity > 0 && my_list->data != NULL)
    {
        fprintf(log_file, "my_list->data:\n");
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", i);
        }
        fprintf(log_file, "\n");
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", my_list->data[i]);
        }
        fprintf(log_file, "\n");
    }

    if(my_list->capacity > 0 && my_list->next != NULL)
    {
        fprintf(log_file, "my_list->next [%p]\n", my_list->next);
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", i);
        }
        fprintf(log_file, "\n");
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", my_list->next[i]);
        }
        fprintf(log_file, "\n");
    }

    if(my_list->capacity > 0 && my_list->prev != NULL)
    {
        fprintf(log_file, "my_list->prev [%p]\n", my_list->prev);
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", i);
        }
        fprintf(log_file, "\n");
        for(int i = 0; i < my_list->capacity; i++)
        {
            fprintf(log_file, "%4d ", my_list->prev[i]);
        }
        fprintf(log_file, "\n");
    }

    fprintf(log_file, "\n");

    CHECK_ERROR(buildGraphs(my_list, log_file));

    fprintf(log_file, "\n");

    return check_error;
}

ErrorNumbers buildGraphs(ListInfo* my_list, FILE* log_file)
{
    CHECK_NULL_ADDR_ERROR(my_list, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);

    static int counter = 0;

    const int FILE_NAME_SIZE = 100;
    char file_name[FILE_NAME_SIZE] = {};
    char command[FILE_NAME_SIZE] = {};

    sprintf(file_name, "image/Graf%d.txt", counter);

    FILE* file_to_write = fopen(file_name, "w");
    CHECK_NULL_ADDR_ERROR(file_to_write, _NULL_ADDRESS_ERROR);

    fprintf(file_to_write, "digraph\n");
    fprintf(file_to_write, "{\n");

    fprintf(file_to_write, "rankdir = LR;\n");

    fprintf(file_to_write, "{\n");

    fprintf(file_to_write, "{\n");

    fprintf(file_to_write, "node[shape = plaintext];\n");
    fprintf(file_to_write, "edge[color = white];\n");

    for(int i = 0; i < my_list->capacity; i++)
    {
        fprintf(file_to_write, "_%d_[label = \" \"]\n", i);
    }

    fprintf(file_to_write, "_0_");
    for(int i = 1; i < my_list->capacity; i++)
    {
        fprintf(file_to_write, "->_%d_", i);
    }

    fprintf(file_to_write, "}\n");

    for(int i = 0, j = 0; j <= my_list->size; i = my_list->next[i], j++)
    {
        fprintf(file_to_write, "_%d[shape = record, style = \"filled\" fillcolor = \"#bbffff\", "
                "label = \" ip = %d | data = %d | next = %d | prev = %d \"]\n",
                i, i, my_list->data[i], my_list->next[i], my_list->prev[i]);
    }

    for(int i = my_list->free, j = my_list->size; j < my_list->capacity - 1; i = my_list->next[i], j++)
    {
        fprintf(file_to_write, "_%d[shape = record, style = \"filled\" fillcolor = \"#b0ffb0\", "
                "label = \" ip = %d | data = %d | next = %d | prev = %d \"]\n",
                i, i, my_list->data[i], my_list->next[i], my_list->prev[i]);
    }

    fprintf(file_to_write, "{\n");
    fprintf(file_to_write, "edge[color = \"#50a0ff\"];\n");

    fprintf(file_to_write, "_%d", my_list->next[0]);
    for(int i = my_list->next[0]; my_list->next[i] != 0; i = my_list->next[i])
    {
        fprintf(file_to_write, "->_%d", my_list->next[i]);
    }
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "}\n");

    fprintf(file_to_write, "{\n");
    fprintf(file_to_write, "edge[color = \"red\"];\n");

    fprintf(file_to_write, "_%d", my_list->prev[0]);
    for(int i = my_list->prev[0]; my_list->prev[i] != 0; i = my_list->prev[i])
    {
        fprintf(file_to_write, "->_%d", my_list->prev[i]);
    }
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "}\n");

    fprintf(file_to_write, "{\n");
    fprintf(file_to_write, "edge[color = \"#30a030\"];\n");

    fprintf(file_to_write, "_%d", my_list->free);
    for(int i = my_list->free; my_list->next[i] != 0; i = my_list->next[i])
    {
        fprintf(file_to_write, "->_%d", my_list->next[i]);
    }
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "}\n");

    int column_number = 0;

    fprintf(file_to_write, "{rank = same; \"_0\"; \"_%d_\";}\n", column_number);
    column_number += 1;
    for(int i = 0; my_list->next[i] != 0; i = my_list->next[i])
    {
        fprintf(file_to_write, "{rank = same; \"_%d\"; \"_%d_\";}\n", my_list->next[i], column_number);
        column_number += 1;
    }

    fprintf(file_to_write, "{rank = same; \"_%d\"; \"_%d_\";}\n", my_list->free, column_number);
    column_number += 1;
    for(int i = my_list->free; my_list->next[i] != 0; i = my_list->next[i])
    {
        fprintf(file_to_write, "{rank = same; \"_%d\"; \"_%d_\";}\n", my_list->next[i], column_number);
        column_number += 1;
    }
    fprintf(file_to_write, "\n");

    fprintf(file_to_write, "}\n");

    fprintf(file_to_write, "HEAD[shape = \"octagon\", style = \"filled\" fillcolor = \"#ffffbb\"];\n");
    fprintf(file_to_write, "TAIL[shape = \"octagon\", style = \"filled\" fillcolor = \"#ffffbb\"];\n");
    fprintf(file_to_write, "FREE[shape = \"octagon\", style = \"filled\" fillcolor = \"#ffffbb\"];\n");

    fprintf(file_to_write, "HEAD->_%d\n", my_list->next[0]);
    fprintf(file_to_write, "TAIL->_%d\n", my_list->prev[0]);
    fprintf(file_to_write, "FREE->_%d\n", my_list->free);

    fprintf(file_to_write, "}\n");

    fclose(file_to_write);

    sprintf(file_name, "image/Graf%d", counter);

    fprintf(log_file, "<img src=\"%s.png\">", file_name);

    sprintf(command, "dot %s.txt -T png -o %s.png", file_name, file_name);

    system(command);

    sprintf(file_name, "image/Graf%d.html", counter);

    counter += 1;

    return _NO_ERROR;
}
