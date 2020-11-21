#pragma once
#ifndef _ThermophysicalModels_Module_Header
#define _ThermophysicalModels_Module_Header

#ifdef FoamThermophysicalModels_STATIC_DEFINE
#define FoamThermophysicalModels_EXPORT
#else
#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamThermophysicalModels_EXPORT __declspec(dllexport)
#else
#define FoamThermophysicalModels_EXPORT __declspec(dllimport)
#endif // FoamThermophysicalModels_EXPORT_DEFINE
#endif // FoamThermophysicalModels_STATIC_DEFINE

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ODE_Module.hxx>
#include <TransportModels_Module.hxx>
#endif // FoamThermophysicalModels_EXPORT_DEFINE

#endif // !_ThermophysicalModels_Module_Header