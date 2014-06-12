/*

Author     : Daniel Sirait
Copyright  : Copyright (c) 2014 Daniel Sirait
License    : Public Domain
Disclaimer : I CAN UNDER NO CIRCUMSTANCES BE HELD RESPONSIBLE FOR
             ANY CONSEQUENCES OF YOUR USE/MISUSE OF THIS PROGRAM,
             WHATEVER THAT MAY BE (GET BUSTED, WORLD WAR, ETC..).

*/

#include "gdi2.h"

/* Uncomment this to have more verbose traces from this module. */
/*#define GDI2_DEBUG     1*/

#ifdef GDI2_DEBUG
    #define GDI2_TRACE         MC_TRACE
#else
    #define GDI2_TRACE(...)    do {} while(0)
#endif


/* Graphics management */
gdi2_Status (WINAPI* gdi2_CreateFromHDC)(HDC,gdi2_Graphics**);
gdi2_Status (WINAPI* gdi2_DeleteGraphics)(gdi2_Graphics*);
gdi2_Status (WINAPI* gdi2_SetSmoothingMode)(gdi2_Graphics*,gdi2_SmoothingMode);
gdi2_Status (WINAPI* gdi2_TranslateWorldTransform)(gdi2_Graphics*,gdi2_Real,gdi2_Real,gdi2_MatrixOrder);
gdi2_Status (WINAPI* gdi2_RotateWorldTransform)(gdi2_Graphics*,gdi2_Real,gdi2_MatrixOrder);
gdi2_Status (WINAPI* gdi2_ResetWorldTransform)(gdi2_Graphics*);

/* Pen management */
gdi2_Status (WINAPI* gdi2_CreatePen1)(gdi2_ARGB,gdi2_Real,gdi2_Unit,gdi2_Pen**);
gdi2_Status (WINAPI* gdi2_DeletePen)(gdi2_Pen*);
gdi2_Status (WINAPI* gdi2_SetPenWidth)(gdi2_Pen*,gdi2_Real);
gdi2_Status (WINAPI* gdi2_SetPenColor)(gdi2_Pen*,gdi2_ARGB);

/* Brush management */
gdi2_Status (WINAPI* gdi2_CreateSolidFill)(gdi2_ARGB,gdi2_SolidFill**);
gdi2_Status (WINAPI* gdi2_DeleteBrush)(gdi2_Brush*);
gdi2_Status (WINAPI* gdi2_SetSolidFillColor)(gdi2_SolidFill*,gdi2_ARGB);

/* Font management */
gdi2_Status (WINAPI* gdi2_CreateFontFromDC)(HDC,gdi2_Font**);
gdi2_Status (WINAPI* gdi2_CreateFontFromLogfontW)(HDC,const LOGFONTW*,gdi2_Font**);
gdi2_Status (WINAPI* gdi2_DeleteFont)(gdi2_Font*);

/* String format management */
gdi2_Status (WINAPI* gdi2_CreateStringFormat)(INT,LANGID,gdi2_StringFormat**);
gdi2_Status (WINAPI* gdi2_DeleteStringFormat)(gdi2_StringFormat*);
gdi2_Status (WINAPI* gdi2_SetStringFormatFlags)(gdi2_StringFormat*,INT);
gdi2_Status (WINAPI* gdi2_SetStringFormatAlign)(gdi2_StringFormat*,gdi2_StringAlignment);

/* Path management */
gdi2_Status (WINAPI* gdi2_CreatePath)(gdi2_FillMode,gdi2_Path**);
gdi2_Status (WINAPI* gdi2_DeletePath)(gdi2_Path*);
gdi2_Status (WINAPI* gdi2_ResetPath)(gdi2_Path*);
gdi2_Status (WINAPI* gdi2_AddPathArc)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_AddPathLine)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_AddPathRectangle)(gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);

/* Image methods */
gdi2_Status (WINAPI* gdi2_LoadImageFromFile)(const WCHAR*,gdi2_Image**);
gdi2_Status (WINAPI* gdi2_LoadImageFromStream)(IStream*,gdi2_Image**);
gdi2_Status (WINAPI* gdi2_DisposeImage)(gdi2_Image*);
gdi2_Status (WINAPI* gdi2_GetImageBounds)(gdi2_Image*,gdi2_RectF*,gdi2_Unit*);

