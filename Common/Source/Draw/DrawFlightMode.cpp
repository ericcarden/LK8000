/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"
#include "Bitmaps.h"
#include "Multimap.h"

extern bool FastZoom;

//
// Bottom right corner indicators: Flight mode, Battery, Logger
//
void MapWindow::DrawFlightMode(HDC hdc, const RECT rc)
{
  static bool flip= true; 
  int offset = -1;

  //
  // Logger indicator
  //
  flip = !flip;

  if (!DisableAutoLogger || LoggerActive) {
	if (LoggerActive || flip) {
		if (LoggerActive)
			SelectObject(hDCTemp,hLogger);
		else
			SelectObject(hDCTemp,hLoggerOff);

		offset -= 7;

		DrawBitmapX(hdc, rc.right+IBLSCALE(offset),
			rc.bottom - BottomSize+NIBLSCALE(4),
			7,7, hDCTemp, 0,0,SRCPAINT,true);

		DrawBitmapX(hdc, rc.right+IBLSCALE(offset),
			rc.bottom-BottomSize+NIBLSCALE(4),
			7,7, hDCTemp, 7,0,SRCAND,true);

		offset +=7;
	}
  }
  

  //
  // Flight mode Icon
  //
  short iconsizex, iconsizey;

  #if 1
  if (IsMultiMapNoMain()) {
	short i=Get_Current_Multimap_Type()-1;
  #else
  if (1) {
	short i=ModeType[LKMODE_MAP];
  #endif
	switch(i) {
		case 1:
			SelectObject(hDCTemp,hMM1);
			break;
		case 2:
			SelectObject(hDCTemp,hMM2);
			break;
		case 3:
			SelectObject(hDCTemp,hMM3);
			break;
		case 4:
			SelectObject(hDCTemp,hMM4);
			break;
		case 5:
			SelectObject(hDCTemp,hMM5);
			break;
		case 6:
			SelectObject(hDCTemp,hMM6);
			break;
		case 7:
			SelectObject(hDCTemp,hMM7);
			break;
		case 8:
			SelectObject(hDCTemp,hMM8);
			break;
		default:
			SelectObject(hDCTemp,hMM0);
			break;
	}
	iconsizex=22;
	iconsizey=22;
	goto _afternotmultimap;
  } else {
	iconsizex=20;
	iconsizey=24;
  }


  if (mode.Is(Mode::MODE_CIRCLING)) {
	SelectObject(hDCTemp,hClimb);
  } else {
	if (mode.Is(Mode::MODE_FINAL_GLIDE)) {
		SelectObject(hDCTemp,hFinalGlide);
	} else {
		SelectObject(hDCTemp,hCruise);
	}
 }

_afternotmultimap:

  offset -= iconsizey;

  DrawBitmapX(hdc,
	rc.right+IBLSCALE(offset-1),
	rc.bottom+IBLSCALE(-iconsizex-1),
	iconsizey,iconsizex,
	hDCTemp,
	0,0,SRCPAINT,true);
    
  DrawBitmapX(hdc,
	rc.right+IBLSCALE(offset-1),
	rc.bottom+IBLSCALE(-iconsizex-1),
	iconsizey,iconsizex,
	hDCTemp,
	iconsizey,0,SRCAND,true);


  //
  // Battery indicator
  // 

  #if TESTBENCH
  // Battery test in Simmode
  if (SIMMODE && !(QUICKDRAW)) {; PDABatteryPercent-=1; if (PDABatteryPercent<0) PDABatteryPercent=100; }
  #endif

  if ((PDABatteryPercent==0 || PDABatteryPercent>100) && PDABatteryStatus==AC_LINE_ONLINE && PDABatteryFlag!=BATTERY_FLAG_CHARGING) {
	SelectObject(hDCTemp,hBatteryFullC);
	goto _drawbattery;
  }

  if (PDABatteryPercent<=6) {
	if (flip) return;
	SelectObject(hDCTemp,hBattery12);
	goto _drawbattery;
  }

  if (PDABatteryPercent<=12) {
	SelectObject(hDCTemp,hBattery12);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=24) {
	SelectObject(hDCTemp,hBattery24);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=36) {
	SelectObject(hDCTemp,hBattery36);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=48) {
	SelectObject(hDCTemp,hBattery48);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=60) {
	SelectObject(hDCTemp,hBattery60);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=72) {
	SelectObject(hDCTemp,hBattery72);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=84) {
	SelectObject(hDCTemp,hBattery84);
	goto _drawbattery;
  }
  if (PDABatteryPercent<=96) {
	SelectObject(hDCTemp,hBattery96);
	goto _drawbattery;
  }
  if (PDABatteryStatus==AC_LINE_ONLINE)
	SelectObject(hDCTemp,hBatteryFullC);
  else
	SelectObject(hDCTemp,hBatteryFull);

_drawbattery:
  if (!DisableAutoLogger || LoggerActive) offset-=5;
  DrawBitmapX(hdc,
	rc.right+IBLSCALE(offset-1),
	rc.bottom - BottomSize + NIBLSCALE(2),
	22,11,
	hDCTemp,
	0,0,SRCPAINT,true);
    
  DrawBitmapX(hdc,
	rc.right+IBLSCALE(offset-1),
	rc.bottom - BottomSize + NIBLSCALE(2),
	22,11,
	hDCTemp,
	22,0,SRCAND,true);

}


