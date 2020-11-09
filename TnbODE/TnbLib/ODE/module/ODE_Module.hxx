#pragma once
#ifndef _ODE_Module_Header
#define _ODE_Module_Header

#include <Base_Module.hxx>

#ifdef FoamODE_STATIC_DEFINE
#define FoamODE_EXPORT
#else
#ifdef FoamODE_EXPORT_DEFINE
#define FoamODE_EXPORT __declspec(dllexport)
#else
#define FoamODE_EXPORT __declspec(dllimport)
#endif // FoamODE_EXPORT_DEFINE

#endif // FoamODE_STATIC_DEFINE

#endif // !_ODE_Module_Header