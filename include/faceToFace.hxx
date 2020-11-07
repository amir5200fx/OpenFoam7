#pragma once
#ifndef _faceToFace_Header
#define _faceToFace_Header

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
	tnbLib::faceToFace

Description
	A topoSetSource to select faces based on usage in another faceSet.

SourceFiles
	faceToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class faceToFace Declaration
	\*---------------------------------------------------------------------------*/

	class faceToFace
		:
		public topoSetSource
	{
		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Name of set to use
		word setName_;

	public:

		//- Runtime type information
		/*TypeName("faceToFace");*/
		static const char* typeName_() { return "faceToFace"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT faceToFace
		(
			const polyMesh& mesh,
			const word& setName
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT faceToFace
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT faceToFace
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~faceToFace();


		// Member Functions

		virtual sourceType setType() const
		{
			return FACESETSOURCE;
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

#endif // !_faceToFace_Header
