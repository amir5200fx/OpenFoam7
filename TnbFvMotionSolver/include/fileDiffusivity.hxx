#pragma once
#ifndef _fileDiffusivity_Header
#define _fileDiffusivity_Header

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
	tnbLib::fileDiffusivity

Description
	Motion diffusivity read from given file name.

SourceFiles
	fileDiffusivity.C

\*---------------------------------------------------------------------------*/

#include <motionDiffusivity.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class fileDiffusivity Declaration
	\*---------------------------------------------------------------------------*/

	class fileDiffusivity
		:
		public motionDiffusivity
	{
	protected:

		// Protected data

		surfaceScalarField faceDiffusivity_;


	public:

		//- Runtime type information
		TypeName("file");


		// Constructors

			//- Construct for the given fvMesh and data Istream
		fileDiffusivity(const fvMesh& mesh, Istream& mdData);

		//- Disallow default bitwise copy construction
		fileDiffusivity(const fileDiffusivity&) = delete;


		//- Destructor
		virtual ~fileDiffusivity();


		// Member Functions

			//- Do not correct the motion diffusivity
		virtual void correct()
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const fileDiffusivity&) = delete;

		//- Return diffusivity field
		virtual tmp<surfaceScalarField> operator()() const
		{
			return faceDiffusivity_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fileDiffusivity_Header
