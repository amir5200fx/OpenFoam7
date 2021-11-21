#pragma once
#ifndef _Engine_Module_Header
#define _Engine_Module_Header

#ifdef FoamEngine_STATIC_DEFINE
#define FoamEngine_EXPORT
#else
#ifdef FoamEngine_EXPORT_DEFINE
#define FoamEngine_EXPORT __declspec(dllexport)
#else
#define FoamEngine_EXPORT __declspec(dllimport)
#endif // FoamEngine_EXPORT_DEFINE
#endif // FoamEngine_STATIC_DEFINE

#ifdef FoamEngine_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FvMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FvMotionSolver_Module.hxx>
#endif // FoamEngine_EXPORT_DEFINE

#endif // !_Engine_Module_Header
