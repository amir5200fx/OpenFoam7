#pragma once
#ifndef _axesRotation_Header
#define _axesRotation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::axesRotation

Description
	A coordinate rotation specified using global axis

	The rotation is defined by a combination of vectors (e1/e2), (e2/e3)
	or (e3/e1). Any nonorthogonality will be absorbed into the second
	vector.

	\verbatim
	axesRotation
	{
		type        axesRotation;
		e1          (1 0 0);
		e2          (0 1 0);
	}
	\endverbatim

SourceFiles
	axesRotation.C

\*---------------------------------------------------------------------------*/

#include <coordinateRotation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class axesRotation Declaration
	\*---------------------------------------------------------------------------*/

	class axesRotation
		:
		public coordinateRotation
	{
		// Private Data

			//- Local-to-Global transformation tensor
		tensor R_;

		//- Global-to-Local transformation tensor
		tensor Rtr_;

		//- The combination of local axes to be used
		enum axisOrder
		{
			e1e2,
			e2e3,
			e3e1
		};

		// Private Member Functions

			//- Calculate transformation tensor
		FoamFvMesh_EXPORT void calcTransform
		(
			const vector& axis1,
			const vector& axis2,
			const axisOrder& order = e3e1
		);


	public:

		//- Runtime type information
		//TypeName("axesRotation");
		static const char* typeName_() { return "axesRotation"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT axesRotation();

		//- Construct from 2 axes
		FoamFvMesh_EXPORT axesRotation(const vector& axis, const vector& dir);

		//- Construct from dictionary
		FoamFvMesh_EXPORT axesRotation(const dictionary&);

		//- Construct from components
		FoamFvMesh_EXPORT axesRotation(const tensor& R);

		//- Construct from dictionary and mesh
		FoamFvMesh_EXPORT axesRotation(const dictionary&, const objectRegistry&);

		//- Return clone
		autoPtr<axesRotation> clone() const
		{
			return autoPtr<axesRotation>(new axesRotation(*this));
		}


		//- Destructor
		virtual ~axesRotation()
		{}


		// Member Functions

			//- Reset rotation to an identity rotation
		virtual void clear()
		{
			R_ = sphericalTensor::I;
			Rtr_ = sphericalTensor::I;
		}

		//- Update the rotation for a list of cells
		virtual void updateCells(const polyMesh&, const labelList&)
		{}

		//- Return local-to-global transformation tensor
		virtual const tensor& R() const
		{
			return R_;
		}

		//- Return global-to-local transformation tensor
		virtual const tensor& Rtr() const
		{
			return Rtr_;
		}

		//- Return local Cartesian x-axis in global coordinates
		virtual const vector e1() const
		{
			return Rtr_.x();
		}

		//- Return local Cartesian y-axis in global coordinates
		virtual const vector e2() const
		{
			return Rtr_.y();
		}

		//- Return local Cartesian z-axis in global coordinates
		virtual const vector e3() const
		{
			return Rtr_.z();
		}

		//- Return transformation tensor field
		FoamFvMesh_EXPORT virtual const tensorField& Tr() const;

		//- Transform vectorField using transformation tensor field
		FoamFvMesh_EXPORT virtual tmp<vectorField> transform(const vectorField& st) const;

		//- Transform vector using transformation tensor
		FoamFvMesh_EXPORT virtual vector transform(const vector& st) const;

		//- Inverse transform vectorField using transformation tensor field
		FoamFvMesh_EXPORT virtual tmp<vectorField> invTransform(const vectorField& st) const;

		//- Inverse transform vector using transformation tensor
		FoamFvMesh_EXPORT virtual vector invTransform(const vector& st) const;

		//- Transform tensor field using transformation tensorField
		FoamFvMesh_EXPORT virtual tmp<tensorField> transformTensor(const tensorField& st) const;

		//- Transform tensor using transformation tensorField
		FoamFvMesh_EXPORT virtual tensor transformTensor(const tensor& st) const;

		//- Transform tensor sub-field using transformation tensorField
		FoamFvMesh_EXPORT virtual tmp<tensorField> transformTensor
		(
			const tensorField& st,
			const labelList& cellMap
		) const;

		//- Transform vectorField using transformation tensorField and return
		//  symmetric tensorField
		FoamFvMesh_EXPORT virtual tmp<symmTensorField> transformVector
		(
			const vectorField& st
		) const;

		//- Transform vector using transformation tensor and return
		//  symmetric tensor
		FoamFvMesh_EXPORT virtual symmTensor transformVector(const vector& st) const;


		// Member Operators

			//- Assign from dictionary
		FoamFvMesh_EXPORT void operator=(const dictionary&);


		// Write

			//- Write
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_axesRotation_Header
