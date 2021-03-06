#include "model/encryption/encryption_aes.hpp"
#include <ostream>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <constants.hpp>

void EncryptionAES::encrypt(RawBytes &data)
{
	switch (cipherMode)
	{
		case ECB:
			encryptECB(data);
			break;
		case CBC:
			encryptCBC(data);
			break;
		case CFB:
			encryptCFB(data);
			break;
		case OFB:
			encryptOFB(data);
			break;
	}
}

EncryptionAES::EncryptionAES(CipherMode cipherMode)
{
	this->cipherMode = cipherMode;
}

void EncryptionAES::encryptECB(RawBytes &data)
{
	std::string result;
	CryptoPP::AES::Encryption e(encryptionKey.getData(), encryptionKey.getDataSize());
	CryptoPP::ECB_Mode_ExternalCipher::Encryption encryption(e, reinterpret_cast<const byte *>(iv.c_str()));
	CryptoPP::StreamTransformationFilter filter(encryption, new CryptoPP::StringSink(result));
	filter.Put(reinterpret_cast<const byte *>(data.toString().c_str()), data.toString().size());
	filter.MessageEnd();
	data.Assign(reinterpret_cast<const byte *>(result.c_str()), result.size());
}

void EncryptionAES::encryptCBC(RawBytes &data)
{
	std::string result;
	CryptoPP::AES::Encryption e(encryptionKey.getData(), encryptionKey.getDataSize());
	CryptoPP::CBC_Mode_ExternalCipher::Encryption encryption(e, reinterpret_cast<const byte *>(iv.c_str()));
	CryptoPP::StreamTransformationFilter filter(encryption, new CryptoPP::StringSink(result));
	filter.Put(reinterpret_cast<const byte *>(data.toString().c_str()), data.toString().size());
	filter.MessageEnd();
	data.Assign(reinterpret_cast<const byte *>(result.c_str()), result.size());
}

void EncryptionAES::encryptCFB(RawBytes &data)
{
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption(encryptionKey.getData(), encryptionKey.getDataSize(),
			 CryptoPP::SecByteBlock(reinterpret_cast<const byte *>(iv.c_str()), iv.size()));
	encryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}

void EncryptionAES::encryptOFB(RawBytes &data)
{
	CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption encryption(encryptionKey.getData(), encryptionKey.getDataSize(),
			 CryptoPP::SecByteBlock(reinterpret_cast<const byte *>(iv.c_str()), iv.size()));
	encryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}

void EncryptionAES::decrypt(RawBytes &data)
{
	switch (cipherMode)
	{
		case ECB:
			decryptECB(data);
			break;
		case CBC:
			decryptCBC(data);
			break;
		case CFB:
			decryptCFB(data);
			break;
		case OFB:
			decryptOFB(data);
			break;
	}
}

void EncryptionAES::decryptECB(RawBytes &data)
{
	std::string result;
	CryptoPP::AES::Decryption e(encryptionKey.getData(), encryptionKey.getDataSize());
	CryptoPP::ECB_Mode_ExternalCipher::Decryption decryption(e, reinterpret_cast<const byte *>(iv.c_str()));
	CryptoPP::StreamTransformationFilter filter(decryption, new CryptoPP::StringSink(result));
	filter.Put(reinterpret_cast<const byte *>(data.toString().c_str()), data.toString().size());
	filter.MessageEnd();
	data.Assign(reinterpret_cast<const byte *>(result.c_str()), result.size());
}

void EncryptionAES::decryptCBC(RawBytes &data)
{
	std::string result;
	CryptoPP::AES::Decryption e(encryptionKey.getData(), encryptionKey.getDataSize());
	CryptoPP::CBC_Mode_ExternalCipher::Decryption decryption(e, reinterpret_cast<const byte *>(iv.c_str()));
	CryptoPP::StreamTransformationFilter filter(decryption, new CryptoPP::StringSink(result));
	filter.Put(reinterpret_cast<const byte *>(data.toString().c_str()), data.toString().size());
	filter.MessageEnd();
	data.Assign(reinterpret_cast<const byte *>(result.c_str()), result.size());
}

void EncryptionAES::decryptCFB(RawBytes &data)
{
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption(encryptionKey.getData(), encryptionKey.getDataSize(),
				 CryptoPP::SecByteBlock(reinterpret_cast<const byte *>(iv.c_str()), iv.size()));
	decryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}

void EncryptionAES::decryptOFB(RawBytes &data)
{
	CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption decryption(encryptionKey.getData(), encryptionKey.getDataSize(),
				 CryptoPP::SecByteBlock(reinterpret_cast<const byte *>(iv.c_str()), iv.size()));
	decryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}
