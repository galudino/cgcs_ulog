/*!
    \file       cgcs_ulog_test.c
    \brief      Test source file for cgcs_ulog

    \author     Gemuele Aludino
    \date       09 Dec 2020
 */

#include <stdio.h>

//#define ULOG_DISABLE_BUG
//#define ULOG_DISABLE_ERROR
//#define ULOG_DISABLE_LOG
//#define ULOG_DISABLE_WARNING

#include "cgcs_ulog.h"

/*!
    \brief  Program execution begins and ends here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, nonzero on failure
 */
int main(int argc, const char *argv[]) {
    BUG(__FILE__, "test");
    LOG(__FILE__, "test");
    ERROR(__FILE__, "test");
    WARNING(__FILE__, "test");

    massert(argc == 5, "argc not 5");

    return 0;
}