/* Draw methods */
gdi2_Status (WINAPI* gdi2_DrawLine)(gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_DrawLines)(gdi2_Graphics*,gdi2_Pen*,const gdi2_PointF*,INT);
gdi2_Status (WINAPI* gdi2_DrawPie)(gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_DrawImageRectRect)(gdi2_Graphics*,gdi2_Image*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Unit,const gdi2_ImageAttributes*,void*,void*);

/* Fill methods */
gdi2_Status (WINAPI* gdi2_FillRectangle)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_FillPolygon)(gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT,gdi2_FillMode);
gdi2_Status (WINAPI* gdi2_FillPolygon2)(gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT);
gdi2_Status (WINAPI* gdi2_FillEllipse)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_FillPie)(gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real);
gdi2_Status (WINAPI* gdi2_FillPath)(gdi2_Graphics*,gdi2_Brush*,gdi2_Path*);

/* String methods */
gdi2_Status (WINAPI* gdi2_DrawString)(gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,const gdi2_Brush*);
gdi2_Status (WINAPI* gdi2_MeasureString)(gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,gdi2_RectF*,INT*,INT*);



static HMODULE gdi2_dll;
static ULONG_PTR gdi2_token;
static void (WINAPI* gdi2_Shutdown)(ULONG_PTR);


typedef struct gdi2_StartupInput_tag gdi2_StartupInput;
struct gdi2_StartupInput_tag {
    UINT32 GdiplusVersion;
    void* DebugEventCallback;  /* DebugEventProc */
    BOOL SuppressBackgroundThread;
    BOOL SuppressExternalCodecs;
} GdiplusStartupInput;

typedef struct gdi2_StartupOutput_tag gdi2_StartupOutput;
/* We do not use gdi2_StartupOutput, so no definition */


gdi2_Status
gdi2_CreateFontFromHFONT(HDC dc, HFONT font, gdi2_Font** gdi2_font)
{
    LOGFONTW lf;
    gdi2_Status status;
    int retries;

    if(font == NULL)
        font = (HFONT) GetStockObject(SYSTEM_FONT);
    GetObjectW(font, sizeof(LOGFONTW), &lf);

    for(retries = 0; retries < 2; retries++) {
        status = gdi2_CreateFontFromLogfontW(dc, &lf, gdi2_font);
        if(status != gdi2_Ok) {
    //        /* Perhaps it is a font which does not have true-type outlines?
    //         * Fallback to a font which should have them. */
            wcscpy(lf.lfFaceName,
                   (NTDDI_VERSION >= NTDDI_LONGHORN  ? L"Segoe UI" : L"Tahoma"));
        } else {
            break;
        }
    }

    return status;
}

