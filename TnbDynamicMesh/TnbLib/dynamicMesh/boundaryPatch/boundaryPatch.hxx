#pragma once
#ifndef _boundaryPatch_Header
#define _boundaryPatch_Header

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
	tnbLib::boundaryPatch

Description
	Like polyPatch but without reference to mesh. patchIdentifier::index
	is not used. Used in boundaryMesh to hold data on patches.

SourceFiles
	boundaryPatch.C

\*---------------------------------------------------------------------------*/

#include <patchIdentifier.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class boundaryPatch;

	FoamDynamicMesh_EXPORT Ostream& operator<<(Ostream&, const boundaryPatch&);


	/*---------------------------------------------------------------------------*\
							   Class boundaryPatch Declaration
	\*---------------------------------------------------------------------------*/

	class boundaryPatch
		:
		public patchIdentifier
	{
		// Private Data

		label size_;
		label start_;

	public:

		// Constructors

			//- Construct from components
		FoamDynamicMesh_EXPORT boundaryPatch
		(
			const word& name,
			const label index,
			const label size,
			const label start,
			const word& physicalType = word::null
		);

		//- Construct from dictionary
		FoamDynamicMesh_EXPORT boundaryPatch
		(
			const word& name,
			const dictionary& dict,
			const label index
		);

		//- Copy constructor, resetting the index
		FoamDynamicMesh_EXPORT boundaryPatch(const boundaryPatch&, const label index);

		//- Clone
		FoamDynamicMesh_EXPORT autoPtr<boundaryPatch> clone() const;


		//- Destructor
		FoamDynamicMesh_EXPORT ~boundaryPatch();


		// Member Functions

		label size() const
		{
			return size_;
		}

		label& size()
		{
			return size_;
		}

		label start() const
		{
			return start_;
		}

		label& start()
		{
			return start_;
		}


		//- Write dictionary
		FoamDynamicMesh_EXPORT virtual void write(Ostream&) const;


		// Ostream Operator

		FoamDynamicMesh_EXPORT friend Ostream& operator<<(Ostream&, const boundaryPatch&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundaryPatch_Header
