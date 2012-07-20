/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"

extern void InsertLDRotary(ldrotary_s *buf, int distance, NMEA_INFO *Basic, DERIVED_INFO *Calculated);
extern void InsertWindRotary(windrotary_s *wbuf, double speed, double track, double altitude);


double LimitLD(double LD) {
  if (fabs(LD)>INVALID_GR) {
    return INVALID_GR;
  } else {
    if ((LD>=0.0)&&(LD<1.0)) {
      LD= 1.0;
    } 
    if ((LD<0.0)&&(LD>-1.0)) {
      LD= -1.0;
    }
    return LD;
  }
}


double UpdateLD(double LD, double d, double h, double filter_factor) {
  double glideangle;
  if (LD != 0) {
    glideangle = 1.0/LD;
  } else {
    glideangle = 1.0;
  }
  if (d!=0) {
    glideangle = LowPassFilter(1.0/LD, h/d, filter_factor);
    if (fabs(glideangle) > 1.0/INVALID_GR) {
      LD = LimitLD(1.0/glideangle);
    } else {
      LD = INVALID_GR;
    }
  }
  return LD;
}


void LD(NMEA_INFO *Basic, DERIVED_INFO *Calculated)
{
  static double LastLat = 0;
  static double LastLon = 0;
  static double LastTime = 0;
  static double LastAlt = 0;

  if (Basic->Time<LastTime) {
    LastTime = Basic->Time;
    Calculated->LDvario = INVALID_GR;
    Calculated->LD = INVALID_GR;
  } 
  if(Basic->Time >= LastTime+1.0)
    {
      double DistanceFlown;
      DistanceBearing(Basic->Latitude, Basic->Longitude, 
                      LastLat, LastLon,
                      &DistanceFlown, NULL);

      Calculated->LD = UpdateLD(Calculated->LD,
                                DistanceFlown,
                                LastAlt - Calculated->NavAltitude, 0.1);

      InsertLDRotary(&rotaryLD,(int)DistanceFlown, Basic, Calculated);
      InsertWindRotary(&rotaryWind, Basic->Speed, Basic->TrackBearing, Calculated->NavAltitude); // 100103
      if (DistanceFlown >3 && DistanceFlown<300) Calculated->Odometer += DistanceFlown;

      LastLat = Basic->Latitude;
      LastLon = Basic->Longitude;
      LastAlt = Calculated->NavAltitude;
      LastTime = Basic->Time;
    }

  // LD instantaneous from vario, updated every reading..
  if (Basic->VarioAvailable && Basic->AirspeedAvailable 
      && Calculated->Flying) {
    Calculated->LDvario = UpdateLD(Calculated->LDvario,
                                   Basic->IndicatedAirspeed,
                                   -Basic->Vario,
                                   0.3);
  } else {
    Calculated->LDvario = INVALID_GR;
  }
}



void CruiseLD(NMEA_INFO *Basic, DERIVED_INFO *Calculated)
{

  if(!Calculated->Circling)
    {
      double DistanceFlown;

      if (Calculated->CruiseStartTime<0) {
        Calculated->CruiseStartLat = Basic->Latitude;
        Calculated->CruiseStartLong = Basic->Longitude;
        Calculated->CruiseStartAlt = Calculated->NavAltitude;
        Calculated->CruiseStartTime = Basic->Time;
      } else {

        DistanceBearing(Basic->Latitude, Basic->Longitude, 
                        Calculated->CruiseStartLat, 
                        Calculated->CruiseStartLong, &DistanceFlown, NULL);
        Calculated->CruiseLD = 
          UpdateLD(Calculated->CruiseLD,
                   DistanceFlown,
                   Calculated->CruiseStartAlt - Calculated->NavAltitude,
                   0.5);
      }
    }
}


