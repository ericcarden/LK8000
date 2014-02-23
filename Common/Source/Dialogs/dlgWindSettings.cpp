/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id: dlgWindSettings.cpp,v 1.1 2011/12/21 10:29:29 root Exp root $
*/

#include "externs.h"
#include "LKProfiles.h"
#include "Dialogs.h"

#define SIM_MANUAL_WIND // In sim mode, only allow Auto Wind to be "Manual"
// There's an identical #define in dlgConfiguration.cpp, where there are
// related changes.

extern HWND   hWndMainWindow;
static WndForm *wf=NULL;

static void OnCancelClicked(WindowControl * Sender){
	(void)Sender;
  wf->SetModalResult(mrOK);
}

static void UpdateWind(bool set) {
  WndProperty *wp;
  double ws = 0.0, wb = 0.0;
  wp = (WndProperty*)wf->FindByName(TEXT("prpSpeed"));
  if (wp) {
    ws = wp->GetDataField()->GetAsFloat()/SPEEDMODIFY;
  }
  wp = (WndProperty*)wf->FindByName(TEXT("prpDirection"));
  if (wp) {
    wb = wp->GetDataField()->GetAsFloat();
  }
  if ((ws != CALCULATED_INFO.WindSpeed)
      ||(wb != CALCULATED_INFO.WindBearing)) {
    if (set) {
      SetWindEstimate(ws, wb);
    }
    CALCULATED_INFO.WindSpeed = ws;
    CALCULATED_INFO.WindBearing = wb;
  }
}


static void OnCloseClicked(WindowControl * Sender){
	(void)Sender;
        UpdateWind(true);
  wf->SetModalResult(mrOK);
}


static void OnWindSpeedData(DataField *Sender, DataField::DataAccessKind_t Mode){

  switch(Mode){
    case DataField::daGet:
      Sender->SetMax(SPEEDMODIFY*(200.0/TOKPH));
      Sender->Set(SPEEDMODIFY*CALCULATED_INFO.WindSpeed);
    break;
    case DataField::daPut:
      UpdateWind(false);
    break;
    case DataField::daChange:
    default:
      // calc alt...
    break;
  }
}

static void OnWindDirectionData(DataField *Sender, DataField::DataAccessKind_t Mode){

  double lastWind;

  switch(Mode){
	case DataField::daGet:
		lastWind = CALCULATED_INFO.WindBearing;
		if (lastWind>=359)
			lastWind=0;
		Sender->Set(lastWind);
		break;
	case DataField::daPut:
		UpdateWind(false);
		break;
	case DataField::daChange:
		lastWind = Sender->GetAsFloat();
		if (lastWind > 359)
			Sender->Set(0.0);
		break;
	default:
		break;
	}
}

static CallBackTableEntry_t CallBackTable[]={
  DeclareCallBackEntry(OnWindSpeedData),
  DeclareCallBackEntry(OnWindDirectionData),
  DeclareCallBackEntry(OnCancelClicked),
  DeclareCallBackEntry(OnCloseClicked),
  DeclareCallBackEntry(NULL)
};

void dlgWindSettingsShowModal(void){

  char filename[MAX_PATH];
  LocalPathS(filename, TEXT("dlgWindSettings.xml"));
  wf = dlgLoadFromXML(CallBackTable, 
		      
                      filename, 
		      hWndMainWindow,
		      TEXT("IDR_XML_WINDSETTINGS"));

  if (wf) {
    WndProperty* wp;

    wp = (WndProperty*)wf->FindByName(TEXT("prpSpeed"));
    if (wp) {
      wp->GetDataField()->SetUnits(Units::GetHorizontalSpeedName());
      wp->RefreshDisplay();
    }

    wp = (WndProperty*)wf->FindByName(TEXT("prpAutoWind"));
    if (wp) {
      DataFieldEnum* dfe;
      dfe = (DataFieldEnum*)wp->GetDataField();
	// LKTOKEN  _@M418_ = "Manual" 
      dfe->addEnumText(gettext(TEXT("_@M418_")));
      
      #ifdef SIM_MANUAL_WIND
      // In sim mode, Manual is the only option.
      if (!SIMMODE) {
        dfe->addEnumText(MsgToken(175)); // "Circling"
        dfe->addEnumText(gettext(TEXT("ZigZag")));
        dfe->addEnumText(MsgToken(149)); // "Both"
        dfe->addEnumText(MsgToken(1793)); // "External"
      }
      #else
	// LKTOKEN  _@M175_ = "Circling" 
      dfe->addEnumText(gettext(TEXT("_@M175_")));
      dfe->addEnumText(gettext(TEXT("ZigZag")));
	// LKTOKEN  _@M149_ = "Both" 
      dfe->addEnumText(gettext(TEXT("_@M149_")));
      dfe->addEnumText(MsgToken(1793)); // External
      #endif

      wp->GetDataField()->Set(AutoWindMode);
      wp->RefreshDisplay();

      wp = (WndProperty*)wf->FindByName(TEXT("prpTrailDrift"));
      if (wp) {
        wp->GetDataField()->Set(MapWindow::EnableTrailDrift);
        wp->RefreshDisplay();
      }
    }

    wf->ShowModal();

    wp = (WndProperty*)wf->FindByName(TEXT("prpAutoWind"));
    if (wp) {
      if (AutoWindMode != wp->GetDataField()->GetAsInteger()) {
	AutoWindMode = wp->GetDataField()->GetAsInteger();
      }
    }
    wp = (WndProperty*)wf->FindByName(TEXT("prpTrailDrift"));
    if (wp) {
      if (MapWindow::EnableTrailDrift != wp->GetDataField()->GetAsBoolean()) {
        MapWindow::EnableTrailDrift = wp->GetDataField()->GetAsBoolean();
      }
    }
    
    delete wf;
  }
  wf = NULL;

}

