// Fichier Calendrier.cpp
// Fonction de manipulation de date et heure dans un calendrier
// Savoir si une année est bissextile
// Définir le jour de la semaine depuis la date jj.mm.aa
// Calculer l'heure locale en fonction de l'heure UTC et du fuseau horaire

#include <Arduino.h>
#include "Calendrier.h"

char * EteHiv;
char * EteHivPres;

uint8_t jour_semaine(uint8_t jour, uint8_t mois, uint8_t annee)
{
  uint8_t c = (14-mois)/12;
  uint8_t a = annee-c;
  uint8_t m = mois + 12*c-2;
  uint8_t j = ( jour + a + a/4 - a/100 + a/400 + (31*m)/12 ) % 7;

  if (j ==0)
  {
    j = 7;  
  }
  return j;
}

int Bissextile(Horloge H)
{
  int A = H.D.annee + 2000;
  if(A%4 == 0 && A%100 != 0)
  {
    return 1;
  }
  else if(A%400 == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

Horloge Correction_Heure_Date(Horloge H, pays pays_UTC, int E)
{
  /*Pour la décrémentation de la date car uint8_t ne prend pas de valeur négative*/
  
  int Hheure = H.H.heure;
  int Hmin = H.H.minute;
  int EH = E;
  
  if(H.D.mois >= 3 && H.D.jour_mois >= 28 && H.H.heure >= 2)
  {
    E = 1;
  }
  else if(H.D.mois >= 10 && H.D.jour_mois >= 31 && H.H.heure >= 3)
  {
    E = -1;
  }
  
  if((H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E) >= 24)
  {
    if(H.D.mois == 1 || H.D.mois == 3 || H.D.mois == 5 || H.D.mois == 7 || H.D.mois == 8 || H.D.mois == 10 || H.D.mois == 12)
    {
      if(H.D.jour_mois == 31)
      {
        H.D.jour_mois = 1;
        if(H.D.mois == 12)
        {
          H.D.mois = 1;
          ++H.D.annee;
        }
        else
        {
          ++H.D.mois;
        }
      }
      else
      {
        ++H.D.jour_mois;
      }
    }
    else if(H.D.mois == 2)
    {
      if(Bissextile(H))
      {
        if(H.D.jour_mois == 29)
        {
          H.D.jour_mois = 1;
          H.D.mois = 3;
        }
       
      }
      else
      {
        if(H.D.jour_mois == 28)
        {
          H.D.jour_mois = 1;
          H.D.mois = 3;
        }
      }
    }
    else
    {
      if(H.D.jour_mois == 30)
      {
        H.D.jour_mois = 1;
        ++H.D.mois;
      }
      else
      {
        ++H.D.jour_mois;
      }
    }
   H.H.heure = (H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E)%24;
   H.H.minute = (H.H.minute + pays_UTC.corr.minute)%60;
   return H;
  }
 else if ((Hheure + pays_UTC.corr.heure + ((Hmin + pays_UTC.corr.minute)/60) + E) < 0)
  {
      if(H.D.jour_mois ==1)
      {
        if(H.D.mois ==1)
        {
          H.D.jour_mois =31;
          H.D.mois = 12;
          H.D.annee--;  
        }
        else if(H.D.mois == 3)
        {
          H.D.mois = 2;
          if(Bissextile(H))
          {
            H.D.jour_mois =29;    
          }

          else
          {
            H.D.jour_mois =28;  
          }
        }
        else if (H.D.mois == 8)
        {
            H.D.jour_mois =31;
            H.D.mois--; 
        }
        else
        {
          H.D.mois--;
          H.D.jour_mois =30;
        }
      }

      else
      {
        --H.D.jour_mois;
      }
  H.H.heure = (H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E)+24;
  H.H.minute = (H.H.minute + pays_UTC.corr.minute)%60;
  return H;
  }
  else
  {
    H.H.heure = (H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E)%24;
    H.H.minute = (H.H.minute + pays_UTC.corr.minute)%60;
    return H;
  }
 
  return H;
}

pays fuseau_horaire_de_ref(int i)
{
  /*Definition Tableau pour la correction date_Heure_UTC en fonction du pays*/
  pays France;
  France.pays = "France";
  France.ville = "Paris";
  France.corr.minute = 0;
  France.corr.heure = 1;
   
  pays Angleterre;
  Angleterre.pays = "Royaume-Uni";
  Angleterre.ville = "Londres";
  Angleterre.corr.heure = 0;
  Angleterre.corr.minute = 0;
  
  pays Russie;
  Russie.pays = "Russie";
  Russie.ville = "Moscou";
  Russie.corr.heure = 3;
  Russie.corr.minute = 0;
  
  pays USA;
  USA.pays = "USA";
  USA.ville = "New York";
  USA.corr.heure = -5;
  USA.corr.minute = 0;
  
  pays Canada;
  Canada.pays = "Candada";
  Canada.ville = "Montreal";
  Canada.corr.heure = -5;
  Canada.corr.minute = 0;
  
  pays Japon;
  Japon.pays = "Japon";
  Japon.ville = "Tokyo";
  Japon.corr.heure = 9;
  Japon.corr.minute = 0;
  
  pays Chine;
  Chine.pays = "Chine";
  Chine.ville = "Pekin";
  Chine.corr.heure = 8;
  Chine.corr.minute = 0;
  
  pays FuseauHoraire[7] = {France,Angleterre,Russie,USA,Canada,Japon,Chine};

  return FuseauHoraire[i];
}

int IndicateurEteHiv(Horloge H)
{
  if(H.D.mois >= 3 && H.D.jour_mois >= 28 && H.H.heure >= 2)
    {
      EteHiv = 1;//ete;
    }
    else
    {
      EteHiv =0;// hiver;
    }

    return EteHiv;
}
