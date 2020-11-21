#pragma once
#ifndef _Lagrangian_Module_Header
#define _Lagrangian_Module_Header

#ifdef FoamLagrangian_STATIC_DEFINE
#define FoamLagrangian_EXPORT
#else
#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamLagrangian_EXPORT __declspec(dllexport)
#else
#define FoamLagrangian_EXPORT __declspec(dllimport)
#endif // FoamLagrangian_EXPORT_DEFINE
#endif // FoamLagrangian_STATIC_DEFINE

#ifdef FoamLagrangian_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <Conversion_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <RadiationModels_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#endif // FoamLagrangian_EXPORT_DEFINE

#endif // !_Lagrangian_Module_Header