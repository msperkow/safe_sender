#ifndef SAFE_SENDER_SENDER_HPP
#define SAFE_SENDER_SENDER_HPP

#include "../raw_bytes.hpp"
#include "sendable.hpp"
#include "communicator.hpp"
#include "../file.hpp"
#include "../text_message.hpp"
#include "../encryption/encryption_key.hpp"
class Application;

class Sender : public Communicator
{
private:
	std::string receiverIP;
	Application* application;
	float progress;
protected:
public:
	//constructor used by client when sending data
	Sender(asio::io_service &ioService, std::string ip, unsigned int port, Application* application);
	~Sender();

	void setReceiverIPAndPort(std::string ip, unsigned int port);

	const std::string &getReceiverIP() const;
	const unsigned int &getReceiverPort() const;
	float getProgress();

	bool connect();
	void disconnect();
	void handleSend(DataContainer* msg, Encryption& encryption, MessageType messageType);
};


#endif //SAFE_SENDER_SENDER_HPP
