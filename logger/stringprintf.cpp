#include "filestructure/logger/logging.hpp"
#include <stdarg.h>
#include <stdio.h> 

#define va_copy(dest, src) (dest = src)

using std::string;

static void StringAppendV(string *dst, const char *format, va_list ap)
{
    // First try with a small fixed size buffer
    char space[1024];

    // It's possible for methods that use a va_list to invalidate
    // the data in it upon use. The fix is to make a copy
    // of the structure before using it and use that copy instead.
    va_list backup_ap;
    va_copy(backup_ap, ap);
#ifdef _WIN32
    int result = vsnprintf_s(space, sizeof(space), format, backup_ap); // Support win32
#elif __linux__
    int result = vsnprintf(space, sizeof(space), format, backup_ap);
#endif
    va_end(backup_ap);

    if ((result >= 0) && (result < sizeof(space))) {
        // It fit
        dst->append(space, result);
        return;
    }

    // Repeatedly increase buffer size until it fits
    int length = sizeof(space);

    while (true) {
        if (result < 0) {
            // Older behavior: just try doubling the buffer size
            length *= 2;
        } else {
            // We need exactly "result+1" characters
            length = result + 1;
        }

        char *buf = new char[length];

        // Restore the va_list before we use it again
        va_copy(backup_ap, ap);
#ifdef _WIN32
        result = vsnprintf_s(buf, sizeof(space), length, format, backup_ap); //support win32
#elif __linux__
        result = vsnprintf(space, sizeof(space), format, backup_ap);
#endif
        va_end(backup_ap);

        if ((result >= 0) && (result < length)) {
            // It fit
            dst->append(buf, result);
            delete[] buf;
            return;
        }

        delete[] buf;
    }
}

string StringPrintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    string result;
    StringAppendV(&result, format, ap);
    va_end(ap);
    return result;
}

void SStringPrintf(string *dst, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    dst->clear();
    StringAppendV(dst, format, ap);
    va_end(ap);
}

void StringAppendF(string *dst, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    StringAppendV(dst, format, ap);
    va_end(ap);
}
