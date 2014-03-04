/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"


void Statistics::DrawXGrid(HDC hdc, const RECT rc, 
			   const double tic_step, 
			   const double zero,
                           const int Style, 
			   const double unit_step, bool draw_units) {

  if(INVERTCOLORS)
    SelectObject(hdc, GetStockObject(BLACK_PEN));


  POINT line[2];

  double xval;
  SIZE tsize;

  int xmin, ymin, xmax, ymax;
  if (!tic_step) return;
  LKASSERT(tic_step!=0);

  //  bool do_units = ((x_max-zero)/tic_step)<10;

  for (xval=zero; xval<= x_max; xval+= tic_step) {

    xmin = (int)((xval-x_min)*xscale)+rc.left+BORDER_X;
    ymin = rc.top;
    xmax = xmin;
    ymax = rc.bottom;
    line[0].x = xmin;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax-BORDER_Y;

    // STYLE_THINDASHPAPER
    if ((xval< x_max) 
        && (xmin>=rc.left+BORDER_X) && (xmin<=rc.right)) {
      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, xval*unit_step/tic_step, unit_step);

//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin-tsize.cx/2, ymax-tsize.cy ,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
	SetBkMode(hdc, TRANSPARENT);
      }
    }

  }

  for (xval=zero-tic_step; xval>= x_min; xval-= tic_step) {

    xmin = (int)((xval-x_min)*xscale)+rc.left+BORDER_X;
    ymin = rc.top;
    xmax = xmin;
    ymax = rc.bottom;
    line[0].x = xmin;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax-BORDER_Y;

    // STYLE_THINDASHPAPER

    if ((xval> x_min) 
        && (xmin>=rc.left+BORDER_X) && (xmin<=rc.right)) {

      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, xval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin-tsize.cx/2, ymax-tsize.cy,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
	SetBkMode(hdc, TRANSPARENT);
      }
    }

  }

}



void Statistics::DrawYGrid(HDC hdc, const RECT rc, 
			   const double tic_step, 
			   const double zero,
                           const int Style, 
			   const double unit_step, bool draw_units) {

  POINT line[2];
  SIZE tsize;
  double yval;

  if(INVERTCOLORS)
    SelectObject(hdc, GetStockObject(BLACK_PEN));


  int xmin, ymin, xmax, ymax;

  if (!tic_step) return;

  for (yval=zero; yval<= y_max; yval+= tic_step) {

    xmin = rc.left;
    ymin = (int)((y_max-yval)*yscale)+rc.top -BORDER_Y;
    xmax = rc.right;
    ymax = ymin;
    line[0].x = xmin+BORDER_X;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax;

    // STYLE_THINDASHPAPER
    if ((yval< y_max) && 
        (ymin>=rc.top) && (ymin<=rc.bottom-BORDER_Y)) {

      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, yval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin, ymin-tsize.cy/2,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
//	SetBkMode(hdc, TRANSPARENT);
      }
    }
  }

  for (yval=zero-tic_step; yval>= y_min; yval-= tic_step) {

    xmin = rc.left;
    ymin = (int)((y_max-yval)*yscale)+rc.top-BORDER_Y;
    xmax = rc.right;
    ymax = ymin;
    line[0].x = xmin+BORDER_X;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax;

    // STYLE_THINDASHPAPER
    if ((yval> y_min) &&
        (ymin>=rc.top) && (ymin<=rc.bottom-BORDER_Y)) {

      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, yval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin, ymin-tsize.cy/2,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
//	SetBkMode(hdc, TRANSPARENT);
      }
    }
  }
}



void Statistics::DrawYGrid_cor(HDC hdc, const RECT rc,
			   const double tic_step,
			   const double zero,
                           const int Style,
			   const double unit_step, bool draw_units) {

  POINT line[2];
  SIZE tsize;
  double yval;

  if(INVERTCOLORS)
    SelectObject(hdc, GetStockObject(BLACK_PEN));


  int xmin, ymin, xmax, ymax;

  if (!tic_step) return;

  for (yval=zero; yval<= y_max; yval+= tic_step) {

    xmin = rc.left;
    ymin = (int)((y_max-yval)*yscale)+rc.top ;
    ymin = (int)((-yval)*yscale)+rc.top -BORDER_Y;
    xmax = rc.right;
    ymax = ymin;
    line[0].x = xmin+BORDER_X;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax;

    // STYLE_THINDASHPAPER
    if ((yval< y_max) &&
        (ymin>=rc.top) && (ymin<=rc.bottom)) {

      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, yval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin, ymin-tsize.cy/2,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
//	SetBkMode(hdc, TRANSPARENT);
      }
    }
  }

  for (yval=zero-tic_step; yval>= y_min; yval-= tic_step) {

    xmin = rc.left;
    ymin = (int)((y_max-yval)*yscale)+rc.top;
    xmax = rc.right;
    ymax = ymin;
    line[0].x = xmin+BORDER_X;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax;

    // STYLE_THINDASHPAPER
    if ((yval> y_min) &&
        (ymin>=rc.top) && (ymin<=rc.bottom)) {

      StyleLine(hdc, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, yval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	GetTextExtentPoint(hdc, unit_text, _tcslen(unit_text), &tsize);
	ExtTextOut(hdc, xmin, ymin-tsize.cy/2,
		   ETO_OPAQUE, NULL, unit_text, _tcslen(unit_text), NULL);
//	SetBkMode(hdc, TRANSPARENT);
      }
    }
  }
}

