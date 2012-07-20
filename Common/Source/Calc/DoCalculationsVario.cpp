/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"

extern void NettoVario(NMEA_INFO *Basic, DERIVED_INFO *Calculated);
extern void SpeedToFly(NMEA_INFO *Basic, DERIVED_INFO *Calculated);

BOOL DoCalculationsVario(NMEA_INFO *Basic, DERIVED_INFO *Calculated)
{
  static double LastTime = 0;

  NettoVario(Basic, Calculated);
  SpeedToFly(Basic, Calculated);

  // has GPS time advanced?
  if(Basic->Time <= LastTime)
    {
      LastTime = Basic->Time; 
      return FALSE;      
    }
  LastTime = Basic->Time;

  return TRUE;
}
