#pragma once
#ifndef _constantHeatTransfer_Header
#define _constantHeatTransfer_Header

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
	tnbLib::fv::constantHeatTransfer

Description
	Constant heat transfer model. htcConst [W/m^2/K] and area/volume [1/m]
	must be provided.

\*---------------------------------------------------------------------------*/

#include <interRegionHeatTransferModel.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							Class constantHeatTransfer Declaration
		\*---------------------------------------------------------------------------*/

		class constantHeatTransfer
			:
			public interRegionHeatTransferModel
		{
			// Private Data

				//- Constant heat transfer coefficient [W/m^2/K]
			autoPtr<volScalarField> htcConst_;

			//- Area per unit volume of heat exchanger [1/m]
			autoPtr<volScalarField> AoV_;


		public:

			//- Runtime type information
			//TypeName("constantHeatTransfer");
			static const char* typeName_() { return "constantHeatTransfer"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamFvOptions_EXPORT constantHeatTransfer
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamFvOptions_EXPORT virtual ~constantHeatTransfer();


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

#endif // !_constantHeatTransfer_Header
