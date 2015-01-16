#include "serwer.hh"

#include <cryptopp/cryptlib.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
//using namespace CryptoPP;

//using namespace std;

int sizeKey,sizeMsg;
//CryptoPP::RSA::PrivateKey *privKey;
//CryptoPP::RSA::PublicKey *pubKey;
//std::string cipher;
CryptoPP::AutoSeededRandomPool *asrPointer;
void dummy()
{
    cout <<"Im dummy a function "<<endl;
}

DWORD WINAPI authorization(LPVOID lpParam )
{
    SOCKET* sock = (SOCKET*)lpParam;
    AuthorizationThread authorizationThread(sock);
    authorizationThread.start();
    authorizationThread.join();
    return 0;
}

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

void encrypt()
{
    CryptoPP::RSA::PublicKey key;
    LoadPublicKey("keys//rsa-public.key", key);
    std::string msg="adsfasdfasdf",cipher,c2;
    //EncodePublicKey("rsa-public.key", key);
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e( key );
    CryptoPP::StringSource( msg, true, new CryptoPP::PK_EncryptorFilter( rng, e, new CryptoPP::StringSink( cipher )));
    cout <<"cipher: "<<endl<<cipher<<endl<<"cipher size: "<<cipher.size()<<endl;

    std::ofstream file ( "keys//msg", std::ios_base::binary );// std::ios::out |
    file.write( cipher.c_str(), cipher.size() );///size tez
    file.close();
}

std::string encrypt(std::string message)
{
    CryptoPP::RSA::PublicKey key;
    //LoadPublicKey("keys//rsa-public.key", key);
    LoadPrivateKey("C://Users//Toshiba//Downloads//secuTalk//klient2//keys//rsa-public.key", key);
    std::string msg=message,cipher,c2;
    //EncodePublicKey("rsa-public.key", key);
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e( key );
    CryptoPP::StringSource( msg, true, new CryptoPP::PK_EncryptorFilter( rng, e, new CryptoPP::StringSink( cipher )));
    cout <<"cipher: "<<endl<<cipher<<endl<<"cipher size: "<<cipher.size()<<endl;

    std::ofstream file ( "keys//msg", std::ios_base::binary );// std::ios::out |
    file.write( cipher.c_str(), cipher.size() );///size tez
    file.close();
    return cipher;
}

void decrypt()
{

    std::ifstream file2 ( "keys//msg", std::ios_base::binary );
    std::vector<char> image( (std::istreambuf_iterator<char>( file2 ) ),(std::istreambuf_iterator<char>()) );
    file2.close();
    std::string c2;
    std::string cipher2(image.begin(), image.end());;

    cout <<"cipher2: "<<endl<<cipher2<<endl<<"cipher2 size: "<<cipher2.size()<<endl;

    CryptoPP::RSA::PrivateKey key2;
    LoadPrivateKey("keys//rsa-private.key", key2);
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(key2);
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::StringSource( cipher2, true, new CryptoPP::PK_DecryptorFilter( rng, d, new CryptoPP::StringSink( c2 )));
    cout <<"c2: "<<endl<<c2<<endl;
}

std::string decrypt(std::string cipher2)
{
    std::string c2;

    cout <<"cipher2: "<<endl<<cipher2<<endl<<"cipher2 size: "<<cipher2.size()<<endl;
    CryptoPP::RSA::PrivateKey key2;
    LoadPrivateKey("keys//rsa-private.key", key2);
    //LoadPrivateKey("C://Users//Toshiba//Downloads//secuTalk//klient2//keys//rsa-private.key", key2);

    CryptoPP::RSAES_OAEP_SHA_Decryptor d(key2);
    //cout <<"cipher2334: "<<endl;
    CryptoPP::AutoSeededRandomPool rng;
    ///pamietac o znaku /0 z protokolu
    CryptoPP::StringSource( cipher2, true, new CryptoPP::PK_DecryptorFilter( rng, d, new CryptoPP::StringSink( c2 )));
    cout <<"c2: "<<endl<<c2<<endl;
    return c2;
}
