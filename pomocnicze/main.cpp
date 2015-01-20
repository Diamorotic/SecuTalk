#include <iostream>
#include <pthread.h>
#include <PrioritableRawData.h>

using namespace std;

class exampleStruct
{
public:
    int numberToPrint;
    string stringToprint;

    exampleStruct(int initialNumber, string initialString)
    {
        this->numberToPrint = initialNumber;
        this->stringToprint = initialString;
    }

    exampleStruct()
    {

    }
};

void* printNumber(void* numberToPrint)
{
    cout <<"Watek: " <<(int)numberToPrint <<endl;
}

void* printExampleStruct(void* inputStruct)
{
    exampleStruct* structToPrint = new(exampleStruct);
    structToPrint = (exampleStruct*)inputStruct;
    cout <<"Watek " <<structToPrint->stringToprint <<": " <<structToPrint->numberToPrint <<endl;
}

int main ()
{
    printNumber(0);
    exampleStruct* exampleStruct0 = new(exampleStruct)(0, "zerowy");
    cout <<exampleStruct0->numberToPrint <<exampleStruct0->stringToprint <<endl;

    pthread_t *thread1, *thread2;
    int numer1 = 1, numer2 = 2;

    //exampleStruct exampleStruct2(2, "drugi");
    void* exampleStruct2Pointer = new(exampleStruct)(2, "drugi");

    pthread_create(thread1, NULL, printNumber, (void *)numer1);
    pthread_create(thread2, NULL, printExampleStruct, exampleStruct2Pointer);

    //Przed zakoñczeniem aplikacji warto zamykaæ w¹tki bo siê potrafi wypieprzaæ. Bez zamykania i system pause potrafi³o nie poczekaæ na wyniki dzia³ania nowego w¹tku.
/*
    unsigned char ileBajtMa=0;
    int minChar = 0, maxChar = 0;
    cout <<"Sprawdzenie chara:\n" <<(int)ileBajtMa <<endl;
    for(int i=0; i<=1000; i++)
    {
        if((int)ileBajtMa > maxChar){
            maxChar = (int)ileBajtMa;
        }
        if((int)ileBajtMa < minChar){
            minChar = (int)ileBajtMa;
        }
        cout <<ileBajtMa <<endl;
        ileBajtMa++;
    }
    cout <<"maxChar: " <<maxChar <<endl <<"minChar: " <<minChar <<endl;

    int jedenI = 1;
    char jedenC = 1;

    if(jedenI == jedenC)
        cout <<"Tak. 1=1\n" <<jedenC <<jedenI;
    else
        cout <<"Nie. 1C != 1i\n";
//*/
    system("PAUSE");
    return 0;
}
