#include "utils.hpp"

std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    
    if (start == std::string::npos)
        return "";
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    
    return str.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string &str)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, ' '))
    {
        token = trim(token);
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

Channel* find_channel_by_name(const std::string& name, std::vector<Channel*> channels)
{
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->getName() == name)
            return *it;
    }
    return NULL;
}

Client* find_client_in_vector(const std::string& name, std::vector<Client*> clients)
{
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if ((*it)->getNickname() == name)
            return *it;
    }
    return NULL;
}

void signal_handler(int signum) 
{
    (void)signum;
    server->clean_up();
}