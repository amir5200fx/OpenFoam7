#pragma once
#ifndef _cyclicLduInterfaceField_Header
#define _cyclicLduInterfaceField_Header

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
	tnbLib::cyclicLduInterfaceField

Description
	Abstract base class for cyclic coupled interfaces.

SourceFiles
	cyclicLduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicLduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicLduInterfaceField
	{

	public:

		//- Runtime type information
		//TypeName("cyclicLduInterfaceField");
		static const char* typeName_() { return "cyclicLduInterfaceField"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given coupled patch
		cyclicLduInterfaceField()
		{}


		//- Destructor
		FoamBase_EXPORT virtual ~cyclicLduInterfaceField();


		// Member Functions

			// Access

				//- Is the transform required
		FoamBase_EXPORT virtual bool doTransform() const = 0;

		//- Return face transformation tensor
		FoamBase_EXPORT virtual const tensorField& forwardT() const = 0;

		//- Return neighbour-cell transformation tensor
		FoamBase_EXPORT virtual const tensorField& reverseT() const = 0;

		//- Return rank of component for transform
		FoamBase_EXPORT virtual int rank() const = 0;


		//- Transform given patch field
		template<class Type>
		void transformCoupleField(Field<Type>& f) const;

		//- Transform given patch component field
		FoamBase_EXPORT void transformCoupleField
		(
			scalarField& f,
			const direction cmpt
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <tensorField.hxx>

template<class Type>
void tnbLib::cyclicLduInterfaceField::transformCoupleField
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

#endif // !_cyclicLduInterfaceField_Header
