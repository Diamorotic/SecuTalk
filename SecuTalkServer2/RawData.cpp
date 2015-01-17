#include "RawData.h"


RawData::RawData()
{
	data_ptr = NULL;
	data_size = 0;
};

RawData::RawData(char* buf_ptr, int size)
{
	data_ptr = new char[size];
	memcpy(data_ptr, buf_ptr, size);

	data_size = size;
};

RawData::RawData(const RawData& data)
{
	data_ptr = data.get_data_instance();
	data_size = data.data_size;
};

RawData::~RawData()
{
	delete data_ptr;
};



char* RawData::get_data_instance() const		//tworzy kopiê przechowywanych danych i zwraca wskaŸnik na ni¹
{
	char* new_ptr = new char[data_size];
	memcpy(new_ptr, data_ptr, data_size);

	return new_ptr;
};

char* RawData::get_data_piece(int beginning, int end) const
{
	if (end > data_size)
		return NULL;

	int piece_size = end-beginning;
	char* new_ptr = new char[piece_size];
	memcpy(new_ptr, data_ptr+beginning, piece_size);

	return new_ptr;
};

RawData RawData::get_packed_data_piece(int beginning, int end) const
{
	if (end > data_size)
		return RawData();

	int piece_size = end-beginning;

	RawData data_piece(data_ptr+beginning, piece_size);

	return data_piece;
};


int RawData::get_data_size() const			//zwraca rozmiar przechowywanych danych
{
	return data_size;
}

int RawData::add_data(char* buf_ptr, int size)	//dopisuje do przechowywanych danych jakieœ nowe; zwraca nowy rozmiar przechowywanych danych
{
	char* new_ptr = new char[data_size + size];
	memcpy(new_ptr, data_ptr, data_size);
	memcpy(new_ptr+data_size, buf_ptr, size);

	delete data_ptr;

	data_ptr = new_ptr;
	data_size += size;

	return data_size;
};

int RawData::add_data(RawData data)	//dopisuje do przechowywanych danych jakieœ nowe; zwraca nowy rozmiar przechowywanych danych
{
	char* new_ptr = new char[data_size + data.data_size];
	memcpy(new_ptr, data_ptr, data_size);
	memcpy(new_ptr+data_size, data.data_ptr, data.data_size);

	delete data_ptr;

	data_ptr = new_ptr;
	data_size += data.data_size;

	return data_size;
};

int RawData::insert_data(char* buf_ptr, int size, int where)
{
	char* new_ptr = new char[data_size+size];
	memcpy(new_ptr, data_ptr, where);
	memcpy(new_ptr+where, buf_ptr, size);
	memcpy(new_ptr+where+size, data_ptr, data_size-where);

	delete data_ptr;

	data_ptr = new_ptr;
	data_size += size;

	return data_size;
};

int RawData::insert_data(RawData data, int where)
{
	char* new_ptr = new char[data_size+data.data_size];
	memcpy(new_ptr, data_ptr, where);
	memcpy(new_ptr+where, data.data_ptr, data.data_size);
	memcpy(new_ptr+where+data.data_size, data_ptr, data_size-where);

	delete data_ptr;

	data_ptr = new_ptr;
	data_size += data.data_size;

	return data_size;
};

void RawData::del_data()				//czyœci "do zera" przechowywane dane
{
	delete data_ptr;
	data_size = 0;
};

void RawData::del_data_piece(int beginning, int end)
{
	int deleted_piece_size = end-beginning;
	char* new_ptr = new char[data_size - deleted_piece_size];
	memcpy(new_ptr, data_ptr, beginning);
	memcpy(new_ptr+beginning, data_ptr, data_size-end);

	data_size -= deleted_piece_size;
};

RawData& RawData::operator=(RawData const &right)
{
	if (this != &right)
	{
		delete data_ptr;
		data_ptr = right.get_data_instance();
		data_size = right.data_size;
	}
		
	return *this;
};

RawData RawData::operator+(const RawData& right)
{
    RawData result(*this);
	result.add_data(right);
	
    return result;
}

RawData& RawData::operator+=(const RawData& right)
{
	add_data(right);
	
	return *this;
}