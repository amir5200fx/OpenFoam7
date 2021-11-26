#pragma once
#ifndef _compressibleInterFoamLibs_Module_Header
#define _compressibleInterFoamLibs_Module_Header

#ifdef FoamCompressibleInterFoamLibs_STATIC_DEFINE
#define FoamCompressibleInterFoamLibs_EXPORT
#else
#ifdef FoamCompressibleInterFoamLibs_EXPORT_DEFINE
#define FoamCompressibleInterFoamLibs_EXPORT __declspec(dllexport)
#else
#define FoamCompressibleInterFoamLibs_EXPORT __declspec(dllimport)
#endif // FoamCompressibleInterFoamLibs_EXPORT_DEFINE
#endif // FoamCompressibleInterFoamLibs_STATIC_DEFINE

#ifdef FoamCompressibleInterFoamLibs_EXPORT_DEFINE
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
#include <FvOptions_Module.hxx>
#endif // FoamCompressibleInterFoamLibs_EXPORT_DEFINE

#endif // !_compressibleInterFoamLibs_Module_Header
