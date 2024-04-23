#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>


#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// Helper function to print integers
void print_int(int value) {
    if (value < 0) {
        putch('-');
        value = -value;
    }
    if (value / 10) {
        print_int(value / 10);
    }
    putch(value % 10 + '0');
}

// Helper function to print strings
void print_string(const char* str) {
    while (*str) {
        putch(*str++);
    }
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const char* p = fmt;
    while (*p) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'd': {
                    int i = va_arg(args, int);
                    print_int(i);
                    break;
                }
                case 's': {
                    const char* s = va_arg(args, const char*);
                    print_string(s);
                    break;
                }
                case 'c': {
                    char c = (char) va_arg(args, int); // Char is promoted to int
                    putch(c);
                    break;
                }
                default: {
                    putch('%');
                    if (*p) {
                        putch(*p); // Print the unknown specifier
                    } else {
                        p--; // Stay in bounds in case '%' is the last character
                    }
                    break;
                }
            }
        } else {
            putch(*p);
        }
        p++;
    }

    va_end(args);
    return 0; // Simplified version, does not return number of characters printed
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}


#endif
