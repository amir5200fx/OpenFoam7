#pragma once
#ifndef _reactingEulerFoamLibs_Module_Header
#define _reactingEulerFoamLibs_Module_Header

#ifdef FoamReactingEulerFoamLibs_STATIC_DEFINE
#define FoamReactingEulerFoamLibs_EXPORT
#else
#ifdef FoamReactingEulerFoamLibs_EXPORT_DEFINE
#define FoamReactingEulerFoamLibs_EXPORT __declspec(dllexport)
#else
#define FoamReactingEulerFoamLibs_EXPORT __declspec(dllimport)
#endif // FoamReactingEulerFoamLibs_EXPORT_DEFINE
#endif // FoamReactingEulerFoamLibs_STATIC_DEFINE

#ifdef FoamReactingEulerFoamLibs_EXPORT_DEFINE

#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#include <DynamicMesh_Module.hxx>

#endif // FoamReactingEulerFoamLibs_EXPORT_DEFINE
#endif // !_reactingEulerFoamLibs_Module_Header
