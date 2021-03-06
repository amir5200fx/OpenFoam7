#pragma once
#ifndef _IOporosityModelList_Header
#define _IOporosityModelList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::IOporosityModelList

Description
	List of porosity models with IO functionality

SourceFiles
	IOporosityModelList.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <porosityModelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class IOporosityModelList Declaration
	\*---------------------------------------------------------------------------*/

	class IOporosityModelList
		:
		public IOdictionary,
		public porosityModelList
	{
		// Private Member Functions

			//- Create IO object if dictionary is present
		FoamFiniteVolume_EXPORT IOobject createIOobject(const fvMesh& mesh) const;


	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT IOporosityModelList(const fvMesh& mesh);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT IOporosityModelList(const IOporosityModelList&) = delete;

		//- Destructor
		virtual ~IOporosityModelList()
		{}


		// Member Functions

			//- Read dictionary
		FoamFiniteVolume_EXPORT virtual bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const IOporosityModelList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOporosityModelList_Header
