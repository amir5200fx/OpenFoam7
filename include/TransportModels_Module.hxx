#pragma once
#ifndef _TransportModels_Module_Header
#define _TransportModels_Module_Header

#ifdef FoamTransportModels_STATIC_DEFINE
#define FoamTransportModels_EXPORT
#else
#ifdef FoamTransportModels_EXPORT_DEFINE
#define FoamTransportModels_EXPORT __declspec(dllexport)
#else
#define FoamTransportModels_EXPORT __declspec(dllimport)
#endif // FoamTransportModels_EXPORT_DEFINE
#endif // FoamTransportModels_STATIC_DEFINE

#ifdef FoamTransportModels_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#endif // FoamTransportModels_EXPORT_DEFINE

#endif // !_TransportModels_Module_Header