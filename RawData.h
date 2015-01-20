#ifndef RAWDATA_H
#define RAWDATA_H


#include <cstdlib>
#include <cstring>


class RawData
{
	private:

	char* dataPtr;
	int dataSize;


	public:

	RawData();							//konstruktor domyœlny
	RawData(const RawData& data);		//konstruktor kopiuj¹cy
	RawData(char* buf_ptr, int size);	//konstruktor ze wskaŸnika na bufor
	~RawData();							//destruktor


	char* get_data_instance() const;				//tworzy kopiê przechowywanych danych i zwraca wskaŸnik na ni¹
	//UWAGA! Do programisty nale¿y zadbanie o póŸniejsze zwolnienie obszaru pamiêci zaalokowanego przez get_data_instance()
	char* get_data_piece_instance(int beginning, int end) const;				//tworzy kopiê fragmentu danych i zwraca wskaŸnik na ni¹. UWAGA!!! Zwraca NULLa, jeœli end>data_size
	RawData get_packed_data_piece(int beginning, int end) const;				//tworzy kopiê fragmentu danych w postaci nowego obiektu RawData
	int get_data_size() const;					//zwraca rozmiar przechowywanych danych

	int add_data(char* buf_ptr, int size);				//dopisuje do przechowywanych danych jakieœ nowe (na koñcu); zwraca nowy rozmiar przechowywanych danych
	int add_data(RawData data);				//dopisuje do przechowywanych danych jakieœ nowe (na koñcu); zwraca nowy rozmiar przechowywanych danych
	int insert_data(char* buf_ptr, int size, int where);	//dopisuje nowe dane w dowolnym miejscu istniej¹cych (rozdziela stare dane na dwie czêœci)
	int insert_data(RawData data, int where);	//dopisuje nowe dane w dowolnym miejscu istniej¹cych (rozdziela stare dane na dwie czêœci)
	int del_data();						//czyœci "do zera" przechowywane dane
	int del_data_piece(int beginning, int end);				//usuwa wybrany fragment przechowywanych danych
	RawData& operator=(RawData const &data);	//operator przypisania
	RawData operator+(const RawData& right);	//operator dodawania (dopisuje dane z prawego operandu na koñcu danych lewego)
	RawData& operator+=(const RawData& right);
	bool operator==(const RawData& right) const;
	bool operator!=(const RawData& right) const;
};


#endif