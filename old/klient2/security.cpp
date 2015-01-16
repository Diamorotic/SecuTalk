#include "security.h"

#include <iostream>
#include <fstream>
#include <cryptlib.h>
#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <files.h>
#include <modes.h>
#include <aes.h>
#include <filters.h>
#include <QMessageBox>

using namespace std;

int sizeKey,sizeMsg;
//CryptoPP::RSA::PrivateKey *privKey;
//CryptoPP::RSA::PublicKey *pubKey;
//std::string cipher;
CryptoPP::AutoSeededRandomPool *asrPointer;

void Save(const string& filename, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}

void SavePublicKey(const string& filename, const CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}

void SavePrivateKey(const string& filename, const CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}

void Load(const string& filename, CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}

void LoadPublicKey(const string& filename, CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}

void LoadPrivateKey(const string& filename, CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}

void Encode(const string& filename, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}

void EncodePublicKey(const string& filename, const CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    key.DEREncodePublicKey(queue);

    Encode(filename, queue);
}

void createKeys()
{

    CryptoPP::AutoSeededRandomPool rng;
    asrPointer=&rng;
    CryptoPP::RSA::PrivateKey rsaPrivate;
    rsaPrivate.GenerateRandomWithKeySize(rng, 3072);///???
    CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

    SavePrivateKey("keys//rsa-private.key", rsaPrivate);
    SavePublicKey("keys//rsa-public.key", rsaPublic);
}

std::string encrypt(QString KeyFileName,QString message)
{
    ifstream f(KeyFileName.toStdString().c_str());
    if (KeyFileName.toStdString().substr(KeyFileName.toStdString().find_last_of(".") + 1) != "key" || !f.good()) {
        f.close();
        QMessageBox messageBox;
        messageBox.critical(0,"Blad","to nie jest klucz !");
        messageBox.setFixedSize(500,200);
        return "";
    }
    f.close();
    CryptoPP::RSA::PublicKey key;
    LoadPublicKey(KeyFileName.toStdString(), key);
    std::string msg=message.toStdString();
    std::string cipher,c2;
    //EncodePublicKey("rsa-public.key", key);
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e( key );
    CryptoPP::StringSource( msg, true, new CryptoPP::PK_EncryptorFilter( rng, e, new CryptoPP::StringSink( cipher )));
    cout <<"msg: "<< message.toStdString() <<endl;
    cout <<"cipher: "<<endl<<cipher<<endl<<"cipher size: "<<cipher.size()<<endl;

    std::ofstream file ( "keys//msg", std::ios_base::binary );
    file.write( cipher.c_str(), cipher.size() );///size tez
    file.close();
    return cipher;
}

std::string decrypt(std::string encoded_random_string)
{
//    std::ifstream file2 ( "keys//msg", std::ios_base::binary );
//    std::vector<char> image( (std::istreambuf_iterator<char>( file2 ) ),(std::istreambuf_iterator<char>()) );
//    file2.close();
    std::string c2;
    //std::string cipher2(image.begin(), image.end());
    std::string cipher2=encoded_random_string;

    cout <<"cipher2: "<<endl<<cipher2<<endl<<"cipher2 size: "<<cipher2.size()<<endl;

    CryptoPP::RSA::PrivateKey key2;
    LoadPrivateKey("keys//rsa-private.key", key2);
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(key2);
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::StringSource( cipher2, true, new CryptoPP::PK_DecryptorFilter( rng, d, new CryptoPP::StringSink( c2 )));
    cout <<"c2: "<<endl<<c2<<endl;
    return c2;
}

QString get_random_string()
{
    int len=20;
    char* s=new char[20];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
    std::string str(s);
    return QString::fromStdString(str);
}

