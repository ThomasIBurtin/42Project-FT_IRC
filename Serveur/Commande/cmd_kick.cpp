#include "../serveur.hpp"

void Serveur::cmd_kick(const std::vector<std::string> input_split, Client* client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() != 3)
        throw std::runtime_error("ERROR: Invalid parameters. Usage: /kick #channel user\n");

    const std::string& channel_name = input_split[1];
    const std::string& user_to_kick = input_split[2];

    Channel* channel_find = find_channel_by_name(channel_name);
    Client *client_find = find_client_in_vector(user_to_kick, channel_find->membre);
    if (!channel_find)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    else if(!client_find)
        throw std::runtime_error("ERROR: User not found.\n");
    else if (channel_find->op != client)
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else if(channel_find->op == client_find)
        throw std::runtime_error("ERROR: User cannot be kicked.\n");
    else
        channel_find->remove_client(client_find);
}

Channel* Serveur::find_channel_by_name(const std::string& name)
{
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->getName() == name)
            return *it;
    }
    return NULL;
}