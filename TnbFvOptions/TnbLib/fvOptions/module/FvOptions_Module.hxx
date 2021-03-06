#pragma once
#ifndef _FvOptions_Module_Header
#define _FvOptions_Module_Header

#ifdef FoamFvOptions_STATIC_DEFINE
#define FoamFvOptions_EXPORT
#else
#ifdef FoamFvOptions_EXPORT_DEFINE
#define FoamFvOptions_EXPORT __declspec(dllexport)
#else
#define FoamFvOptions_EXPORT __declspec(dllimport)
#endif // FoamFvOptions_EXPORT_DEFINE
#endif // FoamFvOptions_STATIC_DEFINE

#ifdef FoamFvOptions_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#include <Conversion_Module.hxx>
#include <Lagrangian_Module.hxx>
#include <RadiationModels_Module.hxx>
#include <Sampling_Module.hxx>
#endif // FoamFvOptions_EXPORT_DEFINE

#endif // !_FvOptions_Module_Header