#include <stdarg.h>
#include <stdio.h>
int myprintf(const char *format, ...)
{
    va_list ap;
    int n;
     
    va_start(ap, format);
    n = vprintf(format, ap);
    va_end(ap);
    return n;    
}


void myerror(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    return;
}

int main(int argc, char const *argv[])
{
    myprintf("score = %d\n", 99);
    myerror("get msg error");
    myerror("ret = %d\n", -100);
    return 0;
}
