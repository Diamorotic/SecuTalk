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


	char* get_data_instance() const;				//tworzy kopi� przechowywanych danych i zwraca wska�nik na ni�
	char* get_data_piece(int beginning, int end) const;				//tworzy kopi� fragmentu danych i zwraca wska�nik na ni�. UWAGA!!! Zwraca NULLa, je�li end>data_size
	RawData get_packed_data_piece(int beginning, int end) const;				//tworzy kopi� fragmentu danych w postaci nowego obiektu RawData
	int get_data_size() const;					//zwraca rozmiar przechowywanych danych

	int add_data(char* buf_ptr, int size);				//dopisuje do przechowywanych danych jakie� nowe (na ko�cu); zwraca nowy rozmiar przechowywanych danych
	int add_data(RawData data);				//dopisuje do przechowywanych danych jakie� nowe (na ko�cu); zwraca nowy rozmiar przechowywanych danych
	int insert_data(char* buf_ptr, int size, int where);	//dopisuje nowe dane w dowolnym miejscu istniej�cych (rozdziela stare dane na dwie cz�ci)
	int insert_data(RawData data, int where);	//dopisuje nowe dane w dowolnym miejscu istniej�cych (rozdziela stare dane na dwie cz�ci)
	void del_data();						//czy�ci "do zera" przechowywane dane
	void del_data_piece(int beginning, int end);				//usuwa wybrany fragment przechowywanych danych
	RawData& operator=(RawData data);
	RawData operator+(const RawData& right);
	RawData& operator+=(const RawData& right)
};
