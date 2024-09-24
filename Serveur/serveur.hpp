#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "../Channel/channel.hpp"
#include "../Client/client.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <poll.h>
#include <fcntl.h>
#include <vector>
#include <map>

class Serveur
{
    public:
    /*--------------------Constructor--Destructor-------------------*/
    Serveur(int port, std::string password);
    ~Serveur();
    /*--------------------Commande----------------------------------*/
    void cmd_pass(std::vector<std::string> input_split, Client *client);
    void cmd_nick(std::vector<std::string> input_split, Client *client);
    void cmd_user(std::vector<std::string> input_split, Client *client);
    void cmd_join(std::vector<std::string> input_split, Client *client);
    void cmd_privmsg(std::vector<std::string> input_split, Client *client);
    void cmd_kick(std::vector<std::string> input_split, Client *client);
    void cmd_topic(const std::vector<std::string> input_split, Client* client);
    void cmd_mode(std::vector<std::string> input_split, Client *client);
    void cmd_invite(std::vector<std::string> input_split, Client *client);
    /*--------------------Fonctions----------------------------------*/
    void create_serveur();
    void wait_evenement();
    void manage_client();
    void NewClientInServ();
    void ClientInput(Client *client, size_t &i);
    void parse_input(std::string input, Client *client);
    std::vector<Client*> clients;
    std::vector<Channel*> channels;
    std::map<std::string, void (Serveur::*)(std::vector<std::string>, Client*)> command_map;
    
    private:
    /*--------------------Variable----------------------------------*/
    std::string _password;
    int _port;
    int _server_socket;
};

#endif
