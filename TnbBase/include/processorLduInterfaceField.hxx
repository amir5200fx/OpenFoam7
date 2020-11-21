#pragma once
#ifndef _processorLduInterfaceField_Header
#define _processorLduInterfaceField_Header

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
	tnbLib::processorLduInterfaceField

Description
	Abstract base class for processor coupled interfaces.

SourceFiles
	processorLduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class processorLduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class processorLduInterfaceField
	{

	public:

		//- Runtime type information
		//TypeName("processorLduInterfaceField");
		static const char* typeName_() { return "processorLduInterfaceField"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given coupled patch
		processorLduInterfaceField()
		{}


		//- Destructor
		FoamBase_EXPORT virtual ~processorLduInterfaceField();


		// Member Functions

			// Access

				//- Return communicator used for comms
		FoamBase_EXPORT virtual label comm() const = 0;

		//- Return processor number
		FoamBase_EXPORT virtual int myProcNo() const = 0;

		//- Return neighbour processor number
		FoamBase_EXPORT virtual int neighbProcNo() const = 0;

		//- Is the transform required
		FoamBase_EXPORT virtual bool doTransform() const = 0;

		//- Return face transformation tensor
		FoamBase_EXPORT virtual const tensorField& forwardT() const = 0;

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
void tnbLib::processorLduInterfaceField::transformCoupleField
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

#endif // !_processorLduInterfaceField_Header
