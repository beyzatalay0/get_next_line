*This project has been created as part of the 42 curriculum by beyatala.*

# get_next_line

## Description

Get Next Line is a project from the 42 curriculum.

The goal of this project is to implement a function that reads from a file
descriptor and returns one line at a time.

The function keeps reading from the file descriptor until it finds a newline
character or reaches the end of the file.

This project helped me understand file descriptors, the `read()` function,
static variables, dynamic memory allocation and buffer management.

The function prototype is:

```c
char *get_next_line(int fd);
```

## Instructions

The project can be compiled with a custom `BUFFER_SIZE`.

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

Then run:

```bash
./gnl_test
```

Different buffer sizes can also be tested:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

If `BUFFER_SIZE` is not defined during compilation, the default value defined
in the header file is used.

Example usage:

```c
char *line;

line = get_next_line(fd);
while (line)
{
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
}
```

Each call to `get_next_line()` returns the next line from the file descriptor.
The returned line includes the newline character when one exists.

When there are no more lines to read, the function returns `NULL`.

## Algorithm

The main idea of the algorithm is to use a static variable called `stash`.

A static variable is used because some characters read by `read()` may belong
to the next line. The stash keeps these remaining characters between different
calls to `get_next_line()`.

The algorithm works in three main steps:

### 1. Read from the file descriptor

`ft_read_stash()` reads from the file descriptor using `BUFFER_SIZE`.

The data is added to the stash until:

- a newline character is found,
- the end of the file is reached,
- or a read error occurs.

If the buffer contains more data than the current line needs, the extra data
remains in the stash.

For example:

```text
BUFFER_SIZE = 8

read() -> "Hello\nWo"

returned line -> "Hello\n"
remaining stash -> "Wo"
```

### 2. Extract the line

`ft_get_line()` creates the line that will be returned by `get_next_line()`.

It copies characters from the stash until it reaches a newline character or
the end of the string.

If a newline exists, it is included in the returned line.

### 3. Update the stash

`ft_update_stash()` removes the returned line from the stash.

Any characters after the newline are saved for the next call to
`get_next_line()`.

For example:

```text
stash before: "Hello\nWorld\n"

returned line: "Hello\n"

stash after: "World\n"
```

If there are no remaining characters, the stash is freed and becomes `NULL`.

### Why this algorithm?

This algorithm was selected because `read()` does not necessarily return
exactly one line.

Depending on `BUFFER_SIZE`, one read operation can return only part of a line
or multiple lines at once.

Using a static stash allows the function to preserve unused characters between
calls without reading the same data again. This makes it possible to return
exactly one line for each call to `get_next_line()`.

## Resources

The following resources were used while working on the project:

- 42 Get Next Line subject
- `read()` manual page (`man 2 read`)
- `malloc()` manual page (`man 3 malloc`)
- `free()` manual page (`man 3 free`)
- C documentation about static variables

### AI Usage

AI was used as a learning and debugging assistant during the project.

It was used for:

- Understanding file descriptors and how `read()` works
- Understanding the purpose of static variables
- Understanding how `BUFFER_SIZE` affects reading
- Discussing the stash logic
- Reviewing the algorithm step by step
- Preparing test cases for different `BUFFER_SIZE` values
- Debugging edge cases such as empty files and newline-only files

The implementation and project logic were reviewed and tested during the
development process.