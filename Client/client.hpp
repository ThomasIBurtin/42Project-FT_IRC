#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Channel/channel.hpp"
#include <iostream>
#include <poll.h>

class Channel;

class Client
{
    public:
    /*--------------------Constructor--Destructor-------------------*/
    Client(int fd, short events, short revents);
    ~Client();
    /*--------------------Getter--Setter----------------------------*/
    std::string getNickname();
    std::string getUsername();
    bool getPassworded();
    bool getNicknamed();
    bool getUsernamed();
    void setNickname(std::string nickname);
    void setUsername(std::string username);
    void setPassworded(bool signe);
    void setNicknamed(bool signe);
    void setUsernamed(bool signe);

    struct pollfd client_pollfd;
    Channel *channel;

    private:
    /*--------------------Variable--------------------------------*/
    std::string _nickname;
    std::string _username;
    bool _passworded;
    bool _nicknamed;
    bool _usernamed;
};

#endif