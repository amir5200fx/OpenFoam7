#pragma once
#ifndef _badQualityToFace_Header
#define _badQualityToFace_Header

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
	tnbLib::badQualityToFace

Description
	Selects bad quality faces (using snappyHexMesh/cvMesh mesh quality selector)

SourceFiles
	badQualityToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <PackedBoolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class badQualityToFace Declaration
	\*---------------------------------------------------------------------------*/

	class badQualityToFace
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamDynamicMesh_EXPORT addToUsageTable usage_;

		//- Mesh quality dictionary
		const dictionary dict_;


		// Private Member Functions

		FoamDynamicMesh_EXPORT void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		//TypeName("badQualityToFace");
		static const char* typeName_() { return "badQualityToFace"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from dictionary
		FoamDynamicMesh_EXPORT badQualityToFace
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamDynamicMesh_EXPORT badQualityToFace
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~badQualityToFace();


		// Member Functions

		virtual sourceType setType() const
		{
			return CELLSETSOURCE;
		}

		FoamDynamicMesh_EXPORT virtual void applyToSet
		(
			const topoSetSource::setAction action,
			topoSet&
		) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_badQualityToFace_Header
