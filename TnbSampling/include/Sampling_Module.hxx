#pragma once
#ifndef _Sampling_Module_Header
#define _Sampling_Module_Header

#ifdef FoamSampling_STATIC_DEFINE
#define FoamSampling_EXPORT
#else
#ifdef FoamSampling_EXPORT_DEFINE
#define FoamSampling_EXPORT __declspec(dllexport)
#else
#define FoamSampling_EXPORT __declspec(dllimport)
#endif // FoamSampling_EXPORT_DEFINE
#endif // FoamSampling_STATIC_DEFINE

#ifdef FoamSampling_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <Conversion_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#endif // FoamSampling_EXPORT_DEFINE

#endif // !_Sampling_Module_Header