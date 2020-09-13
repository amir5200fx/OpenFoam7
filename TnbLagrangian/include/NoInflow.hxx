#pragma once
#ifndef _NoInflow_Header
#define _NoInflow_Header

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
	tnbLib::NoInflow

Description
	Not inserting any particles

\*---------------------------------------------------------------------------*/

#include <InflowBoundaryModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
							  Class NoInflow Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoInflow
		:
		public InflowBoundaryModel<CloudType>
	{
	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from dictionary
		NoInflow
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~NoInflow();


		// Member Functions

			//- Introduce particles (none in this case)
		virtual void inflow();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoInflowI.hxx>

//#ifdef NoRepository
//#include <NoInflow.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoInflow_Header
