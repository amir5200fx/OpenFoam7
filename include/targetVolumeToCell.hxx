#pragma once
#ifndef _targetVolumeToCell_Header
#define _targetVolumeToCell_Header

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
	tnbLib::targetVolumeToCell

Description
	A topoSetSource to select cells based on the wanted volume of selected
	cells. Adapts a plane until it has enough.

SourceFiles
	targetVolumeToCell.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <PackedBoolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class targetVolumeToCell Declaration
	\*---------------------------------------------------------------------------*/

	class targetVolumeToCell
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Wanted volume
		const scalar vol_;

		//- Normal of plane to sweep
		const vector n_;

		//- Optional name of cellSet to calculate volume in
		const word maskSetName_;


		// Private Member Functions

		FoamFvMesh_EXPORT scalar volumeOfSet(const PackedBoolList&) const;

		FoamFvMesh_EXPORT label selectCells
		(
			const scalar normalComp,
			const PackedBoolList&,
			PackedBoolList& selected
		) const;

		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		/*TypeName("targetVolumeToCell");*/
		static const char* typeName_() { return "targetVolumeToCell"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT targetVolumeToCell
		(
			const polyMesh& mesh,
			const scalar vol,
			const vector&
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT targetVolumeToCell
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT targetVolumeToCell
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~targetVolumeToCell();


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

#endif // !_targetVolumeToCell_Header
