#pragma once
#ifndef _RigidBodyMotion_Module_Header
#define _RigidBodyMotion_Module_Header

#ifdef FoamRigidBodyMotion_STATIC_DEFINE
#define FoamRigidBodyMotion_EXPORT
#else
#ifdef FoamRigidBodyMotion_EXPORT_DEFINE
#define FoamRigidBodyMotion_EXPORT __declspec(dllexport)
#else
#define FoamRigidBodyMotion_EXPORT __declspec(dllimport)
#endif // FoamRigidBodyMotion_EXPORT_DEFINE
#endif // FoamRigidBodyMotion_STATIC_DEFINE

#ifdef FoamRigidBodyMotion_EXPORT_DEFINE
#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#endif // FoamRigidBodyMotion_EXPORT_DEFINE

#endif // !_RigidBodyMotion_Module_Header
