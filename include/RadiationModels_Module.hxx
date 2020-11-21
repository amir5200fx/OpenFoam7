#pragma once
#ifndef _RadiationModels_Module_Header
#define _RadiationModels_Module_Header

#ifdef FoamRadiationModels_STATIC_DEFINE
#define FoamRadiationModels_EXPORT
#else
#ifdef FoamRadiationModels_EXPORT_DEFINE
#define FoamRadiationModels_EXPORT __declspec(dllexport)
#else
#define FoamRadiationModels_EXPORT __declspec(dllimport)
#endif // FoamRadiationModels_EXPORT_DEFINE
#endif // FoamRadiationModels_STATIC_DEFINE

#ifdef FoamRadiationModels_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#endif // FoamRadiationModels_EXPORT_DEFINE

#endif // !_RadiationModels_Module_Header