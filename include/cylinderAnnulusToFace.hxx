#pragma once
#ifndef _cylinderAnnulusToFace_Header
#define _cylinderAnnulusToFace_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::cylinderAnnulusToFace

Description
	A topoSetSource to select faces based on face centres inside a
	cylinder annulus.

SourceFiles
	cylinderAnnulusToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class cylinderAnnulusToFace Declaration
	\*---------------------------------------------------------------------------*/

	class cylinderAnnulusToFace
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- First point on cylinder axis
		vector p1_;

		//- Second point on cylinder axis
		vector p2_;

		//- Outer Radius
		scalar outerRadius_;

		//- Inner Radius
		scalar innerRadius_;


		// Private Member Functions

		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;


	public:

		//- Runtime type information
		/*TypeName("cylinderAnnulusToFace");*/
		static const char* typeName_() { return "cylinderAnnulusToFace"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT cylinderAnnulusToFace
		(
			const polyMesh& mesh,
			const vector& p1,
			const vector& p2,
			const scalar outerRadius,
			const scalar innerRadius
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT cylinderAnnulusToFace
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT cylinderAnnulusToFace
		(
			const polyMesh& mesh,
			Istream&
		);


		// Destructor
		FoamFvMesh_EXPORT virtual ~cylinderAnnulusToFace();

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

#endif // !_cylinderAnnulusToFace_Header
