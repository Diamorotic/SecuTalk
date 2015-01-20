#ifndef KOMUNIKATMIEDZYWATKOWY_H
#define KOMUNIKATMIEDZYWATKOWY_H


class KomunikatMiedzywatkowy
{
private:
    unsigned char idRamki;

public:
    KomunikatMiedzywatkowy();
    KomunikatMiedzywatkowy(unsigned const char idRamki);
    ~KomunikatMiedzywatkowy();
    char getIdRamki();
};

#endif // KOMUNIKATMIEDZYWATKOWY_H
//TODO konstruktor KomunikatMiedzywatkowy(char id, RawData *ramkaDoOpakowania) i
        //KomunikatMiedzywatkowy(char id, char* ramkaJednobajtowa)
