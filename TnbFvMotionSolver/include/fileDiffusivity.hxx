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
		//TypeName("file");
		static const char* typeName_() { return "file"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct for the given fvMesh and data Istream
		FoamFvMotionSolver_EXPORT fileDiffusivity(const fvMesh& mesh, Istream& mdData);

		//- Disallow default bitwise copy construction
		FoamFvMotionSolver_EXPORT fileDiffusivity(const fileDiffusivity&) = delete;


		//- Destructor
		FoamFvMotionSolver_EXPORT virtual ~fileDiffusivity();


		// Member Functions

			//- Do not correct the motion diffusivity
		virtual void correct()
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMotionSolver_EXPORT void operator=(const fileDiffusivity&) = delete;

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
