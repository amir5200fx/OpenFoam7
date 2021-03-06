#pragma once
#ifndef _genericPolyPatch_Header
#define _genericPolyPatch_Header

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
	tnbLib::genericPolyPatch

Description
	Substitute for unknown patches. Used for postprocessing when only
	basic polyPatch info is needed.

Note
	Storage is not optimal. It stores all face centres and cells on all
	processors to keep the addressing calculation simple.

SourceFiles
	genericPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <polyPatch.hxx>
#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class genericPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class genericPolyPatch
		:
		public polyPatch
	{
		// Private Data

		word actualTypeName_;
		dictionary dict_;

	public:

		//- Runtime type information
		//TypeName("genericPatch");
		static const char* typeName_() { return "genericPatch"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT genericPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct from dictionary
		FoamBase_EXPORT genericPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct as copy, resetting the boundary mesh
		FoamBase_EXPORT genericPolyPatch
		(
			const genericPolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamBase_EXPORT genericPolyPatch
		(
			const genericPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct given the original patch and a map
		FoamBase_EXPORT genericPolyPatch
		(
			const genericPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new genericPolyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new genericPolyPatch(*this, bm, index, newSize, newStart)
					);
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new genericPolyPatch(*this, bm, index, mapAddressing, newStart)
					);
		}


		//- Destructor
		FoamBase_EXPORT ~genericPolyPatch();


		// Member Functions

			//- Write the polyPatch data as a dictionary
		FoamBase_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_genericPolyPatch_Header
