#pragma once
#ifndef _RandomProcesses_Module_Header
#define _RandomProcesses_Module_Header

#ifdef FoamRandomProcesses_STATIC_DEFINE
#define FoamRandomProcesses_EXPORT
#else
#ifdef FoamRandomProcesses_EXPORT_DEFINE
#define FoamRandomProcesses_EXPORT __declspec(dllexport)
#else
#define FoamRandomProcesses_EXPORT __declspec(dllimport)
#endif // FoamRandomProcesses_EXPORT_DEFINE
#endif // FoamRandomProcesses_STATIC_DEFINE

#ifdef FoamRandomProcesses_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#endif // FoamRandomProcesses_EXPORT_DEFINE

#endif // !_RandomProcesses_Module_Header
