#include "channel.hpp"

/*--------------------Constructor--Destructor-------------------*/

Channel::Channel(std::string name) : _name(name)
{
    this->op = NULL;
    this->_limite = 100;
    this->_I = false;
    this->_T = false;
    this->_K = false;
    this->_O = false;
    this->_L = false;
}

Channel::~Channel()
{
    
}

/*-------------------- Getter--Setter---------------------------*/

std::string Channel::getName() const
{
    return this->_name;
}

std::string Channel::getTopic() const
{
    return this->_topic;
}

size_t Channel::getLimite() const
{
    return this->_limite;
}

std::string Channel::getPassword() const
{
    return this->_password;
}

bool Channel::getMode(char mode) const
{
    switch(mode)
    {
        case 'I':
            return this->_I;
            break;
        case 'T':
            return this->_T;
            break;
        case 'K':
            return this->_K;
            break;
        case 'O':
            return this->_O;
            break;
        case 'L':
            return this->_L;
            break;
        default:
            throw std::runtime_error("ERROR: Mode can only are : i, t, k, o, l\n");
    }
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}

void Channel::setMode(char signe, char mode, std::string optionnel)
{
    bool new_signe;
    if (signe == '+')
        new_signe = true;
    else if (signe == '-')
        new_signe = false;
    else
        throw std::runtime_error("ERROR: Mode sign can only be + or -\n");

    switch (mode)
    {
        case 'i':
            this->_I = new_signe;
            break;

        case 't':
            this->_T = new_signe;
            break;

        case 'k':
        {
            this->_K = new_signe;
            if (new_signe)
            {
                if (optionnel.size() == 0)
                    throw std::runtime_error("ERROR: Password required for +k mode\n");
                this->_password = optionnel;
            }
            else
                this->_password.clear();
            break;
        }

        case 'o':
            this->_O = new_signe;
            break;

        case 'l':
        {
            this->_L = new_signe;
            if (new_signe)
            {
                if (optionnel.size() == 0)
                    throw std::runtime_error("ERROR: Limite required for +l mode\n");
                int limite = atoi(optionnel.c_str());
                if (limite <= 0)
                    throw std::runtime_error("ERROR: Invalid limit value\n");
                this->_limite = limite;
            }
            else
                this->_limite = 100;
            break;
        }
        default:
            throw std::runtime_error("ERROR: Mode can only be i, t, k, o, l\n");
    }
}

/*-------------------------Fonction----------------------------*/

void Channel::send_message(std::string str, Client *client)
{
    for(std::vector<Client*>::iterator it = this->membre.begin(); it != this->membre.end(); it++)
    {
        if(*it != client && ((*it)->channel == client->channel))
        {
            std::string message = str + "\n";
            send((*it)->client_pollfd.fd, message.c_str(), message.size(), 0);
        }
    }
}

void Channel::remove_client(Client *client)
{   
    std::vector<Client*>::iterator it = std::find(this->membre.begin(), this->membre.end(), client);
    std::vector<Client*>::iterator ite = std::find(this->inviter.begin(), this->inviter.end(), client);
    client->channel = NULL;
    this->membre.erase(it);
    if(ite != this->inviter.end())
        this->inviter.erase(ite);
    send(client->client_pollfd.fd, "You have been kicked from the channel.\n", 39, 0);
}

void Channel::add_client(Client* client)
{
    membre.push_back(client);
    client->channel = this;
    std::string message = "You joined the " + this->getName() + " channel.\n";
    send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
}


