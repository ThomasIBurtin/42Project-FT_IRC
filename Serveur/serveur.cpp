#include "serveur.hpp"

/*--------------------Constructor--Destructor-------------------*/

Serveur::Serveur(int port, std::string password) : _password(password), _port(port)
{
    command_map["/pass"] = &Serveur::cmd_pass;
    command_map["/nick"] = &Serveur::cmd_nick;
    command_map["/user"] = &Serveur::cmd_user;
    command_map["/join"] = &Serveur::cmd_join;
    command_map["/privmsg"] = &Serveur::cmd_privmsg;
    command_map["/kick"] = &Serveur::cmd_kick;
    command_map["/topic"] = &Serveur::cmd_topic;
    command_map["/mode"] = &Serveur::cmd_mode;
    command_map["/invite"] = &Serveur::cmd_invite;
}

Serveur::~Serveur()
{
    close(this->_server_socket);
    std::cout << "Serveur fermé." << std::endl;
    exit(0);
}

/*--------------------Fonctions----------------------------------*/

void Serveur::create_serveur()
{
    struct sockaddr_in server_addr;

    this->_server_socket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(this->_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(this->_port);

    bind(this->_server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(this->_server_socket, 10);

    std::cout << "Serveur en écoute sur le port " << this->_port << "..." << std::endl;

    Client* serveur = new Client(this->_server_socket, POLLIN, 0);
    this->clients.push_back(serveur);
}

void Serveur::manage_client()
{
    while (true)
    {
        wait_evenement();
        for (size_t i = 0; i < clients.size(); i++)
        {
            if (clients[i]->client_pollfd.fd == this->_server_socket && (clients[i]->client_pollfd.revents & POLLIN))
                NewClientInServ();
            else if(clients[i]->client_pollfd.revents & POLLIN)
                ClientInput(clients[i], i);
        }
    }
}

void Serveur::wait_evenement()
{
    std::vector<struct pollfd> poll_fds;
    for (std::vector<Client*>::iterator it = this->clients.begin(); it != clients.end(); it++)
        poll_fds.push_back((*it)->client_pollfd);

    poll(poll_fds.data(), poll_fds.size(), -1);

    for (size_t i = 0; i < poll_fds.size(); ++i)
        this->clients[i]->client_pollfd.revents = poll_fds[i].revents;
}

void Serveur::NewClientInServ()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int new_socket = accept(this->_server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    fcntl(new_socket, F_SETFL, O_NONBLOCK);
    std::cout << "Nouvelle connexion de " << inet_ntoa(client_addr.sin_addr) << std::endl;
    Client* client = new Client(new_socket, POLLIN, 0);
    this->clients.push_back(client);
}

void Serveur::ClientInput(Client *client, size_t &i)
{
    char input[1024] = {0};
    int valread = recv(client->client_pollfd.fd, input, sizeof(input), 0);
    if (valread > 0)
        this->parse_input(std::string(input), client);
    else if (valread == 0)
    {
        for(std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
        {
            if(find_client_in_vector(client->getNickname(), (*it)->membre) || find_client_in_vector(client->getNickname(), (*it)->inviter))
                (*it)->remove_client(client);
        }
        clients.erase(clients.begin() + i);
        i--;
        delete client;
    }
}

void Serveur::parse_input(std::string input, Client *client)
{
    std::vector<std::string> input_split = split(input);
    std::map<std::string, void (Serveur::*)(std::vector<std::string>, Client*)>::iterator it = this->command_map.find(input_split[0]);
    try
    {
        if(it != this->command_map.end())
            (this->*(it->second))(input_split, client);
        else if(client->channel != NULL)
            client->channel->send_message(input, client);
        else
            throw std::runtime_error("ERROR: No existing command\n");
    }
    catch(const std::exception& e)
    {
        send(client->client_pollfd.fd, e.what(), strlen(e.what()), 0);
    }
}

void Serveur::clean_up()
{
    if (!clients.empty())
    {
        for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end();)
        {
            delete *it;            
            it = clients.erase(it);
        }
    }

    if (!channels.empty())
    {
        for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end();)
        {
            delete *it;              
            it = channels.erase(it);
        }
    }
    delete this;
}

