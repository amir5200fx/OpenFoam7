#pragma once
#ifndef _normalToFace_Header
#define _normalToFace_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::normalToFace

Description
	A topoSetSource to select faces based on normal.

SourceFiles
	normalToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class normalToFace Declaration
	\*---------------------------------------------------------------------------*/

	class normalToFace
		:
		public topoSetSource
	{

	private:

		//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- (unit)vector to compare to
		vector normal_;

		//- Tolerance (i.e. cos of angle between normal_ and faceNormal)
		const scalar tol_;


		// Private Member Functions

			//- Normalize normal and check tolerance
		FoamFvMesh_EXPORT void setNormal();


	public:

		//- Runtime type information
		/*TypeName("normalToFace");*/
		static const char* typeName_() { return "normalToFace"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT normalToFace
		(
			const polyMesh& mesh,
			const vector& normal,
			const scalar tol
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT normalToFace(const polyMesh& mesh, const dictionary& dict);

		//- Construct from Istream
		FoamFvMesh_EXPORT normalToFace(const polyMesh& mesh, Istream&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~normalToFace();


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

#endif // !_normalToFace_Header
