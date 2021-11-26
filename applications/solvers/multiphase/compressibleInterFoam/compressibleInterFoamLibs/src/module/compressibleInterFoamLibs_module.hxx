#pragma once
#ifndef _compressibleInterFoamLibs_module_Header
#define _compressibleInterFoamLibs_module_Header

#ifdef CompressibleInterFoamLibs_STATIC_DEFINE
#define CompressibleInterFoamLibs_EXPORT
#else
#ifdef CompressibleInterFoamLibs_EXPORT_DEFINE
#define CompressibleInterFoamLibs_EXPORT __declspec(dllexport)
#else
#define CompressibleInterFoamLibs_EXPORT __declspec(dllimport)
#endif // CompressibleInterFoamLibs_EXPORT
#endif // CompressibleInterFoamLibs_STATIC_DEFINE

#ifdef CompressibleInterFoamLibs_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FvMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FvOptions_Module.hxx>
#include <TransportModels_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <Turbulence_Module.hxx>
#include <Lagrangian_Module.hxx>

#endif // CompressibleInterFoamLibs_EXPORT_DEFINE


#endif // !_compressibleInterFoamLibs_module_Header
