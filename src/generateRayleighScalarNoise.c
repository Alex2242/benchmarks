/*! \file generateRayleighScalarNoise.c
    \brief sous-programme generant un scalaire suivant une loi de rayleigh
    \author J.Ph. MOLINIE
    \version 2.0
    \date 05/09/2005
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


void generateRayleighScalarNoise(float param_loi, float *scalaire_rayleigh_real,float *scalaire_rayleigh_imag) {
    /*
        param param_loi parametre de la loi de rayleigh
        retval scalaire_rayleigh scalaire suivant une loi de rayleigh
        return none
    */

    unsigned int g_seed;
    static int compteur_appel=-1;
    time_t temps;
    float var_uni1,var_uni2;

    compteur_appel=compteur_appel+1;
    if (compteur_appel==0) {
        temps=time(0);
        temps=temps-(3666*24*365*(2005-1970));
        temps=(time_t)fmod((double)temps,100000.);
            // 100000 valeurs possibles pour le germe
        g_seed=(unsigned int)temps;

        srand(g_seed);
        // fprintf(stderr,"initialisation du germe (g_seed=%d)\n",g_seed);
    }
    if (compteur_appel>1000000)
        compteur_appel=-1;
        // tous les 1000000 d appels a la fonction on change le germe

    do{
        var_uni1=((float)rand())/((float)RAND_MAX);
    } while(var_uni1 == 0.0);

    /* variable uniforme entre 0 et 1 */
    var_uni2=((float)rand())/((float)RAND_MAX);

    /* variable gaussienne */

    *(scalaire_rayleigh_real) = param_loi* (float)
        (sqrt(-2 * log((double) (var_uni1 + 1.e-20)) ) *
        cos((double)(2.*M_PI*var_uni2)));

    *(scalaire_rayleigh_imag) = param_loi* (float)
        (sqrt(-2. * log((double) (var_uni1 + 1.e-20))) *
        sin((double)(2.*M_PI*var_uni2)));


    /* variable de rayleigh */
    /* 	 *(scalaire_rayleigh)= */
    /* 	   (float) pow((sqrt( (-2. * log((double) (var_uni1 + 1.e-20)) )) * sin((double)(2.*PI*var_uni2))),2.)+ */
    /* 	   (float) pow((sqrt( (-2. * log((double) (var_uni1 + 1.e-20)) )) * cos((double)(2.*PI*var_uni2))),2.); */
    /* 	 *(scalaire_rayleigh)=param_loi* (float)sqrt((double)*(scalaire_rayleigh)); */

    //	 *(scalaire_rayleigh)=param_loi* (float)(sqrt( -2. * log((double) (var_uni1 + 1.e-20)) ) );



    return;
}
