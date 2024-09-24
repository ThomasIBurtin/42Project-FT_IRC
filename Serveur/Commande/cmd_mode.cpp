#include "../serveur.hpp"

void Serveur::cmd_mode(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 3 || input_split.size() > 4 || input_split[2].size() != 2)
        throw std::runtime_error("ERROR: Format is mode channel mode\n");

    const char signe = input_split[2][0];
    const char mode = input_split[2][1];
    Channel *channel_mode = find_channel_by_name(input_split[1], this->channels);
    if(!channel_mode)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    else if(channel_mode->op != client)
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else
    {
        if(input_split.size() > 3)
            channel_mode->setMode(signe, mode, input_split[3]);
        else
            channel_mode->setMode(signe, mode, "");
        std::string message = channel_mode->getName() + " change mode : " + mode + " with " + signe + "\n";
        send(client->client_pollfd.fd, message.c_str(), message.length(), 0);
    }
}
