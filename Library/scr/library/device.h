#include "lib_head.h"

#ifndef _DEVICE_H_
#define _DEVICE_H_

//	インプットデバイスの取得
LPDIRECTINPUT8	GetInputDevice();

//	キーデバイスの取得
LPDIRECTINPUTDEVICE8	GetKeyDevice();

//	マウスデバイスの取得
LPDIRECTINPUTDEVICE8	GetMouseDevice();
#endif

