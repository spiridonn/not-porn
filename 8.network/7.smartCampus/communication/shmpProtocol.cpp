#include <stdexcept> //runtime_error
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm> // std::for_each

#include "shmpProtocol.h"
#include "netExceptions.h" //netcpp::BadRequest_error

namespace smartCampus
{

const std::string ShmpProtocol::m_messageBegin = "SHMP:";
const std::string ShmpProtocol::m_messageEnd = "\0";

static const std::pair<std::string,std::string> responses[] = 
{
	std::pair<std::string, std::string>("ok", "SHMP: status 200 OK")
,	std::pair<std::string, std::string>("badRequest", "SHMP: status 400 Bad Request")
,	std::pair<std::string, std::string>("error", "SHMP: status 500 Internal Server Error")
};
std::map<std::string, std::string> ShmpProtocol::m_responseMap(responses, responses + sizeof(responses) / sizeof(responses[0]));

ShmpProtocol::~ShmpProtocol(){}

void ShmpProtocol::ValidateProtocol(std::stringstream& _msgStream) const
{
	std::string identifier;
	
	_msgStream >> identifier;
	if(identifier != m_messageBegin)
	{
		throw netcpp::BadRequest_error("ShmpProtocol::GetValues: wrong protocol type");
	}
}

void ShmpProtocol::GetTopic(std::stringstream& _msgStream, ProtocolMsg& _msg) const
{
	if(_msgStream.eof())
	{
		throw netcpp::BadRequest_error("ShmpProtocol::GetValues: missing header");
	}
	_msgStream >> _msg.m_topic;
}

void ShmpProtocol::GetValues(std::stringstream& _msgStream, ProtocolMsg& _msg) const
{
	std::string value;
	while(!_msgStream.eof())
	{
		_msgStream >> value;
		_msg.m_values.push_back(value);
	}
}

ProtocolMsg ShmpProtocol::ParseMessage(char* _data, std::size_t _length)
{
	std::stringstream msgStream(std::string(_data, _length - 1));
	ValidateProtocol(msgStream);
	
	ProtocolMsg result;
	
	GetTopic(msgStream, result);
	GetValues(msgStream, result);
	
	return result;
}

std::string ShmpProtocol::CreateMsg(const ProtocolMsg& _msg)
{
	std::stringstream result;
	
	// insert header and topic
	result << m_messageBegin << " " << _msg.m_topic;
	
	// insert values
	std::for_each(_msg.m_values.begin(), _msg.m_values.end(), ShmpProtocol::InsertValueToStream(result));
	
	//insert end of msg
	result << m_messageEnd;
	
	return result.str();
}

std::string ShmpProtocol::GetResponse(const std::string& _type) const
{
	std::map<std::string, std::string>::iterator responseItr = m_responseMap.find(_type);
	if(m_responseMap.end() == responseItr)
	{
		throw std::runtime_error("ShmpProtocol::GetResponse: type desn't exist");
	}
	
	return responseItr->second;
}

}
