#pragma once
#ifndef _DynamicMesh_Module_Header
#define _DynamicMesh_Module_Header

#ifdef FoamDynamicMesh_STATIC_DEFINE
#define FoamDynamicMesh_EXPORT
#else
#ifdef FoamDynamicMesh_EXPORT_DEFINE
#define FoamDynamicMesh_EXPORT __declspec(dllexport)
#else
#define FoamDynamicMesh_EXPORT __declspec(dllimport)
#endif // FoamDynamicMesh_EXPORT_DEFINE
#endif // FoamDynamicMesh_STATIC_DEFINE

#ifdef FoamDynamicMesh_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#endif // FoamDynamicMesh_EXPORT_DEFINE

#endif !_DynamicMesh_Module_Header