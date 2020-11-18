#pragma once
#ifndef _FunctionObjects_Module_Header
#define _FunctionObjects_Module_Header

#ifdef FoamFunctionObjects_STATIC_DEFINE
#define FoamFunctionObjects_EXPORT
#else
#ifdef FoamFunctionObjects_EXPORT_DEFINE
#define FoamFunctionObjects_EXPORT __declspec(dllexport)
#else
#define FoamFunctionObjects_EXPORT __declspec(dllimport)
#endif // FoamFunctionObjects_EXPORT_DEFINE
#endif // FoamFunctionObjects_STATIC_DEFINE

#ifdef FoamFunctionObjects_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <Conversion_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#include <Sampling_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#endif // FoamFunctionObjects_EXPORT

#endif // !_FunctionObjects_Module_Header