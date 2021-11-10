#pragma once
#ifndef _FoamyMesh_Module_Header
#define _FoamyMesh_Module_Header

#ifdef FoamFoamyMesh_STATIC_DEFINE
#define FoamFoamyMesh_EXPORT
#else
#ifdef FoamFoamyMesh_EXPORT_DEFINE
#define FoamFoamyMesh_EXPORT __declspec(dllexport)
#else
#define FoamFoamyMesh_EXPORT __declspec(dllimport)
#endif // FoamFoamyMesh_EXPORT_DEFINE
#endif // FoamFoamyMesh_STATIC_DEFINE

#ifdef FoamFoamyMesh_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#endif // FoamFoamyMesh_EXPORT_DEFINE

#endif // !_FoamyMesh_Module_Header
