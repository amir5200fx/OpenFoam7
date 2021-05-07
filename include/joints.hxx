#pragma once
#ifndef _joints_Header
#define _joints_Header

// Null joint for the root-body
#include <nullJoint.hxx>

// Composite joint to handle combination of rotations and translations
#include <compositeJoint.hxx>

// 6-DoF joint for floating bodies
#include <floatingJoint.hxx>

// Revolute joints
#include <Rx.hxx>
#include <Ry.hxx>
#include <Rz.hxx>
#include <Ra.hxx>
#include <Rs.hxx>
#include <Rzyx.hxx>
#include <Rxyz.hxx>
#include <Ryxz.hxx>

// Prismatic joints
#include <Px.hxx>
#include <Py.hxx>
#include <Pz.hxx>
#include <Pa.hxx>
#include <Pxyz.hxx>

// 0-DoF joints
#include <rigid.hxx>
#include <function.hxx>
#include <functionDot.hxx>


#endif // !_joints_Header
