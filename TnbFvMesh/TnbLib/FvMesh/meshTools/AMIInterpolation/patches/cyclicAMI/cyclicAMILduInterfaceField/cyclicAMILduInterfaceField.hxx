#pragma once
#ifndef _cyclicAMILduInterfaceField_Header
#define _cyclicAMILduInterfaceField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::cyclicAMILduInterfaceField

Description
	Abstract base class for cyclic AMI coupled interfaces

SourceFiles
	cyclicAMILduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>

#include <typeInfo.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicAMILduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicAMILduInterfaceField
	{

	public:

		//- Runtime type information
		//TypeName("cyclicAMILduInterfaceField");
		static const char* typeName_() { return "cyclicAMILduInterfaceField"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		cyclicAMILduInterfaceField()
		{}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicAMILduInterfaceField();


		// Member Functions

			// Access

				//- Is the transform required
		FoamFvMesh_EXPORT virtual bool doTransform() const = 0;

		//- Return face transformation tensor
		FoamFvMesh_EXPORT virtual const tensorField& forwardT() const = 0;

		//- Return neighbour-cell transformation tensor
		FoamFvMesh_EXPORT virtual const tensorField& reverseT() const = 0;

		//- Return rank of component for transform
		FoamFvMesh_EXPORT virtual int rank() const = 0;


		//- Transform given patch field
		template<class Type>
		void transformCoupleField(Field<Type>& f) const;

		//- Transform given patch internal field
		FoamFvMesh_EXPORT void transformCoupleField
		(
			scalarField& psiInternal,
			const direction cmpt
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <tensorField.hxx>

template<class Type>
void tnbLib::cyclicAMILduInterfaceField::transformCoupleField
(
	Field<Type>& f
) const
{
	if (doTransform())
	{
		if (forwardT().size() == 1)
		{
			transform(f, forwardT()[0], f);
		}
		else
		{
			transform(f, forwardT(), f);
		}
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMILduInterfaceField_Header
