#pragma once
#ifndef _Parallel_Module_Header
#define _Parallel_Module_Header

#ifdef FoamParallel_STATIC_DEFINE
#define FoamParallel_EXPORT
#else
#ifdef FoamParallel_EXPORT_DEFINE
#define FoamParallel_EXPORT __declspec(dllexport)
#else
#define FoamParallel_EXPORT __declspec(dllimport)
#endif // FoamParallel_EXPORT_DEFINE
#endif // FoamParallel_STATIC_DEFINE

#ifdef FoamParallel_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#endif // FoamParallel_EXPORT_DEFINE

#endif // !_Parallel_Module_Header