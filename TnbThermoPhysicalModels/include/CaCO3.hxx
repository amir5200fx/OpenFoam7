#pragma once
#ifndef _CaCO3_Header
#define _CaCO3_Header

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
	tnbLib::CaCO3

Description
	Calcium carbonate (limestone)

SourceFiles
	CaCO3.C

\*---------------------------------------------------------------------------*/

#include <solidProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class CaCO3 Declaration
	\*---------------------------------------------------------------------------*/

	class CaCO3
		:
		public solidProperties
	{

	public:

		//- Runtime type information
		//TypeName("CaCO3");
		static const char* typeName_() { return "CaCO3"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		FoamThermophysicalModels_EXPORT CaCO3();

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT CaCO3(const dictionary& dict);

		//- Construct and return clone
		virtual autoPtr<solidProperties> clone() const
		{
			return autoPtr<solidProperties>(new CaCO3(*this));
		}


		// I-O

			//- Write the function coefficients
		FoamThermophysicalModels_EXPORT void writeData(Ostream& os) const;

		//- Ostream Operator
		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const CaCO3& s);
	};


	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const CaCO3& s);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CaCO3_Header
