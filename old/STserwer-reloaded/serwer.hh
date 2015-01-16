#include "monitor.hpp"
#include "authorizationThread.hpp"

void dummy();
int runClient();
DWORD WINAPI authorization(LPVOID lpParam );
void createKeys();
void encrypt();
void decrypt();
std::string decrypt(std::string cipher2);
std::string encrypt(std::string message);
