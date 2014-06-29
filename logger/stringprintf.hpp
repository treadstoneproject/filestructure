#ifndef STRUTIL_STRINGPRINTF_H_
#define STRUTIL_STRINGPRINTF_H_
// Author: Leo Shen (leoshen@tencent.com),  GNU General Public License
#include <string>

std::string StringPrintf(const char* format, ...);
void SStringPrintf(std::string* dst, const char* format, ...);
void StringAppendF(std::string* dst, const char* format, ...);

#endif // STRUTIL_STRINGPRINTF_H_