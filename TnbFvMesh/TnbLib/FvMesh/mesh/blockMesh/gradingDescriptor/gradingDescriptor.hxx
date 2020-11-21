#pragma once
#ifndef _gradingDescriptor_Header
#define _gradingDescriptor_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::gradingDescriptor

Description
	Handles the specification for grading within a section of a block

	blockFraction: the fraction of the block the section occupies

	nDivFraction: the fraction of the divisions of the block allocated to
		the section

	expansionRatio: the expansions ratio for the grading with the section of
		block defined as the ratio of the size of the division at either and
		of the section.

SourceFiles
	gradingDescriptor.C

\*---------------------------------------------------------------------------*/


#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class gradingDescriptor;
	class gradingDescriptors;
	FoamFvMesh_EXPORT Istream& operator>>(Istream&, gradingDescriptor&);
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const gradingDescriptor&);

	/*---------------------------------------------------------------------------*\
						 Class gradingDescriptor Declaration
	\*---------------------------------------------------------------------------*/

	class gradingDescriptor
	{
		// Private Data

		scalar blockFraction_;
		scalar nDivFraction_;
		scalar expansionRatio_;


	public:

		friend class gradingDescriptors;


		// Constructors

			//- Default constructor
		FoamFvMesh_EXPORT gradingDescriptor();

		//- Construct from components
		FoamFvMesh_EXPORT gradingDescriptor
		(
			const scalar blockFraction,
			const scalar nDivFraction,
			const scalar expansionRatio
		);

		//- Construct from expansionRatio
		FoamFvMesh_EXPORT gradingDescriptor
		(
			const scalar expansionRatio
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT gradingDescriptor(Istream&);


		//- Destructor
		FoamFvMesh_EXPORT ~gradingDescriptor();


		// Member Functions

			// Access

		scalar blockFraction() const
		{
			return blockFraction_;
		}

		scalar nDivFraction() const
		{
			return nDivFraction_;
		}

		scalar expansionRatio() const
		{
			return expansionRatio_;
		}


		// Member Functions

			//- Return the inverse gradingDescriptor with 1/expansionRatio
		FoamFvMesh_EXPORT gradingDescriptor inv() const;


		// Member Operators

		FoamFvMesh_EXPORT bool operator==(const gradingDescriptor&) const;
		FoamFvMesh_EXPORT bool operator!=(const gradingDescriptor&) const;


		// IOstream Operators

		friend FoamFvMesh_EXPORT Istream& operator>>(Istream&, gradingDescriptor&);
		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const gradingDescriptor&);

		friend FoamFvMesh_EXPORT Istream& operator>>(Istream&, gradingDescriptors&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gradingDescriptor_Header
