#include "KontrolerWejsciowy.h"

KontrolerWejsciowy::KontrolerWejsciowy(std::queue<RawData> *mojaKolejka, std::queue<KomunikatMiedzywatkowy> *kolejkaModelu)
{
    this->mojaKolejka = mojaKolejka;
    this->kolejkaModelu = kolejkaModelu;
}

KontrolerWejsciowy::~KontrolerWejsciowy()
{

}

void *KontrolerWejsciowy::initializeController()//ta przekazywana przy tworzeniu watku
{
    //tutaj nastepuje sprawdzanie, czy cos jest w kolejce i obslugiwanie kolejnych elementow


    RawData daneDoWyslania = porcjaDanych();
    //tu juz mamy nasza porcje RawData do podzialu

    wyslijDoModelu(&daneDoWyslania);
    //tu powinny do kolejki modelu pojsc kolejne obiekty zawierajace poszczegolne ramki
}

RawData KontrolerWejsciowy::porcjaDanych()
{
    RawData wynik;
    while(!mojaKolejka->empty())
    {
        wynik += mojaKolejka->front();
        mojaKolejka->pop();
        if(wynik.get_data_size() >= suggestedRawDataMaxSize)
        {
            break;
        }
    }
    return wynik;
}

bool KontrolerWejsciowy::wyslijDoModelu(RawData *daneDoWyslania)
{
    resultPair paraWynikowa = pierwszaRamka(daneDoWyslania);
    while(paraWynikowa.first)
    {
        kolejkaModelu->push(paraWynikowa.second);
        paraWynikowa = pierwszaRamka(daneDoWyslania);
    }
    return true;//TODO zwracanie sukcesu
}

resultPair KontrolerWejsciowy::pierwszaRamka(RawData *daneDoParsowania)
{
    resultPair wynik;

    char *pierwszyBit = daneDoParsowania->get_data_piece_instance(0, 1);
    switch(*pierwszyBit)
    {
    case 1:
        wynik = std::make_pair(true, KomunikatMiedzywatkowy(1));
        daneDoParsowania->del_data_piece(0, 1);
        break;
    }
    return wynik;
}
