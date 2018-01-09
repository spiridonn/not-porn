#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <tr1/memory>

#include "protocol.h"
#include "nthread.h"
#include "server.h"
#include "hub.h"
#include "registrarConector.h"
#include "registrationHandler.h"


namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;
typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;

class Communicator
{
public:
	Communicator(Hub* _hub);
	~Communicator();

private:
	/* data */
	Hub* m_hub;
	std::tr1::shared_ptr<Protocol> m_protocol;
	std::tr1::shared_ptr<netcpp::Server> m_server;
	advcpp::sync::Nthread<netcpp::Server> m_serverThread;
	RegistrarConectorPtr m_registrarConnector; 
	RegistrationHandlerPtr m_registrationHandler;
};

}
#endif /* COMMUNICATOR_H */

