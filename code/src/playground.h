#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <pcosynchro/pcohoaremonitor.h>

class Playground : PcoHoareMonitor
{
public:
    ///
    /// \brief Constructeur
    /// \param nbKidsToLeave Nombre d'enfants permettant de relâcher la moitié d'entre eux
    ///
    Playground(unsigned int nbKidsToLeave): nbPlaying(0), threshold(nbKidsToLeave)
    {
        // TODO
    }

    ///
    /// \brief Fonction bloquante jusqu'à ce que le bon nombre d'enfants soit atteint
    ///
    /// Cette fonction doit bloquer les enfants jusqu'à ce que le bon nombre d'entre
    /// eux soient présents. A ce moment-là la moitié des enfants présents doivent
    /// repartir.
    ///
    void play()
    {
        // TODO
        monitorIn();
        ++nbPlaying;
        if(nbPlaying < threshold) {
            // Chaque enfant joue
            PcoHoareMonitor::wait(cond);
        }else{
            // Les enfants partent au toboggan
            for( unsigned i = 0; i <= threshold / 2; ++i){
                --nbPlaying;
                PcoHoareMonitor::signal(cond);
            }
        }
        monitorOut();
    }


private:
    unsigned int nbPlaying, threshold;
    Condition cond;
};

#endif // PLAYGROUND_H
