#pragma once
#ifndef _FiniteVolume_Module_Header
#define _FiniteVolume_Module_Header

#include <Base_Module.hxx>
#include <FvMesh_Module.hxx>

#ifdef FoamFiniteVolume_STATIC_DEFINE
#define FoamFiniteVolume_EXPORT
#else
#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFiniteVolume_EXPORT __declspec(dllexport)
#else
#define FoamFiniteVolume_EXPORT __declspec(dllimport)
#endif // FoamFiniteVolume_EXPORT_DEFINE

#endif // FoamFiniteVolume_STATIC_DEFINE

#ifdef FoamFiniteVolume_Template_EXPORT_DEFINE
#define Foam_EXPORT FoamFiniteVolume_EXPORT
#else
#define Foam_EXPORT 
#endif // Foam_EXPORT_DEFINE

#endif !_FiniteVolume_Module_Header