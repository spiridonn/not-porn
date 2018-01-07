#include "eventCommHandler.h"
#include "protocolCommSocket.h"
#include "event.h"

namespace smartCampus
{

EventCommHandler::EventCommHandler(Hub* _hub):
	m_hub(_hub){}

EventCommHandler::~EventCommHandler(){}

netcpp::EventStatus EventCommHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	
	ProtocolMsg msg = static_cast<ProtocolCommSocket*>(_socket.get())->Recv();
	
	Event event = m_factoryDispatcher.CreateEvent(msg);
	
	m_hub->SendEvent(event);
	
	return netcpp::e_statusOk;
}



}
