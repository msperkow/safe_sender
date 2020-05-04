#include "../../include/model/raw_bytes.hpp"
#include <iomanip>

RawBytes::RawBytes()
{

}

RawBytes::RawBytes(unsigned long size)
: CryptoPP::SecByteBlock(size)
{

}

RawBytes::RawBytes(const std::string &str)
: CryptoPP::SecByteBlock(reinterpret_cast<const unsigned char*>(&str[0]), str.size())
{

}

std::string RawBytes::toString()
{
	std::string ret(reinterpret_cast<char*>(BytePtr()), size());
	return ret;
}

void RawBytes::print(std::ostream &o)
{
	for (byte byte : *this)
	{
		o << std::setw(2) << std::setfill('0') << std::hex << byte << " ";
	}
}

const byte &RawBytes::getByte(unsigned long i) const
{
	return BytePtr()[i];
}