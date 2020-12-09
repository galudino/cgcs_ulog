/*!
    \file       cgcs_ulog.c
    \brief      Source file for 'pretty-printing' console messages, user logs

    \author     Gemuele Aludino
    \brief      09 Dec 2020
 */

#include "cgcs_ulog.h"

#include <string.h>

bool ulog_attrs_disable[] = {false, false, false, false, false, false, false};

/*!
    Utility function for debugging/error messages
 
    \param[in]      dest        stream destination
    \param[in]      level       literals "BUG", "ERROR", "WARNING", or "LOG"
    \param[in]      file        macro __FILE__ is to be used here (by client)
    \param[in]      func        macro __func__ is to be used here
    \param[in]      line        macro __LINE__ is to be used here
    \param[in]      fmt         formatting to be used
    
    \return         character count of buffer (from fprintf)
 */
int cgcs_ulog(FILE *dest, 
              const char *level, 
              const char *file, 
              const char *func,
              long double line, 
              const char *fmt, ...) {

    char buffer[4096];
    char temp[256];

    const char *color = KNRM;
    const char *blink = "";

    bool found = false;
    bool is_integer = false;
    bool is_currency = *file == '$';

    int j = 0;

    if (strcmp(level, "[BUG]") == 0) {
        color = KYEL_b;
        found = true;
    }

    if (found == false) {
        if (strcmp(level, "[LOG]") == 0) {
            color = KCYN_b;
            found = true;
        }
    }

    if (found == false) {
        if (strcmp(level, "[ERROR]") == 0) {
            color = KRED_b;
            blink = KBNK;
            found = true;
        }
    }

    if (found == false) {
        if (strcmp(level, "[WARNING]") == 0) {
            color = KMAG_b;
            blink = KBNK;
        }
    }

    sprintf(temp, "%Lf", line);

    /* char digit = strchr(temp, '.'); */

    is_integer = line / (long long int)(line) == 1.000000 || line == 0.00000;
    is_integer = is_currency ? false : is_integer;

    if (ulog_attrs_disable[DATE] == false) {
        char date[1024];
        sprintf(date, "%s%s%s ", KGRY, __DATE__, KNRM);

        j += sprintf(buffer + j, "%s", date);
    }

    if (ulog_attrs_disable[TIME] == false) {
        char time[1024];
        sprintf(time, "%s%s%s ", KGRY, __TIME__, KNRM);

        j += sprintf(buffer + j, "%s", time);
    }

    if (ulog_attrs_disable[LEVEL] == false) {
        char leveltype[1024];
        sprintf(leveltype, "%s%s%s%s ", blink, color, level, KNRM);

        j += sprintf(buffer + j, "%s", leveltype);
    }

    if (ulog_attrs_disable[FILENAME] == false && ulog_attrs_disable[LINE]) {
        char filename[1024];
        sprintf(filename, "[%s] ", file);

        j += sprintf(buffer + j, "%s", filename);
    } else if (ulog_attrs_disable[FILENAME] &&
               ulog_attrs_disable[LINE] == false) {
        char linenumber[1024];

        if (is_integer) {
            sprintf(linenumber, "[%lli] ", (long long int)(line));
        } else {
            if (is_currency) {
                sprintf(linenumber, "[%0.2Lf] ", line);
            } else {
                sprintf(linenumber, "[%Lf] ", line);
            }
        }

        j += sprintf(buffer + j, "%s", linenumber);
    } else if (ulog_attrs_disable[FILENAME] == false &&
               ulog_attrs_disable[LINE] == false) {
        char fileline[1024];

        if (is_integer) {
            sprintf(fileline, "[%s:%lli] ", file, (long long int)(line));
        } else {
            if (is_currency) {
                sprintf(fileline, "[%s%0.2Lf] ", file, line);
            } else {
                sprintf(fileline, "[%s:%Lf] ", file, line);
            }
        }

        j += sprintf(buffer + j, "%s", fileline);
    }

    if (ulog_attrs_disable[FUNCTION] == false) {
        char function[1024];
        sprintf(function, "%s%s", KCYN, func);

        j += sprintf(buffer + j, "%s", function);
    }

    if (ulog_attrs_disable[FUNCTION] == false &&
        ulog_attrs_disable[MESSAGE] == false) {
        j += sprintf(buffer + j, "%s", " ");
    }

    if (ulog_attrs_disable[MESSAGE] == false) {
        char message[4096];
        va_list args;

        va_start(args, fmt);
        vsprintf(message, fmt, args);
        va_end(args);

        j += sprintf(buffer + j, "%s%s%s", KNRM_b, message, KNRM);
    }

    return fprintf(dest, "%s\n", buffer);
}
