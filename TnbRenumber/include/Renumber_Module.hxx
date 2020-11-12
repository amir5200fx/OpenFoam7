#pragma once
#ifndef _Renumber_Module_Header
#define _Renumber_Module_Header

#ifdef FoamRenumber_STATIC_DEFINE
#define FoamRenumber_EXPORT
#else
#ifdef FoamRenumber_EXPORT_DEFINE
#define FoamRenumber_EXPORT __declspec(dllexport)
#else
#define FoamRenumber_EXPORT __declspec(dllimport)
#endif // FoamRenumber_EXPORT_DEFINE
#endif // FoamRenumber_STATIC_DEFINE

#ifdef FoamRenumber_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <Lagrangian_Module.hxx>
#include <Parallel_Module.hxx>
#endif // FoamRenumber_EXPORT_DEFINE

#endif // !_Renumber_Module_Header