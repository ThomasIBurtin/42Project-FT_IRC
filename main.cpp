#include "Serveur/serveur.hpp"


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "need port ans password" << std::endl;
        return 1;
    }
    Serveur serveur(atoi(argv[1]), argv[2]);
}
