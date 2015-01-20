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

	RawData();							//konstruktor domy�lny
	RawData(const RawData& data);		//konstruktor kopiuj�cy
	RawData(char* buf_ptr, int size);	//konstruktor ze wska�nika na bufor
	~RawData();							//destruktor


	char* get_data_instance() const;				//tworzy kopi� przechowywanych danych i zwraca wska�nik na ni�
	//UWAGA! Do programisty nale�y zadbanie o p�niejsze zwolnienie obszaru pami�ci zaalokowanego przez get_data_instance()
	char* get_data_piece_instance(int beginning, int end) const;				//tworzy kopi� fragmentu danych i zwraca wska�nik na ni�. UWAGA!!! Zwraca NULLa, je�li end>data_size
	RawData get_packed_data_piece(int beginning, int end) const;				//tworzy kopi� fragmentu danych w postaci nowego obiektu RawData
	int get_data_size() const;					//zwraca rozmiar przechowywanych danych

	int add_data(char* buf_ptr, int size);				//dopisuje do przechowywanych danych jakie� nowe (na ko�cu); zwraca nowy rozmiar przechowywanych danych
	int add_data(RawData data);				//dopisuje do przechowywanych danych jakie� nowe (na ko�cu); zwraca nowy rozmiar przechowywanych danych
	int insert_data(char* buf_ptr, int size, int where);	//dopisuje nowe dane w dowolnym miejscu istniej�cych (rozdziela stare dane na dwie cz�ci)
	int insert_data(RawData data, int where);	//dopisuje nowe dane w dowolnym miejscu istniej�cych (rozdziela stare dane na dwie cz�ci)
	int del_data();						//czy�ci "do zera" przechowywane dane
	int del_data_piece(int beginning, int end);				//usuwa wybrany fragment przechowywanych danych
	RawData& operator=(RawData const &data);	//operator przypisania
	RawData operator+(const RawData& right);	//operator dodawania (dopisuje dane z prawego operandu na ko�cu danych lewego)
	RawData& operator+=(const RawData& right);
	bool operator==(const RawData& right) const;
	bool operator!=(const RawData& right) const;
};


#endif