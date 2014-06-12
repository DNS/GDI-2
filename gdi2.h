
/*

Author     : Daniel Sirait
Copyright  : Copyright (c) 2014 Daniel Sirait
License    : Public Domain
Disclaimer : I CAN UNDER NO CIRCUMSTANCES BE HELD RESPONSIBLE FOR
             ANY CONSEQUENCES OF YOUR USE/MISUSE OF THIS DOCUMENT,
             WHATEVER THAT MAY BE (GET BUSTED, WORLD WAR, ETC..).

*/

#ifndef GDI2_H
#define GDI2_H

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <wchar.h>
//#include <.h>
//#include "misc.h"


/************************
 *** Fake <gdiplus.h> ***
 ************************/

/* Microsoft (and their SDK) does not support using GDI+ from C and C++ is
 * required. Their headers simply are incompatible with C. We load GDIPLUS.DLL
 * with LoadLibrary() so the C++ wrapper sugary in their headers cannot be
 * used. Hence we do not include any GDI+ related header and instead use our
 * own types.
 *
 * Note we declare only types and constants we need to use in mCtrl.
 */

typedef void* gdi2_Graphics;
typedef void* gdi2_SolidFill;
typedef void* gdi2_Brush;
typedef void* gdi2_Pen;
typedef void* gdi2_Font;
typedef void* gdi2_StringFormat;
typedef void* gdi2_Path;
typedef void* gdi2_Image;
typedef void* gdi2_ImageAttributes;
typedef gdi2_Image gdi2_Bitmap;

typedef float gdi2_Real;
typedef DWORD gdi2_ARGB;

typedef enum gdi2_Status_tag gdi2_Status;
enum gdi2_Status_tag {
    gdi2_Ok = 0
};

typedef struct gdi2_PointF_tag gdi2_PointF;
struct gdi2_PointF_tag {
    gdi2_Real x;
    gdi2_Real y;
};

typedef struct gdi2_RectF_tag gdi2_RectF;
struct gdi2_RectF_tag {
    gdi2_Real x;
    gdi2_Real y;
    gdi2_Real w;
    gdi2_Real h;
};

typedef enum gdi2_MatrixOrder_tag gdi2_MatrixOrder;
enum gdi2_MatrixOrder_tag {
    gdi2_MatrixOrderPrepend = 0,
    gdi2_MatrixOrderAppend = 1
};

typedef enum gdi2_Unit_tag gdi2_Unit;
enum gdi2_Unit_tag {
    gdi2_UnitWorld = 0
};

typedef enum gdi2_SmoothingMode_tag gdi2_SmoothingMode;
enum gdi2_SmoothingMode_tag {
    gdi2_SmoothingModeHighQuality = 2
};

typedef enum gdi2_StringAlignment_tag gdi2_StringAlignment;
enum gdi2_StringAlignment_tag {
    gdi2_StringAlignmentCenter = 1,
    gdi2_StringAlignmentFar = 2
};

typedef enum gdi2_FillMode_tag gdi2_FillMode;
enum gdi2_FillMode_tag  {
    gdi2_FillModeAlternate = 0
} ;

#define gdi2_StringFormatFlagsNoWrap   0x00001000
#define gdi2_StringFormatFlagsNoClip   0x00004000


/**********************************
 *** Pointers to GDI+ functions ***
 **********************************/

/* Graphics management */
extern gdi2_Status (WINAPI* gdi2_CreateFromHDC)(HDC,gdi2_Graphics**);
extern gdi2_Status (WINAPI* gdi2_DeleteGraphics)(gdi2_Graphics*);
extern gdi2_Status (WINAPI* gdi2_SetSmoothingMode)(gdi2_Graphics*,gdi2_SmoothingMode);
extern gdi2_Status (WINAPI* gdi2_TranslateWorldTransform)(gdi2_Graphics*,gdi2_Real,gdi2_Real,gdi2_MatrixOrder);
extern gdi2_Status (WINAPI* gdi2_RotateWorldTransform)(gdi2_Graphics*,gdi2_Real,gdi2_MatrixOrder);
extern gdi2_Status (WINAPI* gdi2_ResetWorldTransform)(gdi2_Graphics*);

/* Pen management */
extern gdi2_Status (WINAPI* gdi2_CreatePen1)(gdi2_ARGB,gdi2_Real,gdi2_Unit,gdi2_Pen**);
extern gdi2_Status (WINAPI* gdi2_DeletePen)(gdi2_Pen*);
extern gdi2_Status (WINAPI* gdi2_SetPenWidth)(gdi2_Pen*,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_SetPenColor)(gdi2_Pen*,gdi2_ARGB);

