#pragma once
#ifndef _rotatedBoxToCell_Header
#define _rotatedBoxToCell_Header

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
	tnbLib::rotatedBoxToCell

Description
	A topoSetSource to select cells based on cell centres inside
	rotated/skewed box (parallelopiped?).

	Box defined as origin and i,j,k vectors.
	E.g. box rotated 45 degrees around z-axis with sizes sqrt(0.2^2+0.2^2)
	(and extra large, 200 in z direction):
	\verbatim
	   origin   ( 0.4 0.4 -100);
	   i        ( 0.2 0.2    0);
	   j        (-0.2 0.2    0);
	   k        ( 0.0 0.0  100);
	\endverbatim

SourceFiles
	rotatedBoxToCell.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <treeBoundBox.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class rotatedBoxToCell Declaration
	\*---------------------------------------------------------------------------*/

	class rotatedBoxToCell
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;


		//- Skewed box
		const vector origin_;
		const vector i_;
		const vector j_;
		const vector k_;


		// Private Member Functions

		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		/*TypeName("rotatedBoxToCell");*/
		static const char* typeName_() { return "rotatedBoxToCell"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT rotatedBoxToCell
		(
			const polyMesh& mesh,
			const vector& origin,
			const vector& i,
			const vector& j,
			const vector& k
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT rotatedBoxToCell(const polyMesh& mesh, const dictionary& dict);

		//- Construct from Istream
		FoamFvMesh_EXPORT rotatedBoxToCell(const polyMesh& mesh, Istream&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~rotatedBoxToCell();


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

#endif // !_rotatedBoxToCell_Header
