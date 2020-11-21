#pragma once
#ifndef _simpleFilter_Header
#define _simpleFilter_Header

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
	tnbLib::simpleFilter

Description
	Simple top-hat filter used in dynamic LES models.

	Implemented as a surface integral of the face interpolate of the field.

SourceFiles
	simpleFilter.C

\*---------------------------------------------------------------------------*/

#include <LESfilter.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class simpleFilter Declaration
	\*---------------------------------------------------------------------------*/

	class simpleFilter
		:
		public LESfilter

	{
	public:

		//- Runtime type information
		//TypeName("simple");
		static const char* typeName_() { return "simple"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamTurbulence_EXPORT simpleFilter(const fvMesh& mesh);

		//- Construct from IOdictionary
		FoamTurbulence_EXPORT simpleFilter(const fvMesh& mesh, const dictionary&);

		//- Disallow default bitwise copy construction
		FoamTurbulence_EXPORT simpleFilter(const simpleFilter&) = delete;


		//- Destructor
		virtual ~simpleFilter()
		{}


		// Member Functions

			//- Read the LESfilter dictionary
		FoamTurbulence_EXPORT virtual void read(const dictionary&);


		// Member Operators

		FoamTurbulence_EXPORT virtual tmp<volScalarField> operator()
			(
				const tmp<volScalarField>&
				) const;

		FoamTurbulence_EXPORT virtual tmp<volVectorField> operator()
			(
				const tmp<volVectorField>&
				) const;

		FoamTurbulence_EXPORT virtual tmp<volSymmTensorField> operator()
			(
				const tmp<volSymmTensorField>&
				) const;

		FoamTurbulence_EXPORT virtual tmp<volTensorField> operator()
			(
				const tmp<volTensorField>&
				) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTurbulence_EXPORT void operator=(const simpleFilter&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_simpleFilter_Header
