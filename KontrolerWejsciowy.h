#ifndef KONTROLERWEJSCIOWY_H
#define KONTROLERWEJSCIOWY_H

#include "RawData.h"
#include "deklaracje.h"
#include "KomunikatMiedzywatkowy.h"

class KontrolerWejsciowy
{
private:
    std::queue<RawData> *mojaKolejka;
    std::queue<KomunikatMiedzywatkowy> *kolejkaModelu;

    RawData porcjaDanych();
    bool wyslijDoModelu(RawData *daneDoWyslania);
    resultPair pierwszaRamka(RawData *daneDoParsowania); //zwraca parê <czySukces, komunikatDoPrzeslania>

public:
    KontrolerWejsciowy(std::queue<RawData> *mojaKolejka, std::queue<KomunikatMiedzywatkowy> *kolejkaModelu);
    ~KontrolerWejsciowy();
    void* initializeController();
};

#endif // KONTROLERWEJSCIOWY_H
