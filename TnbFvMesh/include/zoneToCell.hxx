#pragma once
#ifndef _zoneToCell_Header
#define _zoneToCell_Header

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
	tnbLib::zoneToCell

Description
	A topoSetSource to select faces based on cellZone.

SourceFiles
	zoneToCell.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <wordRe.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class zoneToCell Declaration
	\*---------------------------------------------------------------------------*/

	class zoneToCell
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Name/regular expression of cellZone
		wordRe zoneName_;


		// Private Member Functions

		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		/*TypeName("zoneToCell");*/
		static const char* typeName_() { return "zoneToCell"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT zoneToCell
		(
			const polyMesh& mesh,
			const word& zoneName
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT zoneToCell
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT zoneToCell
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~zoneToCell();


		// Member Functions

		virtual sourceType setType() const
		{
			return CELLSETSOURCE;
		}

		FoamFvMesh_EXPORT virtual void applyToSet
		(
			const topoSetSource::setAction action,
			topoSet&
		) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zoneToCell_Header
