#include "channel.hpp"

/*--------------------Constructor--Destructor-------------------*/

Channel::Channel(std::string name) : _name(name)
{
    this->_limite = 100;
    this->_I = false;
    this->_T = false;
    this->_K = false;
    this->_O = false;
    this->_L = false;
}

Channel::~Channel()
{
    std::cout << "Channel fermé." << std::endl;
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

std::string Channel::setMode(char signe, char mode, std::string optionnel)
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
        {
            this->_I = new_signe;
            if(new_signe)
                return("Mode invitation only actif\n");
            else
                return("Mode invitation only inactif\n");
        }

        case 't':
        {
            this->_T = new_signe;
            if(new_signe)
                return("Mode topic operator only actif\n");
            else
                return("Mode topic operator only inactif\n");
        }

        case 'k':
        {
            this->_K = new_signe;
            if (new_signe)
            {
                if (optionnel.size() == 0)
                    throw std::runtime_error("ERROR: Password required for +k mode\n");
                this->_password = optionnel;
                return("Password actif for this channel\n");
            }
            else
            {
                this->_password.clear();
                return("Password inactif for this channel\n");
            }
        }

        case 'o':
        {
            if (optionnel.size() == 0)
                throw std::runtime_error("ERROR: Client required for o mode\n");
            Client *client = find_client_in_vector(optionnel, this->membre);
            if(!client)
                throw std::runtime_error("ERROR: Client are not in channel\n");
            this->_O = new_signe;
            if(new_signe)
            {
                if(find_client_in_vector(optionnel, this->oprator))
                    throw std::runtime_error("ERROR: Client is already operator\n");
                this->oprator.push_back(client);
                return(client->getNickname() + " is now an operator of " + this->getName() + "\n");
            }
            else
            {
                std::vector<Client*>::iterator it = std::find(this->oprator.begin(), this->oprator.end(), client);
                if(it != this->oprator.end())
                {
                    this->oprator.erase(it);
                    return(client->getNickname() + " is now a basic user of " + this->getName() + "\n");
                }
                else
                    throw std::runtime_error("ERROR: Client are not operator in channel\n");
            }
        }

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
                return("the limite of " + this->getName() + " is " + std::to_string(limite) + "\n");
            }
            else
            {
                this->_limite = 100;
                return("no limit in of people in " + this->getName() + "\n");
            }
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
    std::vector<Client*>::iterator itee = std::find(this->oprator.begin(), this->oprator.end(), client);
    if(client->channel == this)
        client->channel = NULL;
    if(it != this->membre.end())
        this->membre.erase(it);
    if(ite != this->inviter.end())
        this->inviter.erase(ite);
    if(itee != this->oprator.end())
        this->oprator.erase(itee);
}

void Channel::add_client(Client* client)
{
    membre.push_back(client);
    client->channel = this;
    std::string message = "You joined the " + this->getName() + " channel.\n";
    send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
}


