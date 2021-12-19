#ifndef PLACE_H
#define PLACE_H

#include <pcosynchro/pcoconditionvariable.h>
#include <pcosynchro/pcomutex.h>


class Place
{
public:
    ///
    /// \brief Constructeur
    /// \param nbMaxPeople Nombre maximal de personnes sur cet emplacement
    ///
    Place(unsigned int nbMaxPeople): maxPeople(nbMaxPeople), nbPeople(0)
    {
        // TODO
    }

    ///
    /// \brief Fonction permettant de gérer l'accès à l'emplacement.
    ///
    void access()
    {
        mutex.lock();
        while(nbPeople + 1 > maxPeople){
            isFree.wait(&mutex);
        }
        ++nbPeople;
        mutex.unlock();
    }

    ///
    /// \brief Fonction permettant de quitter la marche proprement
    ///
    void leave()
    {
        mutex.lock();
        --nbPeople;
        isFree.notifyAll();
        mutex.unlock();
    }

private:
    // TODO
    PcoMutex mutex;
    PcoConditionVariable isFree;
    unsigned maxPeople, nbPeople;
};

#endif // PLACE_H
