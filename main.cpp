#include "Serveur/serveur.hpp"

Serveur *server = nullptr;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }
    server = new Serveur(atoi(argv[1]), argv[2]);
    std::signal(SIGINT, signal_handler);
    server->create_serveur();
    server->manage_client();
}
