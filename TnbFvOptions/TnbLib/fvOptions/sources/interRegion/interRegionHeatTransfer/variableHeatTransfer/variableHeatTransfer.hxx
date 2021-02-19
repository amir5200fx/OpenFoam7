#pragma once
#ifndef _variableHeatTransfer_Header
#define _variableHeatTransfer_Header

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
	tnbLib::fv::variableHeatTransfer

Description
	Variable heat transfer model depending on local values. The area of contact
	between regions (area) must be provided. The Nu number is calculated as:

		Nu = a*pow(Re, b)*pow(Pr, c)

	and the heat transfer coefficient as:

		htc = Nu*K/ds

	where:
		K is the heat conduction
		ds is the strut diameter

\*---------------------------------------------------------------------------*/

#include <interRegionHeatTransferModel.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							Class variableHeatTransfer Declaration
		\*---------------------------------------------------------------------------*/

		class variableHeatTransfer
			:
			public interRegionHeatTransferModel
		{
			// Private Data

				//- Name of neighbour velocity field; default = U
			word UNbrName_;

			//- Model constants
			scalar a_;
			scalar b_;
			scalar c_;

			//- Strut diameter
			scalar ds_;

			//- Fluid Prandt number
			scalar Pr_;

			//- Area per unit volume of heat exchanger
			autoPtr<volScalarField> AoV_;


		public:

			//- Runtime type information
			//TypeName("variableHeatTransfer");
			static const char* typeName_() { return "variableHeatTransfer"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamFvOptions_EXPORT variableHeatTransfer
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamFvOptions_EXPORT virtual ~variableHeatTransfer();


			// Public Functions

				//- Calculate the heat transfer coefficient
			FoamFvOptions_EXPORT virtual void calculateHtc();


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_variableHeatTransfer_Header
