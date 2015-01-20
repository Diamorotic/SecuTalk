#include "RawData.h"


//konstruktor domyœlny
RawData::RawData()
{
	dataPtr = NULL;
	dataSize = 0;
};

//kontruktor z bufora znakowego
RawData::RawData(char* bufPtr, int size)
{
	dataPtr = new char[size];
	memcpy(dataPtr, bufPtr, size);

	dataSize = size;
};

//konstuktor kopiuj¹cy
RawData::RawData(const RawData& data)
{
	dataPtr = data.get_data_instance();
	dataSize = data.dataSize;
};

//destruktor
RawData::~RawData()
{
	delete dataPtr;
};


//tworzy kopiê przechowywanych danych i zwraca wskaŸnik na ni¹
// !!! UWAGA, do programisty nale¿y zadbanie o póŸniejsze
// !!! zwolnienie obszaru pamiêci, zaalokowanego w tej funkcji
char* RawData::get_data_instance() const
{
	char* newPtr = new char[dataSize];
	memcpy(newPtr, dataPtr, dataSize);

	return newPtr;
};

//tak jak powy¿ej, z t¹ ró¿nic¹, ¿e dotyczy wybranego fragmentu danych
char* RawData::get_data_piece_instance(int beginning, int end) const
{
	if (end > dataSize)
		return NULL;

	int pieceSize = end-beginning;
	char* newPtr = new char[pieceSize];
	memcpy(newPtr, dataPtr+beginning, pieceSize);

	return newPtr;
};

//tak jak powy¿ej, z t¹ ró¿nic¹, ¿e zwraca nowy obiekt RawData
RawData RawData::get_packed_data_piece(int beginning, int end) const
{
	if (end > dataSize)
		return RawData();

	int piece_size = end-beginning;

	RawData data_piece(dataPtr+beginning, piece_size);

	return data_piece;
};

//zwraca rozmiar przechowywanych danych
int RawData::get_data_size() const
{
	return dataSize;
};

//dopisuje do przechowywanych danych jakieœ nowe; zwraca nowy rozmiar przechowywanych danych
int RawData::add_data(char* bufPtr, int size)
{
	char* newPtr = new char[dataSize + size];
	memcpy(newPtr, dataPtr, dataSize);
	memcpy(newPtr+dataSize, bufPtr, size);

	delete dataPtr;

	dataPtr = newPtr;
	dataSize += size;

	return dataSize;
};

//dopisuje do przechowywanych danych jakieœ nowe; zwraca nowy rozmiar przechowywanych danych
int RawData::add_data(RawData data)
{
	char* newPtr = new char[dataSize + data.dataSize];
	memcpy(newPtr, dataPtr, dataSize);
	memcpy(newPtr+dataSize, data.dataPtr, data.dataSize);

	delete dataPtr;

	dataPtr = newPtr;
	dataSize += data.dataSize;

	return dataSize;
};

//wstawia nowe dane w wybrane miejsce starych danych
int RawData::insert_data(char* bufPtr, int size, int where)
{
	char* newPtr = new char[dataSize+size];
	memcpy(newPtr, dataPtr, where);
	memcpy(newPtr+where, bufPtr, size);
	memcpy(newPtr+where+size, dataPtr, dataSize-where);

	delete dataPtr;

	dataPtr = newPtr;
	dataSize += size;

	return dataSize;
};

//wstawia nowe dane w wybrane miejsce starych danych
int RawData::insert_data(RawData data, int where)
{
	char* newPtr = new char[dataSize+data.dataSize];
	memcpy(newPtr, dataPtr, where);
	memcpy(newPtr+where, data.dataPtr, data.dataSize);
	memcpy(newPtr+where+data.dataSize, dataPtr, dataSize-where);

	delete dataPtr;

	dataPtr = newPtr;
	dataSize += data.dataSize;

	return dataSize;
};

//czyœci "do zera" przechowywane dane, zwraca nowy rozmiar danych
int RawData::del_data()
{
	delete dataPtr;
	dataPtr = NULL;
	dataSize = 0;
	
	return dataSize;
};

//usuwa wybrany fragment danych, zwraca nowy rozmiar danych
int RawData::del_data_piece(int beginning, int end)
{
	int deleted_piece_size = end-beginning;
	char* newPtr = new char[dataSize - deleted_piece_size];
	memcpy(newPtr, dataPtr, beginning);
	memcpy(newPtr+beginning, dataPtr, dataSize-end);

	dataSize -= deleted_piece_size;
	
	return dataSize;
};

//operator przypisania
RawData& RawData::operator=(RawData const &right)
{
	if (this != &right)
	{
		delete dataPtr;
		dataPtr = right.get_data_instance();
		dataSize = right.dataSize;
	}

	return *this;
};

//operator dodawania (dopisuje dane z prawego operandu na koñcu danych lewego)
RawData RawData::operator+(const RawData& right)
{
    RawData result(*this);
	result.add_data(right);

    return result;
};

//operator przypisania z dodawaniem
RawData& RawData::operator+=(const RawData& right)
{
	add_data(right);

	return *this;
};

//wynik porównania jest pozytywny, jeœli przechowywane dane s¹ identyczne
bool RawData::operator==(const RawData& right) const
{
	if (dataSize != right.get_data_size())
		return false;

	char* rightDataPtr = right.get_data_instance();

	for (int i=0; i<dataSize; i++)
	{
		if (dataPtr[i] != rightDataPtr[i])
		{
			delete rightDataPtr;

			return false;
		}
	}

	delete rightDataPtr;

	return true;
};

//operator nierównioœciowy - analogiczny do operatora równoœciowy
bool RawData::operator!=(const RawData& right) const
{
	return !((*this) == right);
};
