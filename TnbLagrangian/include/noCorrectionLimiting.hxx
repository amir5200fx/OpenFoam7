#pragma once
#ifndef _noCorrectionLimiting_Header
#define _noCorrectionLimiting_Header

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
	tnbLib::CorrectionLimitingMethods::noCorrectionLimiting

Description

SourceFiles
	noCorrectionLimiting.C

\*---------------------------------------------------------------------------*/

#include <CorrectionLimitingMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace CorrectionLimitingMethods
	{

		/*---------------------------------------------------------------------------*\
							Class noCorrectionLimiting Declaration
		\*---------------------------------------------------------------------------*/

		class noCorrectionLimiting
			:
			public CorrectionLimitingMethod
		{
		public:

			//- Runtime type information
			//TypeName("none");
			static const char* typeName_() { return "none"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT noCorrectionLimiting(const dictionary& dict);

			//- Copy constructor
			FoamLagrangian_EXPORT noCorrectionLimiting(const noCorrectionLimiting& cl);

			//- Construct and return a clone
			virtual autoPtr<CorrectionLimitingMethod> clone() const
			{
				return autoPtr<CorrectionLimitingMethod>
					(
						new noCorrectionLimiting(*this)
						);
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~noCorrectionLimiting();


			// Member Functions

				//- Return the limited velocity
			FoamLagrangian_EXPORT virtual vector limitedVelocity
			(
				const vector uP,
				const vector dU,
				const vector uMean
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace CorrectionLimitingMethods
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noCorrectionLimiting_Header
