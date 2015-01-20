//*
#include "RawData.h"
#include "deklaracje.hh" //TODO dodac SuggestedRawDataMaxSize
using namespace std;
class NaszThread
{
    winThread thread;
    KolejkaKomunikatowMiedzywatkowych *queue;
};

typedef pair<bool, KomunikatMiedzywatkowy> resultPair;

class KlasaKontroleraWejsciowego
{
    int userId;//git
    //KolejkaKomunikatowMiedzywatkowych *myQueue;
    KolejkaRawData *mojaKolejka;//git
    NaszThread *mojModel;//git

    void* initializeController(void *userId);//git
    RawData porcjaDanych();//git
    bool wyslijDoModelu(RawData *daneDoWys³ania);//git
    resultPair pierwszaRamka(RawData *daneDoParsowania); //zwraca parê <czySukces, komunikatDoPrzeslania>
//git
};

void *KlasaKontroleraWejsciowego::initializeController(void *userId)//ta przekazywana przy tworzeniu watku
{
    //tutaj nastepuje sprawdzanie, czy cos jest w kolejce i obslugiwanie kolejnych elementow


    RawData daneDoWyslania = porcjaDanych();
    //tu juz mamy nasza porcje RawData do podzialu

    wyslijDoModelu(daneDoWyslania);
    //tu powinny do kolejki modelu pojsc kolejne obiekty zawierajace poszczegolne ramki
}

RawData KlasaKontroleraWejsciowego::porcjaDanych()
{
    RawData wynik;
    while(mojaKolejka.notEmpty())
    {
        wynik += mojaKolejka.pop();
        if(wynik.get_data_size() >= SuggestedRawDataMaxSize)
        {
            break;
        }
    }
    return wynik;
}

bool KlasaKontroleraWejsciowego::wyslijDoModelu(RawData *daneDoWys³ania)
{
    resultPair paraWynikowa = pierwszaRamka(daneDoWys³ania);
    while(paraWynikowa.first)
    {
        mojModel->queue->push(paraWynikowa.second);
        paraWynikowa = pierwszaRamka(daneDoWys³ania);
    }
    return true;//TODO zwracanie sukcesu
}

resultPair KlasaKontroleraWejsciowego::pierwszaRamka(RawData *daneDoParsowania)
{
    resultPair wynik;

    char *pierwszyBit = daneDoParsowania->get_data_piece(0, 1);
    switch(pierwszyBit*)
    {
    case 1:
        wynik = make_pair(true, KomunikatMiedzywatkowy(1, pierwszyBit));//TODO konstruktor KomunikatMiedzywatkowy(char id, RawData *ramkaDoOpakowania) i
        //KomunikatMiedzywatkowy(char id, char* ramkaJednobajtowa)
        daneDoParsowania->del_data_piece(0, 1);
        break;
    }
    return wynik;
}

//*/
