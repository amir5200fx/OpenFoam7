#pragma once
#ifndef _AtmosphericModels_Module_Header
#define _AtmosphericModels_Module_Header

#ifdef FoamAtmosphericModels_STATIC_DEFINE
#define FoamAtmosphericModels_EXPORT
#else
#ifdef FoamAtmosphericModels_EXPORT_DEFINE
#define FoamAtmosphericModels_EXPORT __declspec(dllexport)
#else
#define FoamAtmosphericModels_EXPORT __declspec(dllimport)
#endif // FoamAtmosphericModels_EXPORT_DEFINE
#endif // FoamAtmosphericModels_STATIC_DEFINE

#ifdef FoamAtmosphericModels_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#include <FvOptions_Module.hxx>
#endif// FoamAtmosphericModels_EXPORT_DEFINE

#endif // !_AtmosphericModels_Module_Header
