#pragma once
#ifndef _thirdBodyEfficiencies_Header
#define _thirdBodyEfficiencies_Header

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
	tnbLib::thirdBodyEfficiencies

Description
	Third body efficiencies

SourceFiles
	thirdBodyEfficienciesI.H

\*---------------------------------------------------------------------------*/

#include <scalarList.hxx>
#include <speciesTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class dictionary;  // added by amir

	class thirdBodyEfficiencies;
	Ostream& operator<<(Ostream&, const thirdBodyEfficiencies&);


	/*---------------------------------------------------------------------------*\
					  Class thirdBodyEfficiencies Declaration
	\*---------------------------------------------------------------------------*/

	class thirdBodyEfficiencies
		:
		public scalarList
	{
		// Private Data

		const speciesTable& species_;


	public:

		// Constructors

			//- Construct from components
		inline thirdBodyEfficiencies
		(
			const speciesTable& species,
			const scalarList& efficiencies
		);

		//- Construct from dictionary
		inline thirdBodyEfficiencies
		(
			const speciesTable& species,
			const dictionary& dict
		);


		// Member Functions

			//- Calculate and return M, the concentration of the third-bodies
		inline scalar M(const scalarList& c) const;

		//- Write to stream
		inline void write(Ostream& os) const;



		// Ostream Operator

		friend Ostream& operator<<(Ostream&, const thirdBodyEfficiencies&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <thirdBodyEfficienciesI.hxx>

#endif // !_thirdBodyEfficiencies_Header
