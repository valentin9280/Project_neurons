/**
 * \file main.c
 * \brief Programme de tests spike
 * \author Tartare.V
 * \version 1.0
 * \date 04 novembre 2007
 *
 * Programme de tester pour pour la création de neurones.
 *
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


#define dt 0.5
#define n 100
#define tau_g 10
#define rate 2*1e-3
#define n_in 100

/**
 * \fn createTable
 * \brief Fonction de création de tableau
 *
 * \param self Adresse de ll'objet Str_t à détruire.
 * \return STR_NO_ERR si aucune erreur, STR_EMPTY_ERR sinon.
 */

float **createTable(int nbLin, int nbCol)       //fonction création tableau
{
    float **tableau= (float **)malloc(sizeof(float*)*nbLin);
    float *tableau2= (float *)malloc(sizeof(float)*nbCol*nbLin);
    int i;
    for(i=0;i<nbLin;i++)
    {
        tableau[i] = &tableau2[i*nbCol];
    }
    return tableau;
}


/**
 * \fn freeTable
 * \brief Libération de l'espace mémoire
 *
 * \param self Adresse de ll'objet Str_t à détruire.
 * \return STR_NO_ERR si aucune erreur, STR_EMPTY_ERR sinon.
 */

void freeTable(float **tableau){
    free(tableau[0]);
    free(tableau);
}


int main(void)
{
    float p[n],inh[n],exc[n],a[n],d[n],du[n],dv[n],Iapp[n],g_in[n_in],E_in[n_in],W_in[n][n_in];
    int T,i,j,t,k;
    int fired[n];
    srand(time(NULL));
    T= ceil(1000/dt);
    float **v=NULL;
    float **u=NULL;
    //float **spks=NULL;
    v= createTable(n,T);
    u= createTable(n,T);
    //spks= createTable(n,T);

    for(i=0;i<n;i++)        // Initialize parameters
    {
        inh[i]= ((float)(rand()%100));
        if(inh[i]<20)inh[i]=1;
        else inh[i]=0;

        if(inh[i]==1)exc[i]=0;
        else exc[i]=1;

        d[i]=8*exc[i]+2*inh[i];
        a[i]=0.02*exc[i]+0.1*inh[i];
    }

    for(i=0;i<n;i++)          // reserve memory
    {
        for(j=0;j<T;j++)
        {
            if(j==0)
            {
                v[i][j]= -70;
                u[i][j]= -14;
            }
            else
            {
                v[i][j]= 0;
                u[i][j]= 0;
            }
        }
    }


    for(j=0;j<n_in;j++)
    {
        g_in[i]=0;
        E_in[i]=0;
        for(i=0;i<n;i++)
        {
            W_in[i][j]= 10*0.070;
            k= rand()%100;
            if(k>10) W_in[i][j]=0;

            //printf("%f",W_in[i][j]);
        }

    }
    for(t=1;t<(T-1);t++)

    {
        if((t*dt>200) && (t*dt<700))
        {
            for(i=0;i<n_in;i++)
            {
                p[i] = ((float)(rand()%100));
                if(p[i]<(rate*dt)) p[i]=1;
                else p[i]=0;
            }
        }else for(i=0;i<n_in;i++)p[i]=0;

        for(j=0;j<n_in;j++)
        {
            for(i=0;i<n;i++)
            {
                g_in[i]=g_in[i] +p[i];
                Iapp[i] = W_in[i][j]+(g_in[i] * E_in[i]);
                Iapp[i] = Iapp[i]-(W_in[i][j]*g_in[i])*v[t][0];
                printf("%f",Iapp[i]);
                g_in[i] = (1-dt/tau_g)*g_in[i];
            }
        }

        for(i=0;i<n;i++)
        {
            dv[i] =(0.04*v[t][0]+5)*v[t][0]+140-u[t][0];
            v[t+1][0]=v[t][0]+(dv[i]+Iapp[i])*dt;
            du[i] =a[n]*(0.2*v[t][0]-u[t][0]);
            u[t+1][0]=u[t][0]+dt*du[i];
            if(v[t][0]<=35)fired[i]= v[t][0];
            v[fired[i]][t] = 35;
            v[fired[i]][t+1]= -65;
            u[fired[i]][t+1]= u[fired[i]][t]+d[i];

            //printf("%f",dv[n]);

        }


    }


    return 0;
}

