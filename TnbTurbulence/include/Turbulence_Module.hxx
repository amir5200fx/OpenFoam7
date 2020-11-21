#pragma once
#ifndef _Turbulence_Module_Header
#define _Turbulence_Module_Header

#ifdef FoamTurbulence_STATIC_DEFINE
#define FoamTurbulence_EXPORT
#else
#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamTurbulence_EXPORT __declspec(dllexport)
#else
#define FoamTurbulence_EXPORT __declspec(dllimport)
#endif // FoamTurbulence_EXPORT_DEFINE
#endif // FoamTurbulence_STATIC_DEFINE

#ifdef FoamTurbulence_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#endif // FoamTurbulence_EXPORT_DEFINE

#endif // !_Turbulence_Module_Header