/* Brush management */
extern gdi2_Status (WINAPI* gdi2_CreateSolidFill)(gdi2_ARGB,gdi2_SolidFill**);
extern gdi2_Status (WINAPI* gdi2_DeleteBrush)(gdi2_Brush*);
extern gdi2_Status (WINAPI* gdi2_SetSolidFillColor)(gdi2_SolidFill*,gdi2_ARGB);

/* Font management */
extern gdi2_Status (WINAPI* gdi2_CreateFontFromDC)(HDC,gdi2_Font**);
extern gdi2_Status (WINAPI* gdi2_CreateFontFromLogfontW)(HDC,const LOGFONTW*,gdi2_Font**);
extern gdi2_Status (WINAPI* gdi2_DeleteFont)(gdi2_Font*);

/* String format management */
extern gdi2_Status (WINAPI* gdi2_CreateStringFormat)(INT,LANGID,gdi2_StringFormat**);
extern gdi2_Status (WINAPI* gdi2_DeleteStringFormat)(gdi2_StringFormat*);
extern gdi2_Status (WINAPI* gdi2_SetStringFormatFlags)(gdi2_StringFormat*,INT);
extern gdi2_Status (WINAPI* gdi2_SetStringFormatAlign)(gdi2_StringFormat*,gdi2_StringAlignment);

/* Path management */
extern gdi2_Status (WINAPI* gdi2_CreatePath)(gdi2_FillMode,gdi2_Path**);
extern gdi2_Status (WINAPI* gdi2_DeletePath)(gdi2_Path*);
extern gdi2_Status (WINAPI* gdi2_ResetPath)(gdi2_Path*);
extern gdi2_Status (WINAPI* gdi2_AddPathArc)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_AddPathLine)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_AddPathRectangle)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);

/* Image methods */
extern gdi2_Status (WINAPI* gdi2_LoadImageFromFile)(const WCHAR*,gdi2_Image**);
extern gdi2_Status (WINAPI* gdi2_LoadImageFromStream)(IStream*,gdi2_Image**);
extern gdi2_Status (WINAPI* gdi2_DisposeImage)(gdi2_Image*);
extern gdi2_Status (WINAPI* gdi2_GetImageBounds)(gdi2_Image*,gdi2_RectF*,gdi2_Unit*);

/* Draw methods */
extern gdi2_Status (WINAPI* gdi2_DrawLine)(gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_DrawLines)(gdi2_Graphics*,gdi2_Pen*,const gdi2_PointF*,INT);
extern gdi2_Status (WINAPI* gdi2_DrawPie)(gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_DrawImageRectRect)(gdi2_Graphics*,gdi2_Image*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Unit,const gdi2_ImageAttributes*,void*,void*);

/* Fill methods */
extern gdi2_Status (WINAPI* gdi2_FillRectangle)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_FillPolygon)(gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT,gdi2_FillMode);
extern gdi2_Status (WINAPI* gdi2_FillPolygon2)(gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT);
extern gdi2_Status (WINAPI* gdi2_FillEllipse)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_FillPie)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
extern gdi2_Status (WINAPI* gdi2_FillPath)(gdi2_Graphics*,gdi2_Brush*,gdi2_Path*);

/* String methods */
extern gdi2_Status (WINAPI* gdi2_DrawString)(gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,const gdi2_Brush*);
extern gdi2_Status (WINAPI* gdi2_MeasureString)(gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,gdi2_RectF*,INT*,INT*);


/*************************
 *** Wrapper functions ***
 *************************/

/* Safer function for getting a reasonable font. GDI+ supports only true-type
 * fonts and this does a reasonable fallback. */
gdi2_Status gdi2_CreateFontFromHFONT(HDC dc, HFONT font, gdi2_Font** gdi2_font);


/**********************
 *** ARGB functions ***
 **********************/

static gdi2_ARGB
gdi2_ARGB_from_argb(BYTE a, BYTE r, BYTE g, BYTE b)
{
    return ((((DWORD) a) << 24) | (((DWORD) r) << 16) |
            (((DWORD) g) <<  8) | (((DWORD) b) <<  0));
}

static gdi2_ARGB
gdi2_ARGB_from_rgb(BYTE r, BYTE g, BYTE b)
{
    return gdi2_ARGB_from_argb(0xff, r, g, b);
}

static gdi2_ARGB
gdi2_ARGB_from_cr(COLORREF cr)
{
    return gdi2_ARGB_from_argb(0xff, GetRValue(cr), GetGValue(cr), GetBValue(cr));
}

static gdi2_ARGB
gdi2_ARGB_from_acr(BYTE a, COLORREF cr)
{
    return gdi2_ARGB_from_argb(a, GetRValue(cr), GetGValue(cr), GetBValue(cr));
}


#endif  /* GDI2_H */
