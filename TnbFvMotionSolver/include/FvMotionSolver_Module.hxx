#pragma once
#ifndef _FvMotionSolver_Module_Header
#define _FvMotionSolver_Module_Header

#ifdef FoamFvMotionSolver_STATIC_DEFINE
#define FoamFvMotionSolver_EXPORT
#else
#ifdef FoamFvMotionSolver_EXPORT_DEFINE
#define FoamFvMotionSolver_EXPORT __declspec(dllexport)
#else
#define FoamFvMotionSolver_EXPORT __declspec(dllimport)
#endif // FoamFvMotionSolver_EXPORT_DEFINE
#endif // FoamFvMotionSolver_STATIC_DEFINE

#ifdef FoamFvMotionSolver_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#endif // FoamFvMotionSolver_EXPORT_DEFINE

#endif // !_FvMotionSolver_Module_Header