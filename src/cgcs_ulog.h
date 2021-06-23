/*!
    \file       cgcs_ulog.h
    \brief      Header file for 'pretty-printing' console messages, user logs
    
    \author     Gemuele Aludino
    \date       08 Dec 2020
 */

#ifndef CGCS_ULOG_H
#define CGCS_ULOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#define KNRM        "\x1B[0;0m" //!< reset to standard color/weight
#define KNRM_b      "\x1B[0;1m" //!< standard color bold

#define KGRY        "\x1B[0;2m" //!< dark grey

#define KITL        "\x1B[0;3m" //!< italics
#define KULN        "\x1B[0;4m" //!< underline

#define KBNK        "\x1B[0;5m" //!< blink every second
#define KHIL        "\x1B[0;7m" //!< grey highlight

#define KRED        "\x1B[0;31m" //!< red
#define KGRN        "\x1B[0;32m" //!< green
#define KYEL        "\x1B[0;33m" //!< yellow
#define KBLU        "\x1B[0;34m" //!< blue
#define KMAG        "\x1B[0;35m" //!< magenta
#define KCYN        "\x1B[0;36m" //!< cyan
#define KWHT        "\x1B[0;37m" //!< white

#define KRED_b      "\x1B[1;31m" //!< red bold
#define KGRN_b      "\x1B[1;32m" //!< green bold
#define KYEL_b      "\x1B[1;33m" //!< yellow bold
#define KBLU_b      "\x1B[1;34m" //!< blue bold
#define KMAG_b      "\x1B[1;35m" //!< magenta bold
#define KCYN_b      "\x1B[1;36m" //!< cyan bold
#define KWHT_b      "\x1B[1;37m" //!< white bold

/*!
    \brief      Prints a 'pretty' console message to a FILE stream dest.

    \details    Format is as follows:

                MM DD YYYY HH:MM:ss [level] [file:line] func fmt

                The BUG, LOG, ERROR, and WARNING macros are 'prepackaged'
                cgcs_ulog calls -- try using those first before using
                cgcs_ulog directly (feel free to do so, if you have a special use case.)

    \param[in]  dest    Destination file stream for console message
    \param[in]  level   Boldfaced label in-between brackets, i.e. BUG, LOG, ERROR, WARNING
    \param[in]  func    Primarly made for the __func__ macro
    \param[in]  line    Primarly made for the __LINE__ macro
    \param[in]  fmt, ...    For formatted strings

    \return     @see fprintf
 */
int cgcs_ulog(FILE *dest,
         const char *level,
         const char *file,
         const char *func,
         long double line,
         const char *fmt, ...);

/*!
    Unless you would like to create a customized
    debugging message, please use the following preprocessor directives.
 
    BUG is suggested for documenting bugs at certain points in your program.
    LOG is a general-purpose messaging tool.
    ERROR is used for displaying error messages (i.e. something failed, etc)
    WARNING is used to notify the client of an impending issue.
 
    The first argument in BUG, LOG, ERROR, and WARNING is FILEMACRO,
    which refers to the following macro:
           __FILE__
    This is just a string, so if you are building a custom ulog message,
    with BUG, LOG, ERROR, or WARNING, and would like to put a different
    string in place of __FILE__, you may do so.
 */

//<! Designated default streams for BUG, LOG, ERROR, and WARNING
#define ULOG_STREAM_BUG stderr
#define ULOG_STREAM_LOG stdout
#define ULOG_STREAM_ERROR stderr
#define ULOG_STREAM_WARNING stderr

/*!
    \def        ULOG_DISABLE_ALL
    \brief      Shorthand macro to disable the following preprocessor macros:
                BUG, LOG, ERROR, WARNING
 
    Use the preprocessor directive
        #define ULOG_DISABLE_ALL
    before the inclusion of cgcs_ulog.h (or before any of the directives below)
    to disable the macros BUG, LOG, ERROR, and WARNING all at once.
 
    You may also use any combination of these macros to keep some
    of the ulog macro types active.

    ulog has the following format:
    (level is what appears in LEVEL, usually [BUG], [LOG], [ERROR], or [WARNING]
    if using the ulog macros. Using the ulog function allows you to customize
    your own error message)
    MMM dd yyyy HH:mm:ss LEVEL [filepath/filename:linenumber] function_name message
 */
#ifdef ULOG_DISABLE_ALL
# define ULOG_DISABLE_BUG
# define ULOG_DISABLE_LOG
# define ULOG_DISABLE_ERROR
# define ULOG_DISABLE_WARNING
#endif /* ULOG_DISABLE_ALL */

/*!
    \def        BUG
    \brief      Shorthand macro for ulog to note bugs in a program
    
    Use the preprocessor directive
        #define ULOG_DISABLE_BUG
    before the inclusion of cgcs_ulog.h (or before these directives)
    to disable the BUG macro.
 */
# ifndef ULOG_DISABLE_BUG
#  define BUG(FILEMACRO, ...)                                                    \
          cgcs_ulog(ULOG_STREAM_BUG, "[BUG]", FILEMACRO, __func__, (long int)__LINE__,    \
              __VA_ARGS__)