int
gdi2_init_module(void)
{
    gdi2_Status (WINAPI* gdi2_Startup)(ULONG_PTR*,const gdi2_StartupInput*,gdi2_StartupOutput*);
    gdi2_Status status;
    gdi2_StartupInput input = { 0 };

    gdi2_dll = LoadLibrary(TEXT("GDIPLUS.DLL"));
    if(gdi2_dll == NULL) {
        //MC_TRACE_ERR("gdi2_init_module: LoadLibrary(GDIPLUS.DLL) failed");
        goto err_LoadLibrary;
    }

    gdi2_Startup = (gdi2_Status (WINAPI*)(ULONG_PTR*,const gdi2_StartupInput*,gdi2_StartupOutput*))
                                                GetProcAddress(gdi2_dll, "GdiplusStartup");
    if(gdi2_Startup == NULL) {
        //MC_TRACE_ERR("gdi2_init_module: GetProcAddress(GdiplusStartup) failed");
        goto err_GetProcAddress;
    }

    gdi2_Shutdown = (void (WINAPI*)(ULONG_PTR)) GetProcAddress(gdi2_dll, "GdiplusShutdown");
    if(gdi2_Shutdown == NULL) {
        //MC_TRACE_ERR("gdi2_init_module: GetProcAddress(GdiplusShutdown) failed");
        goto err_GetProcAddress;
    }

#define GPA(name, params)                                                     \
        do {                                                                  \
            gdi2_##name = (gdi2_Status (WINAPI*)params)                       \
                        GetProcAddress(gdi2_dll, "Gdip" #name);               \
            if(gdi2_##name == NULL) {                                 \
                goto err_GetProcAddress;                                      \
            }                                                                 \
        } while(0)

    GPA(CreateFromHDC,        (HDC,gdi2_Graphics**));
    GPA(DeleteGraphics,       (gdi2_Graphics*));
    GPA(SetSmoothingMode,     (gdi2_Graphics*,gdi2_SmoothingMode));
    GPA(TranslateWorldTransform, (gdi2_Graphics*,gdi2_Real,gdi2_Real,gdi2_MatrixOrder));
    GPA(RotateWorldTransform, (gdi2_Graphics*,gdi2_Real,gdi2_MatrixOrder));
    GPA(ResetWorldTransform,  (gdi2_Graphics*));

    GPA(CreatePen1,           (gdi2_ARGB,gdi2_Real,gdi2_Unit,gdi2_Pen**));
    GPA(DeletePen,            (gdi2_Pen*));
    GPA(SetPenWidth,          (gdi2_Pen*,gdi2_Real));
    GPA(SetPenColor,          (gdi2_Pen*,gdi2_ARGB));

    GPA(CreateSolidFill,      (gdi2_ARGB,gdi2_SolidFill**));
    GPA(DeleteBrush,          (gdi2_Brush*));
    GPA(SetSolidFillColor,    (gdi2_SolidFill*,gdi2_ARGB));

    GPA(CreateFontFromDC,     (HDC,gdi2_Font**));
    GPA(CreateFontFromLogfontW, (HDC,const LOGFONTW*,gdi2_Font**));
    GPA(DeleteFont,           (gdi2_Font*));

    GPA(CreatePath,           (gdi2_FillMode,gdi2_Path**));
    GPA(DeletePath,           (gdi2_Path*));
    GPA(ResetPath,            (gdi2_Path*));
    GPA(AddPathArc,           (gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(AddPathLine,          (gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(AddPathRectangle,     (gdi2_Path*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));

    GPA(CreateStringFormat,   (INT,LANGID,gdi2_StringFormat**));
    GPA(DeleteStringFormat,   (gdi2_StringFormat*));
    GPA(SetStringFormatFlags, (gdi2_StringFormat*,INT));
    GPA(SetStringFormatAlign, (gdi2_StringFormat*,gdi2_StringAlignment));

    GPA(LoadImageFromFile,    (const WCHAR*,gdi2_Image**));
    GPA(LoadImageFromStream,  (IStream*,gdi2_Image**));
    GPA(DisposeImage,         (gdi2_Image*));
    GPA(GetImageBounds,       (gdi2_Image*,gdi2_RectF*,gdi2_Unit*));

    GPA(DrawLine,             (gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(DrawLines,            (gdi2_Graphics*,gdi2_Pen*,const gdi2_PointF*,INT));
    GPA(DrawPie,              (gdi2_Graphics*,gdi2_Pen*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(DrawImageRectRect,    (gdi2_Graphics*,gdi2_Image*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Unit,const gdi2_ImageAttributes*,void*,void*));

    GPA(FillRectangle,        (gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(FillPolygon,          (gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT,gdi2_FillMode));
    GPA(FillPolygon2,         (gdi2_Graphics*,gdi2_Brush*,const gdi2_PointF*,INT));
    GPA(FillEllipse,          (gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(FillPie,              (gdi2_Graphics*,gdi2_Brush*,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real,gdi2_Real));
    GPA(FillPath,             (gdi2_Graphics*,gdi2_Brush*,gdi2_Path*));

    GPA(DrawString,           (gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,const gdi2_Brush*));
    GPA(MeasureString,        (gdi2_Graphics*,const WCHAR*,INT,const gdi2_Font*,const gdi2_RectF*,const gdi2_StringFormat*,gdi2_RectF*,INT*,INT*));

#undef GPA

    input.GdiplusVersion = 1;
    input.SuppressExternalCodecs = TRUE;
    status = gdi2_Startup(&gdi2_token, &input, NULL);
    if(status != gdi2_Ok) {
        //MC_TRACE("GdiplusStartup() failed. [%d]", (int)status);
        goto err_Startup;
    }

    GDI2_TRACE("gdi2_init_module: Success.");
    return 0;

err_Startup:
err_GetProcAddress:
    FreeLibrary(gdi2_dll);
err_LoadLibrary:
    return -1;
}

void
gdi2_fini_module(void)
{
    gdi2_Shutdown(gdi2_token);
    FreeLibrary(gdi2_dll);
}
