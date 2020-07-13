#pragma once
#ifndef _zoneToFace_Header
#define _zoneToFace_Header

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
	tnbLib::zoneToFace

Description
	A topoSetSource to select faces based on faceZone.

SourceFiles
	zoneToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <wordRe.hxx>


namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class zoneToFace Declaration
	\*---------------------------------------------------------------------------*/

	class zoneToFace
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static addToUsageTable usage_;

		//- Name/regular expression of cellZone
		wordRe zoneName_;


		// Private Member Functions

		void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		TypeName("zoneToFace");

		// Constructors

			//- Construct from components
		zoneToFace
		(
			const polyMesh& mesh,
			const word& zoneName
		);

		//- Construct from dictionary
		zoneToFace
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		zoneToFace
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		virtual ~zoneToFace();


		// Member Functions

		virtual sourceType setType() const
		{
			return FACESETSOURCE;
		}

		virtual void applyToSet
		(
			const topoSetSource::setAction action,
			topoSet&
		) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zoneToFace_Header
