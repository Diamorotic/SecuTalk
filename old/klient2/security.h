#ifndef SECURITY_H
#define SECURITY_H

#include "deklaracje.h"

void createKeys();
std::string encrypt(QString KeyFileName,QString message);
std::string decrypt(std::string message);
QString get_random_string();
#endif // SECURITY_H
