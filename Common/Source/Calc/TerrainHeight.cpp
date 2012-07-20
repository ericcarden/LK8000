/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"
#include "RasterTerrain.h"


void TerrainHeight(NMEA_INFO *Basic, DERIVED_INFO *Calculated)
{
  short Alt = 0;

  RasterTerrain::Lock();
  // want most accurate rounding here
  RasterTerrain::SetTerrainRounding(0,0);
  Alt = RasterTerrain::GetTerrainHeight(Basic->Latitude, 
                                        Basic->Longitude);
  RasterTerrain::Unlock();

  if(Alt!=TERRAIN_INVALID) { // terrain invalid is now positive  ex. 32767
	Calculated->TerrainValid = true;
	if (Alt>=0) {
		Calculated->TerrainAlt = Alt;
	} else {
		// this can be still a problem for dutch users.. Todo Fix
		Calculated->TerrainAlt = 0;
	}
  } else {
	Calculated->TerrainValid = false; 
	Calculated->TerrainAlt = 0;
  }
  Calculated->AltitudeAGL = Calculated->NavAltitude - Calculated->TerrainAlt;
  if (!FinalGlideTerrain) {
	Calculated->TerrainBase = Calculated->TerrainAlt;
  }
}

