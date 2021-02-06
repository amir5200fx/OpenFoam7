#pragma once
#ifndef _CombustionModels_Module_Header
#define _CombustionModels_Module_Header

#ifdef FoamCombustionModels_STATIC_DEFINE
#define FoamCombustionModels_EXPORT
#else
#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamCombustionModels_EXPORT __declspec(dllexport)
#else
#define FoamCombustionModels_EXPORT __declspec(dllimport)
#endif // FoamCombustionModels_EXPORT_DEFINE
#endif // FoamCombustionModels_STATIC_DEFINE

#ifdef FoamCombustionModels_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Turbulence_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <RadiationModels_Module.hxx>
#endif// FoamCombustionModels_EXPORT_DEFINE

#endif // !_CombustionModels_Module_Header
