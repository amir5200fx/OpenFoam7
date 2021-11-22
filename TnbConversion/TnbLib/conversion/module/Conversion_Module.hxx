#pragma once
#ifndef _Conversion_Module_Header
#define _Conversion_Module_Header

#ifdef FoamConversion_STATIC_DEFINE
#define FoamConversion_EXPORT
#else
#ifdef FoamConversion_EXPORT_DEFINE
#define FoamConversion_EXPORT __declspec(dllexport)
#else
#define FoamConversion_EXPORT __declspec(dllimport)
#endif // FoamConversion_EXPORT_DEFINE
#endif // FoamConversion_STATIC_DEFINE

#ifdef FoamConversion_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#endif// FoamConversion_EXPORT_DEFINE

#endif // !_Conversion_Module_Header