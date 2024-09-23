#include "client.hpp"

/*--------------------Constructor--Destructor-------------------*/

Client::Client(int fd, short events, short revents)
{
    this->channel = NULL;
    this->_passworded = false;
    this->_usernamed = false;
    this->_nicknamed = false;
    this->client_pollfd.fd = fd;
    this->client_pollfd.events = events;
    this->client_pollfd.revents = revents;
}

Client::~Client()
{

}

/*--------------------Getter--Setter----------------------------*/

std::string Client::getUsername()
{
    return this->_username;
}

std::string Client::getNickname()
{
    return this->_nickname;
}

bool Client::getPassworded()
{
    return this->_passworded;
}

bool Client::getNicknamed()
{
    return this->_nicknamed;
}

bool Client::getUsernamed()
{
    return this->_usernamed;
}

void Client::setNickname(std::string nickname)
{
    this->_nickname = nickname;
}

void Client::setUsername(std::string username)
{
    this->_username = username;
}

void Client::setPassworded(bool signe)
{
    this->_passworded = signe;
}

void Client::setNicknamed(bool signe)
{
    this->_nicknamed = signe;
}

void Client::setUsernamed(bool signe)
{
    this->_usernamed = signe;
}