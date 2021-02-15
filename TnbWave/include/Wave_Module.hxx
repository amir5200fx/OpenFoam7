#pragma once
#ifndef _Wave_Module_Header
#define _Wave_Module_Header

#ifdef FoamWave_STATIC_DEFINE
#define FoamWave_EXPORT
#else
#ifdef FoamWave_EXPORT_DEFINE
#define FoamWave_EXPORT __declspec(dllexport)
#else
#define FoamWave_EXPORT __declspec(dllimport)
#endif // FoamWave_EXPORT_DEFINE
#endif // FoamWave_STATIC_DEFINE

#ifdef FoamWave_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <DynamicMesh_Module.hxx>
#endif// FoamWave_EXPORT_DEFINE

#endif // !_Wave_Module_Header
