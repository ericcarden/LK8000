/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"
#include "McReady.h"

void Flaps(NMEA_INFO *Basic, DERIVED_INFO *Calculated)
{	
	double speed = 0.0;
	if (GlidePolar::FlapsMass<=0) return; // avoid division by zero crashes
	if (Basic->AirspeedAvailable) {
		speed = (int)(Basic->IndicatedAirspeed);
	} else {
		speed = (int)(Calculated->IndicatedAirspeedEstimated);
	}

	double massCorrectionFactor = sqrt(GlidePolar::GetAUW()/GlidePolar::FlapsMass);

	for (int i=0;i<GlidePolar::FlapsPosCount-1;i++) {
		if (speed >= GlidePolar::FlapsPos[i]*massCorrectionFactor 
			&& speed < GlidePolar::FlapsPos[i+1]*massCorrectionFactor) {
			wcscpy(Calculated->Flaps,GlidePolar::FlapsName[i]);
		}
	}	
}
