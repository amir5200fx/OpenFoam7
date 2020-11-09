#pragma once
#ifndef _ThermophysicalModels_Module_Header
#define _ThermophysicalModels_Module_Header

#include <TransportModels_Module.hxx>
#include <ODE_Module.hxx>

#ifdef FoamThermophysicalModels_STATIC_DEFINE
#define FoamThermophysicalModels_EXPORT
#else
#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamThermophysicalModels_EXPORT __declspec(dllexport)
#else
#define FoamThermophysicalModels_EXPORT __declspec(dllimport)
#endif // FoamThermophysicalModels_EXPORT_DEFINE

#endif // FoamThermophysicalModels_STATIC_DEFINE

#endif // !_ThermophysicalModels_Module_Header