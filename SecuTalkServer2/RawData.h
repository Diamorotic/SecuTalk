#include <cstdlib>
#include <cstring>

using namespace std;

class RawData
{
	private:

	char* data_ptr;
	int data_size;


	public:

	RawData();
	RawData(const RawData& data);
	RawData(char* buf_ptr, int size);
	~RawData();


	char* get_data_instance() const;				//tworzy kopiê przechowywanych danych i zwraca wskaŸnik na ni¹
	char* get_data_piece(int beginning, int end) const;				//tworzy kopiê fragmentu danych i zwraca wskaŸnik na ni¹. UWAGA!!! Zwraca NULLa, jeœli end>data_size
	RawData get_packed_data_piece(int beginning, int end) const;				//tworzy kopiê fragmentu danych w postaci nowego obiektu RawData
	int get_data_size() const;					//zwraca rozmiar przechowywanych danych

	int add_data(char* buf_ptr, int size);				//dopisuje do przechowywanych danych jakieœ nowe (na koñcu); zwraca nowy rozmiar przechowywanych danych
	int add_data(RawData data);				//dopisuje do przechowywanych danych jakieœ nowe (na koñcu); zwraca nowy rozmiar przechowywanych danych
	int insert_data(char* buf_ptr, int size, int where);	//dopisuje nowe dane w dowolnym miejscu istniej¹cych (rozdziela stare dane na dwie czêœci)
	int insert_data(RawData data, int where);	//dopisuje nowe dane w dowolnym miejscu istniej¹cych (rozdziela stare dane na dwie czêœci)
	void del_data();						//czyœci "do zera" przechowywane dane
	void del_data_piece(int beginning, int end);				//usuwa wybrany fragment przechowywanych danych
	RawData& operator=(RawData data);
	RawData operator+(const RawData& right);
	RawData& operator+=(const RawData& right)
};
