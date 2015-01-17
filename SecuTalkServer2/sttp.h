#include <windows.h>
#include <queue>
#include <stdlib>

#include "deklaracje.hh"
#include "PrioritableRawData.h"


#define STTP_DATA_FIELD_LEN 26
#define DIR_SENDING true
#define DIR_RECEIVING false


using namespace std;

class STTP
{
	private:
	
	const bool direction;	//true <-> do sieci, false <-> z sieci
	const int dataFieldLen;
	queue<RawData>* netQueue;
	queue<PrioritableRawData>* controllerQueue;
	unsigned char frameCtrlNr;
	RawData buffer;
	string session_key;
	
	void to_net(RawData data);	//wsadza dane do kolejki ni¿szej warstwy
	void to_controller(RawData data);	//wsadza dane do kolejki wy¿szej warstwy
	RawData from_net();			//pobiera dane z kolejki od ni¿szej warstwy
	PrioritableRawData from_controller();	//pobiera dane z kolejki od wy¿szej warstwy
	RawData prepare_sttp_frame(RawData dataField);	//zwróci puste RawData!!!, jeœli dataField ma wiêcej bajtów ni¿ 26
	int single_send();	//zwraca iloœæ bajtów wys³anych wewn¹trz pola danych ramki STTP
	void single_receive();
	
	
	public:
	
	STTP(queue<RawData>* nq, queue<RawData>* cq);
	~STTP();

	int single_transmit(bool force_send);	//single_send albo single_receive, w zale¿noœci od direction; zwraca przes³an¹ iloœæ bajtów protoko³u komunikacyjnego

	int get_data_field_len();
};