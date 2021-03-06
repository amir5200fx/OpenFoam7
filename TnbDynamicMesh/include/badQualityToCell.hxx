#pragma once
#ifndef _badQualityToCell_Header
#define _badQualityToCell_Header

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
	tnbLib::badQualityToCell

Description
	Selects bad quality cells (using snappyHexMesh/cvMesh mesh quality selector)

SourceFiles
	badQualityToCell.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <PackedBoolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class badQualityToCell Declaration
	\*---------------------------------------------------------------------------*/

	class badQualityToCell
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
		//TypeName("badQualityToCell");
		static const char* typeName_() { return "badQualityToCell"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from dictionary
		FoamDynamicMesh_EXPORT badQualityToCell
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamDynamicMesh_EXPORT badQualityToCell
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~badQualityToCell();


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

#endif // !_badQualityToCell_Header
