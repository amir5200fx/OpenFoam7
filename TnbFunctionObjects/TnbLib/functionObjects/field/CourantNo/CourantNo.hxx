#pragma once
#ifndef _CourantNo_Header
#define _CourantNo_Header

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
	tnbLib::functionObjects::CourantNo

Description
	Calculates and outputs the Courant number as a volScalarField.  The field is
	stored on the mesh database so that it can be retrieved and used for other
	applications.

See also
	tnbLib::functionObjects::fieldExpression
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	CourantNo.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class CourantNo Declaration
		\*---------------------------------------------------------------------------*/

		class CourantNo
			:
			public fieldExpression
		{
			// Private Data

				//- Name of flux field, default is "phi"
			word phiName_;

			//- Name of density field (optional)
			word rhoName_;


			// Private Member Functions

				//- Divide the Courant number by rho if required
			FoamFunctionObjects_EXPORT tmp<volScalarField::Internal> byRho
			(
				const tmp<volScalarField::Internal>& Co
			) const;

			//- Calculate the Courant number field and return true if successful
			FoamFunctionObjects_EXPORT virtual bool calc();


		public:

			//- Runtime type information
			//TypeName("CourantNo");
			static const char* typeName_() { return "CourantNo"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT CourantNo
			(
				const word& name,
				const Time&,
				const dictionary&
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~CourantNo();


			// Member Functions

				//- Read the CourantNo data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CourantNo_Header
