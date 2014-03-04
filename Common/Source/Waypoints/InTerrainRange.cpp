/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"
#include "Waypointparser.h"
#include "RasterTerrain.h"
#include "Dialogs.h"


extern int WaypointOutOfTerrainRangeDontAskAgain;


bool WaypointInTerrainRange(WAYPOINT *List) {

  if (WaypointOutOfTerrainRangeDontAskAgain == 1){
    return(true);
  }

  if (!RasterTerrain::isTerrainLoaded()) {
    return(true);
  }

  if (RasterTerrain::WaypointIsInTerrainRange(List->Latitude,
                                              List->Longitude)) {
    return true;
  } else {
    if (WaypointOutOfTerrainRangeDontAskAgain == 0){
      
      TCHAR sTmp[250];
      int res;

      _stprintf(sTmp, _T("Waypoint #%d \"%s\" \r\n%s\r\n\r\n%s"), 
                List->Number, List->Name,
	// LKTOKEN  _@M837_ = "out of Terrain bound" 
		gettext(TEXT("_@M837_")),
	// LKTOKEN  _@M395_ = "Load anyway?" 
		gettext(TEXT("_@M395_")));
      
      res = dlgWaypointOutOfTerrain(sTmp);
      
      switch(res){
      case wpTerrainBoundsYes: 
        return true;
      case wpTerrainBoundsNo: 
        return false;
      case wpTerrainBoundsYesAll: 
        WaypointOutOfTerrainRangeDontAskAgain = 1;
        // WaypointsOutOfRange = 1; // this would override user choice in configuration!
        return true;
      case mrCancle: 
      case wpTerrainBoundsNoAll: 
        WaypointOutOfTerrainRangeDontAskAgain = 2;
        // WaypointsOutOfRange = 2; // this would override user choice in configuration!
        return false;
      }
      
    } else {
      if (WaypointOutOfTerrainRangeDontAskAgain == 2)
        return(false);
      if (WaypointOutOfTerrainRangeDontAskAgain == 1)
        return(true);
    }
    return false;
  }
}
