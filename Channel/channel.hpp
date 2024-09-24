#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Client/client.hpp"
#include "../utils/utils.hpp"
#include <sys/socket.h>
#include <iostream>
#include <vector>

class Client;

class Channel
{
    public:
    /*--------------------Constructor--Destructor-------------------*/
    Channel(std::string name);
    ~Channel();
    /*-------------------- Getter--Setter---------------------------*/
    std::string getName() const;
    std::string getTopic() const;
    size_t getLimite() const;
    std::string getPassword() const;
    bool getMode(char mode) const;
    void setTopic(std::string topic);
    std::string setMode(char signe, char mode, std::string optionnel);
    /*-------------------------Fonction----------------------------*/
    void send_message(std::string str, Client *client);
    void remove_client(Client *client);
    void add_client(Client* client);
    std::vector<Client*> membre;
    std::vector<Client*> inviter;
    std::vector<Client*> oprator;

    private:
    /*-------------------------Variable----------------------------*/
    bool _I;
    bool _T;
    bool _K;
    bool _O;
    bool _L;
    int _limite;
    std::string _password;
    std::string _topic;
    std::string _name;
};

#endif