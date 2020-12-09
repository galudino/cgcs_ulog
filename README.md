# cgcs_ulog
 Utilities for pretty-printing console messages, written in C.

Note:
Repository under construction.<br>
`CMakeLists.txt` is planned for this submodule.

For now, you may simply bring `cgcs_ulog.h` and `cgcs_ulog.c` 
and use it among your other sources within your project.
In the future, you will be able to use this repository as a submodule.

## The `ulog` function

<code>#include "cgcs_ulog.h"</code> in the file where you intend to use `ulog`.

The prototype for `cgcs_ulog` is this:

```c
int cgcs_ulog(FILE *dest,        // destination file stream, i.e. stdout
              const char *level, // Primary label, i.e. "ERROR", or "BUG"
              const char *file,  // Primarily for the __FILE__ macro
              const char *func,  // Primarily for the __func__ macro
              long double line,  // Primarily for the __LINE__ macro
              const char *fmt, ...);    // Formatted string

```

The format for a console printout of a `cgcs_ulog` call is as follows:

<code>
MM DD YYYY HH:MM:ss <b>[level]</b> [file:line] func <b>fmt</b>
</code><br><br>

There are four macros in `cgcs_ulog.h`:<br>
`BUG`, `LOG`, `WARNING`, `ERROR`
that are 'prepackaged' calls to `cgcs_ulog()`.<br>

All that is required to use these macros is use of the `__FILE__` macro,<br>
and a message string.<br>

This may be formatted (i.e. as per `printf`), or just a single string. 
It is generally better to utilize these macros, for ease of use -- you may even make your own if you want.


- `BUG(FILEMACRO, ...)`<br>
is used for logging bugs. The [level] section is yellow.

- `LOG(FILEMACRO, ...)`<br>
  is a general-purpose log. The [level] section is cyan.

- `ERROR(FILEMACRO, ...)`<br>
  is used for errors. The [level] selection is red, and it blinks.

- `WARNING(FILEMACRO, ...)`<br>
  is used for warnings. The [level] section is pink, and it blinks.

## Pretty colors

Also include are macros for adding color to your console messages.

```c
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
```

For example, if you want a string to have green text,<br>
you can do this:

```c
const char *mystr = KGRN"Look at me, I'm green!"KNRM;
```

You can also use a formatted string:

```c
printf("%s%s%s\n", KGRN, "Look at me, I'm green!", KNRM);
```

Color codes may be combined as well<br>
(say if you want a bold-italic colored message that blinks) --
but you must end the string/message with a `KNRM` macro.

Otherwise, all subsequent output will retain the previous formatting.


## `massert` (A version of `assert()` with a message)

`massert` works just like `assert` from `assert.h`,<br>
but wraps the `ERROR` macro within it.<br>
(The `ERROR` ulog message will appear below the `Assertion failed:` line.)

```c
int x = 4;
massert(x == 5, "x must be equal to 5");
```

Result:

```c
Assertion failed: (x == 5)
Nov  23 2009 03:54:00 [ERROR] [cgcs_ulog_test.c:39] main x must be equal to 5
```


## Sample usage

```c
#include <stdio.h>

#include "cgcs_ulog.h"

int main(int argc, const char *argv[]) {
    BUG(__FILE__, "test");
    LOG(__FILE__, "test");
    ERROR(__FILE__, "test");
    WARNING(__FILE__, "test");

    // You can use more than one color code at a time,
    // but make sure to end your string with a KNRM macro --
    // or else subsequent printouts in your stream will still
    // have your previous setting!
    printf("%s%s%s\n", KGRN_b, "Look at me, I'm green!!!", KNRM);

    int x = 4;
    massert(x == 5, "x must be equal to 5");
    // Program will abort() here.

    return 0;
}
```
