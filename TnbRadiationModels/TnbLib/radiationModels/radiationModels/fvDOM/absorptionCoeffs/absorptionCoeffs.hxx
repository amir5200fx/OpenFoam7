#pragma once
#ifndef _absorptionCoeffs_Header
#define _absorptionCoeffs_Header

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
	tnbLib::absorptionCoeffs

Description
	Absorption coefficients class used in greyMean and wideBand
	absorptionEmission models

SourceFiles
	absorptionCoeffs.C

\*---------------------------------------------------------------------------*/

#include <List.hxx>
#include <IOstreams.hxx>
#include <IOdictionary.hxx>

#include <FixedList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
							  Class absorptionCoeffs Declaration
		\*---------------------------------------------------------------------------*/

		class absorptionCoeffs
		{
		public:

			// Public data members

			static const int nCoeffs_ = 6;
			typedef FixedList<scalar, nCoeffs_> coeffArray;


		private:

			// Private Data

				// Temperature limits of applicability for functions

			scalar Tcommon_;

			scalar Tlow_;

			scalar Thigh_;


			// Polynomial using inverse temperatures
			bool invTemp_;

			coeffArray highACoeffs_;
			coeffArray lowACoeffs_;


			// Private Member Functions

				//- Check given temperature is within the range of the fitted coeffs
			FoamRadiationModels_EXPORT void checkT(const scalar T) const;


		public:

			// Constructors

				// Null constructor
			absorptionCoeffs()
			{}


			//- Destructor
			FoamRadiationModels_EXPORT ~absorptionCoeffs();


			// Member Functions

				//- Return the coefficients corresponding to the given temperature
			FoamRadiationModels_EXPORT const coeffArray& coeffs(const scalar T) const;

			// Initialise from a dictionary
			FoamRadiationModels_EXPORT void initialise(const dictionary&);


			// Access Functions

			inline bool invTemp() const;

			inline scalar Tcommon() const;

			inline scalar Tlow() const;

			inline scalar Thigh() const;

			inline const coeffArray& highACoeffs() const;

			inline const coeffArray& lowACoeffs() const;
		};

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tnbLib
} // End namespace radiationModels

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <absorptionCoeffsI.hxx>

#endif // !_absorptionCoeffs_Header
