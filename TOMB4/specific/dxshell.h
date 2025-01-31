#pragma once
#include "../global/types.h"

void DXBitMask2ShiftCnt(ulong mask, uchar* shift, uchar* count);
#ifdef USE_SDL
const Uint8 *SDLReadKeyboard(const Uint8* KeyMap);
#else
void DXReadKeyboard(char* KeyMap);
#endif
#ifdef ENABLE_MINIMUM_DX_FUNCTIONS
long DXAttempt(HRESULT r);
#endif
void* AddStruct(void* p, long num, long size);
#ifndef USE_BGFX
long DXDDCreate(LPGUID pGuid, void** pDD4);
long DXD3DCreate(LPDIRECTDRAWX pDD4, void** pD3D);
long DXSetCooperativeLevel(LPDIRECTDRAWX pDD4, HWND hwnd, long flags);

#ifdef UNICODE
BOOL __stdcall DXEnumDirectDraw(GUID FAR* lpGUID, LPWSTR lpDriverDescription, LPWSTR lpDriverName, LPVOID lpContext);
#else
BOOL __stdcall DXEnumDirectDraw(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);
#endif

#endif

#if !defined(MA_AUDIO_SAMPLES) || !defined(MA_AUDIO_ENGINE)
#ifdef UNICODE
BOOL __stdcall DXEnumDirectSound(LPGUID lpGuid, LPCWSTR lpcstrDescription, LPCWSTR lpcstrModule, LPVOID lpContext);
#else
BOOL __stdcall DXEnumDirectSound(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
#endif
#endif

long DXGetInfo(DXINFO* dxinfo, HWND hwnd);
void DXFreeInfo(DXINFO* dxinfo);
#ifndef USE_BGFX
HRESULT __stdcall DXEnumDisplayModes(LPDDSURFACEDESCX lpDDSurfaceDesc2, LPVOID lpContext);
#endif
long BPPToDDBD(long BPP);
#ifndef USE_BGFX
HRESULT __stdcall DXEnumTextureFormats(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
HRESULT __stdcall DXEnumZBufferFormats(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
long DXCreateSurface(LPDIRECTDRAWX dd, LPDDSURFACEDESCX desc, LPDIRECTDRAWSURFACEX* surf);
long DXSetVideoMode(LPDIRECTDRAWX dd, long dwWidth, long dwHeight, long dwBPP);
long DXCreateD3DDevice(LPDIRECT3DX d3d, GUID guid, LPDIRECTDRAWSURFACEX surf, LPDIRECT3DDEVICEX* device);
long DXCreateViewport(LPDIRECT3DX d3d, LPDIRECT3DDEVICEX device, long w, long h, LPDIRECT3DVIEWPORTX* viewport);
#endif
HRESULT DXShowFrame();
#ifndef USE_BGFX
void DXMove(long x, long y);
#if 0
void DXSaveScreen(LPDIRECTDRAWSURFACEX surf, const char* name);
#endif
void DXClose();
#endif
long DXCreate(long w, long h, long bpp, long Flags, DXPTR* dxptr, HWND hWnd, long WindowStyle);
#ifndef USE_BGFX
long DXChangeVideoMode();
long DXToggleFullScreen();
HRESULT __stdcall DXEnumDirect3D(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext);
#endif

#ifdef ENABLE_MINIMUM_DX_FUNCTIONS
const char* DXGetErrorString(HRESULT hr);
#endif

void DXInitKeyboard(HWND hwnd, HINSTANCE hinstance);

extern DXPTR* G_dxptr;
extern DXINFO* G_dxinfo;
#ifndef USE_BGFX
extern LPDIRECTDRAWX G_ddraw;
extern LPDIRECT3DX G_d3d;
extern HWND G_hwnd;
#endif

extern int keymap_count;
#ifdef USE_SDL
extern const Uint8 *keymap;
extern SDL_GameController *controller;
extern const char* controller_name;
extern SDL_GameControllerType controller_type;
#else
extern char keymap[256];
#endif