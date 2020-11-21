#pragma once
#ifndef _SnappyHexMesh_Module_Header
#define _SnappyHexMesh_Module_Header

#ifdef FoamSnappyHexMesh_STATIC_DEFINE
#define FoamSnappyHexMesh_EXPORT
#else
#ifdef FoamSnappyHexMesh_EXPORT_DEFINE
#define FoamSnappyHexMesh_EXPORT __declspec(dllexport)
#else
#define FoamSnappyHexMesh_EXPORT __declspec(dllimport)
#endif // FoamSnappyHexMesh_EXPORT_DEFINE
#endif // FoamSnappyHexMesh_STATIC_DEFINE

#ifdef FoamSnappyHexMesh_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#include <Parallel_Module.hxx>
#endif // FoamSnappyHexMesh_EXPORT_DEFINE

#endif // !_SnappyHexMesh_Module_Header