#include <internal/attribute.h>
#include <stdio.h>

__weak void clearerr(__unused FILE* stream) { }
