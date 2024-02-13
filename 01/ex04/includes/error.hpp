#ifndef ERROR_H
#define ERROR_H

#include <string>

#define ERR_INVALID_ARGS "invalid arguments"
#define ERR_REPLACE      "fail to create replaced newfile"

void PutError(const std::string &message);

#endif /* ERROR_H */
