/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"

#include "devFlymasterF1.h"

extern bool UpdateBaroSource(NMEA_INFO* pGPS, const short parserid, const PDeviceDescriptor_t d, const double fAlt);


static BOOL VARIO(PDeviceDescriptor_t d, TCHAR *String, NMEA_INFO *pGPS);

static BOOL FlymasterF1ParseNMEA(PDeviceDescriptor_t d, TCHAR *String, NMEA_INFO *pGPS){

  (void)d;

  if (!NMEAParser::NMEAChecksum(String) || (pGPS == NULL)){
    return FALSE;
  }


  if(_tcsncmp(TEXT("$VARIO"), String, 6)==0)
    {
      return VARIO(d, &String[7], pGPS);
    } 

  return FALSE;

}

/*
static BOOL FlymasterF1IsLogger(PDeviceDescriptor_t d){
  (void)d;
  return(FALSE);
}
*/

static BOOL FlymasterF1IsGPSSource(PDeviceDescriptor_t d){
  (void)d;
  return(TRUE); 
}


static BOOL FlymasterF1IsBaroSource(PDeviceDescriptor_t d){
	(void)d;
  return(TRUE);
}


static BOOL FlymasterF1LinkTimeout(PDeviceDescriptor_t d){
  (void)d;
  return(TRUE);
}


static BOOL flymasterf1Install(PDeviceDescriptor_t d){

  StartupStore(_T(". FlymasterF1 device installed%s"),NEWLINE);

  _tcscpy(d->Name, TEXT("FlymasterF1"));
  d->ParseNMEA = FlymasterF1ParseNMEA;
  d->PutMacCready = NULL;
  d->PutBugs = NULL;
  d->PutBallast = NULL;
  d->Open = NULL;
  d->Close = NULL;
  d->Init = NULL;
  d->LinkTimeout = FlymasterF1LinkTimeout;
  d->Declare = NULL;
  d->IsGPSSource = FlymasterF1IsGPSSource;
  d->IsBaroSource = FlymasterF1IsBaroSource;

  return(TRUE);

}


BOOL flymasterf1Register(void){
  return(devRegister(
    TEXT("FlymasterF1"),
    (1l << dfGPS)
    | (1l << dfBaroAlt)
    | (1l << dfVario),
    flymasterf1Install
  ));
}


// *****************************************************************************
// local stuff

static BOOL VARIO(PDeviceDescriptor_t d, TCHAR *String, NMEA_INFO *pGPS)
{
  // $VARIO,fPressure,fVario,Bat1Volts,Bat2Volts,BatBank,TempSensor1,TempSensor2*CS

  TCHAR ctemp[80];
  NMEAParser::ExtractParameter(String,ctemp,0);
  double ps = StrToDouble(ctemp,NULL);
  UpdateBaroSource( pGPS, 0,d,  	 (1 - pow(fabs(ps / QNH), 0.190284)) * 44307.69);

  NMEAParser::ExtractParameter(String,ctemp,1);
  pGPS->Vario = StrToDouble(ctemp,NULL)/10.0;
  // JMW vario is in dm/s

  NMEAParser::ExtractParameter(String,ctemp,2);
  pGPS->ExtBatt1_Voltage = StrToDouble(ctemp,NULL);
  NMEAParser::ExtractParameter(String,ctemp,3);
  pGPS->ExtBatt2_Voltage = StrToDouble(ctemp,NULL);
  NMEAParser::ExtractParameter(String,ctemp,4);
  pGPS->ExtBatt_Bank = (int)StrToDouble(ctemp,NULL);

/*
  StartupStore(_T("++++++ BATTBANK: "));
  StartupStore(ctemp);
  StartupStore(_T("\n"));
*/

  pGPS->VarioAvailable = TRUE;

  TriggerVarioUpdate();

  return TRUE;
}