# else
#  define BUG(FILEMACRO, ...)
# endif /* ULOG_DISABLE_BUG */

/*!
    \def        LOG
    \brief      Shorthand macro for ulog to create messages for a program
    
    Use the preprocessor directive
        #define ULOG_DISABLE_BUG
    before the inclusion of cgcs_ulog.h (or before these directives)
    to disable the LOG macro.
 */
# ifndef ULOG_DISABLE_LOG
#  define LOG(FILEMACRO, ...)                                                    \
          cgcs_ulog(ULOG_STREAM_LOG, "[LOG]", FILEMACRO, __func__, (long int)__LINE__,    \
          __VA_ARGS__)
# else
#  define LOG(FILEMACRO, ...)
# endif /* ULOG_DISABLE_LOG */

/*!
    \def        ERROR
    \brief      Shorthand macro for ulog to display errors for a program
 
    Use the preprocessor directive
        #define ULOG_DISABLE_ERROR
    before the inclusion of cgcs_ulog.h (or before these directives)
    to disable the ERROR macro.
 */
# ifndef ULOG_DISABLE_ERROR
#  define ERROR(FILEMACRO, ...)                                                  \
          cgcs_ulog(ULOG_STREAM_ERROR, "[ERROR]", FILEMACRO, __func__,                    \
          (long int)__LINE__, __VA_ARGS__)
# else
#  define ERROR(FILEMACRO, MSG)
# endif /* ULOG_DISABLE_ERROR */

/*!
    \def        WARNING
    \brief      Shorthand macro for ulog to display warning for a program
 */
# ifndef ULOG_DISABLE_WARNING
#  define WARNING(FILEMACRO, ...)                                                \
          cgcs_ulog(ULOG_STREAM_WARNING, "[WARNING]", FILEMACRO, __func__,                \
          (long int)__LINE__, __VA_ARGS__)
#else
#  define WARNING(FILEMACRO, MSG)
# endif /* ULOG_DISABLE_WARNING */

#define UTILS_LOG_ATTRS_COUNT 7
enum ULOG_ATTRS { DATE, TIME, LEVEL, FILENAME, LINE, FUNCTION, MESSAGE };
extern bool ulog_attrs_disable[UTILS_LOG_ATTRS_COUNT];

#define ULOG_TOGGLE_ATTR(ULOG_ATTR)                                            \
    ulog_attrs_disable[ULOG_ATTR] =                                            \
        (ulog_attrs_disable[ULOG_ATTR]) ? (false) : (true)

//!< Turn off ulog attributes by invoking one or more of these in a function.
/*
    ULOG_TOGGLE_ATTR(DATE);
    ULOG_TOGGLE_ATTR(TIME);
    ULOG_TOGGLE_ATTR(LEVEL);
    ULOG_TOGGLE_ATTR(FILENAME);
    ULOG_TOGGLE_ATTR(LINE);
    ULOG_TOGGLE_ATTR(FUNCTION);
    ULOG_TOGGLE_ATTR(MESSAGE);
*/

/*!
    Custom assert function with message string -
    message prints to stderr, just like the assert macro in assert.h,
    and the message string is printed using the ulog function --
    wrapped with the ERROR macro defined in this header file.
    Then, just like the assert macro, abort() is invoked
    and the program ends.
 
    massert is most useful when a program is no longer fit
    to continue, given a particular condition --
    a description message of your choice can be provided.
 
    If no message is preferred, you may provide an empty string.
 */
#ifndef NDEBUG
#define massert(CONDITION, MESSAGE)\
    if (!(CONDITION)) {\
        fprintf(stderr, "Assertion failed: (%s)\n", #CONDITION);\
        ERROR(__FILE__, MESSAGE);\
        abort();\
    }
#else
#define massert(CONDITION, MESSAGE) 
#endif /* massert(CONDITION, MESSAGE) */

#define massert_ptr(PTR);\
massert(PTR, "['"#PTR"' was found to be NULL - '"#PTR"' must be nonnull to continue.]");

#define massert_ttbl(TTBL);\
massert(TTBL, "['"#TTBL"' was found to be NULL -- '"#TTBL"' is mandatory for data type information]");

#define massert_malloc(PTR);\
massert(PTR, "[Request for heap storage allocation failed (malloc returned NULL and was assigned to '"#PTR"')]");

#define massert_calloc(PTR);\
massert(PTR, "[Request for heap storage allocation failed (calloc returned NULL and was assigned to '"#PTR"')]");

#define massert_realloc(PTR);\
massert(PTR, "[Request for heap storage reallocation failed (realloc returned NULL and was assigned to '"#PTR"')]");

#define massert_pfunc(PFUNC);\
massert(PFUNC, "['"#PFUNC"' was found to be NULL - '"#PFUNC"' must be assigned to a function with a matching prototype.]");

#define massert_container(PTR);\
massert(PTR, "['"#PTR"' was found to be NULL - '"#PTR"' must be assigned to the return value of a container initializer function prior to use.]");

#endif /* CGCS_ULOG_H */
