#pragma once
#ifndef _pointConstraints_Header
#define _pointConstraints_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::pointConstraints

Description
	Application of (multi-)patch point constraints.

	Note: includes all points which are on the boundary of a patch
		  with a constraint. It includes them (even though the constraint
		  will already be implemented through the patch evaluation)
		  since these points might be
		  coupled to points which are not on any constraint patch and we
		  don't want to get inconsistency between the two points.

SourceFiles
	pointConstraints.C
	pointConstraintsTemplates.C

\*---------------------------------------------------------------------------*/

#include <MeshObject.hxx>
#include <tensorField.hxx>
#include <pointFieldFwd.hxx>
#include <pointConstraint.hxx>

#include <pointFieldsFwd.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointMesh;
	class polyMesh;
	 
	template<class T> class pointPatchField;  // added by amir
	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;  // added by amir

	/*---------------------------------------------------------------------------*\
						   Class pointConstraints Declaration
	\*---------------------------------------------------------------------------*/

	class pointConstraints
		:
		public MeshObject<pointMesh, UpdateableMeshObject, pointConstraints>
	{
		// Private Data

			// Patch-patch constraints

				//- Mesh points on which to apply special constraints
		labelList patchPatchPointConstraintPoints_;
		//- Special constraints (as tensors)
		tensorField patchPatchPointConstraintTensors_;
		//- Special constraints (raw)
		List<pointConstraint> patchPatchPointConstraints_;


		// Private Member Functions

			//- Make patch-patch constraints
		FoamFiniteVolume_EXPORT void makePatchPatchAddressing();


	public:

		// Declare name of the class and its debug switch
		/*ClassName("pointConstraints");*/
		static const char* typeName_() { return "pointConstraints"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName; 
		static FoamFiniteVolume_EXPORT int debug;


		// Constructors

			//- Constructor from pointMesh.
		FoamFiniteVolume_EXPORT explicit pointConstraints(const pointMesh&);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT pointConstraints(const pointConstraints&) = delete;


		//- Destructor
		FoamFiniteVolume_EXPORT ~pointConstraints();


		// Member Functions

			// Access

				//- Mesh points on which to apply special constraints
		const labelList& patchPatchPointConstraintPoints() const
		{
			return patchPatchPointConstraintPoints_;
		}

		//- Special constraints
		const tensorField& patchPatchPointConstraintTensors() const
		{
			return patchPatchPointConstraintTensors_;
		}

		//- Actual constraints
		const List<pointConstraint>& patchPatchPointConstraints() const
		{
			return patchPatchPointConstraints_;
		}


		// Edit

		//- Update mesh topology using the morph engine
		FoamFiniteVolume_EXPORT void updateMesh(const mapPolyMesh&);

		//- Correct weighting factors for moving mesh.
		FoamFiniteVolume_EXPORT bool movePoints();


		// Interpolation functions

			//- Helper: sync data on collocated points only
		template<class Type, class CombineOp>
		static void syncUntransformedData
		(
			const polyMesh& mesh,
			List<Type>& pointData,
			const CombineOp& cop
		);

		//- Helper: set patchField values from internal values (on
		//  valuePointPatchFields). Opposite of
		//  pointPatchField::setInInternalField
		template<class Type>
		static void setPatchFields
		(
			GeometricField<Type, pointPatchField, pointMesh>&
		);

		//- Apply patch-patch constraints only
		template<class Type>
		void constrainCorners
		(
			GeometricField<Type, pointPatchField, pointMesh>& pf
		) const;

		//- Apply boundary conditions (single-patch constraints) and
		//  patch-patch constraints on generic pointField.
		//  Optionally override valuePointPatchFields with constrained
		//  values (see setPatchFields above)
		template<class Type>
		void constrain
		(
			GeometricField<Type, pointPatchField, pointMesh>& pf,
			const bool overrideValue = false
		) const;

		//- Apply boundary conditions (single-patch constraints),
		//  patch-patch constraints and
		//  two-D constraints on displacement field
		FoamFiniteVolume_EXPORT void constrainDisplacement
		(
			pointVectorField& displacement,
			const bool overrideValue = false
		) const;


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const pointConstraints&) = delete;
	};


	template<>
	FoamFiniteVolume_EXPORT void pointConstraints::constrainCorners<scalar>
		(
			GeometricField<scalar, pointPatchField, pointMesh>& pf
			) const;
	template<>
	FoamFiniteVolume_EXPORT void pointConstraints::constrainCorners<label>
		(
			GeometricField<label, pointPatchField, pointMesh>& pf
			) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pointConstraintsI.hxx>

//#ifdef NoRepository
//#include <pointConstraintsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointConstraints_Header
