#include "../serveur.hpp"

void Serveur::cmd_topic(const std::vector<std::string> input_split, Client* client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed())
        throw std::runtime_error("ERROR: You are not identified.\n"); 
    if (input_split.size() < 2 || input_split.size() > 3)
        throw std::runtime_error("ERROR: Invalid parameters. Usage: /topic #channel new topic\n");

    const std::string& new_topic_channel = input_split[2];
    Channel* channel_topic = find_channel_by_name(input_split[1], this->channels);
    if (!channel_topic)
        throw std::runtime_error("ERROR: Channel does not exist.\n");  
    else if(input_split.size() == 2)
    {
        if(channel_topic->getTopic().empty())
            throw std::runtime_error("ERROR: Not topic in this channel\n");
        std::string message = "the topic of " + channel_topic->getName() + " is " + channel_topic->getTopic() + "\n";
        send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
    }
    else if (!find_client_in_vector(client->getNickname(), channel_topic->oprator) && (channel_topic->getMode('T') == true))
        throw std::runtime_error("ERROR: You need to be an operator for modify topic.\n");
    else
    {
        channel_topic->setTopic(new_topic_channel);
        std::string message = "the new topic of " + channel_topic->getName() + " is " + channel_topic->getTopic() + "\n";
        send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
    }
}