#pragma once
#ifndef _Conversion_Module_Header
#define _Conversion_Module_Header

#include <FiniteVolume_Module.hxx>

#ifdef FoamConversion_STATIC_DEFINE
#define FoamConversion_EXPORT
#else
#ifdef FoamConversion_EXPORT_DEFINE
#define FoamConversion_EXPORT __declspec(dllexport)
#else
#define FoamConversion_EXPORT __declspec(dllimport)
#endif // FoamConversion_EXPORT_DEFINE

#endif // FoamConversion_STATIC_DEFINE

#endif // !_Conversion_Module_Header