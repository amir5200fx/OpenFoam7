#pragma once
#ifndef _tabulatedHeatTransfer_Header
#define _tabulatedHeatTransfer_Header

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
	tnbLib::fv::tabulatedHeatTransfer

Description
	Tabulated heat transfer model. The heat exchange area per unit volume
	must be provided.  The 2D table returns the heat transfer coefficient
	by querying the local and neighbour region velocities

\*---------------------------------------------------------------------------*/

#include <interRegionHeatTransferModel.hxx>
#include <autoPtr.hxx>
#include <interpolation2DTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							Class tabulatedHeatTransfer Declaration
		\*---------------------------------------------------------------------------*/

		class tabulatedHeatTransfer
			:
			public interRegionHeatTransferModel
		{
			// Private Data

				//- Name of velocity field; default = U
			word UName_;

			//- Name of neighbour velocity field; default = U
			word UNbrName_;

			//- 2D look up table
			autoPtr<interpolation2DTable<scalar>> hTable_;

			//- Area per unit volume of heat exchanger
			autoPtr<volScalarField> AoV_;

			//- Heat transfer coefficient table
			FoamFvOptions_EXPORT const interpolation2DTable<scalar>& hTable();

			//- Field of area divided by volume
			FoamFvOptions_EXPORT const volScalarField& AoV();

			//- Start time name
			const word startTimeName_;


		public:

			//- Runtime type information
			//TypeName("tabulatedHeatTransfer");
			static const char* typeName_() { return "tabulatedHeatTransfer"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamFvOptions_EXPORT tabulatedHeatTransfer
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamFvOptions_EXPORT virtual ~tabulatedHeatTransfer();


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

#endif // !_tabulatedHeatTransfer_Header
