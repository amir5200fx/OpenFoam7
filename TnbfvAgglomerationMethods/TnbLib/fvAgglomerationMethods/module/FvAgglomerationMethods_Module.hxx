#pragma once
#ifndef _FvAgglomerationMethods_Module_Header
#define _FvAgglomerationMethods_Module_Header

#ifdef FoamFvAgglomerationMethods_STATIC_DEFINE
#define FoamFvAgglomerationMethods_EXPORT
#else
#ifdef FoamFvAgglomerationMethods_EXPORT_DEFINE
#define FoamFvAgglomerationMethods_EXPORT __declspec(dllexport)
#else
#define FoamFvAgglomerationMethods_EXPORT __declspec(dllimport)
#endif // FoamFvAgglomerationMethods_EXPORT_DEFINE
#endif // FoamFvAgglomerationMethods_EXPORT_DEFINE

#ifdef FoamFvAgglomerationMethods_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FvMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>

#endif // FoamFvAgglomerationMethods_EXPORT_DEFINE

#endif // !_FvAgglomerationMethods_Module_Header
