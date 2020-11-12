#pragma once
#ifndef _FvMesh_Module_Header
#define _FvMesh_Module_Header

#ifdef FoamFvMesh_STATIC_DEFINE
#define FoamFvMesh_EXPORT
#else
#ifdef FoamFvMesh_EXPORT_DEFINE
#define FoamFvMesh_EXPORT __declspec(dllexport)
#else
#define FoamFvMesh_EXPORT __declspec(dllimport)
#endif // FoamFvMesh_EXPORT_DEFINE
#endif // FoamFvMesh_STATIC_DEFINE

#ifdef FoamFvMesh_EXPORT_DEFINE
#include <Base_Module.hxx>
#endif // FoamFvMesh_EXPORT_DEFINE

#endif // !_FvMesh_Module_Header
