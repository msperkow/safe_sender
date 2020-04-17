#include "../../include/model/encryption_key.hpp"

EncryptionKey::EncryptionKey(const std::string& str)
: Encryptable(str)
{

}

EncryptionKey::EncryptionKey(RawBytes bytes)
: Encryptable(bytes)
{

}

EncryptionKey::EncryptionKey()
{

}
