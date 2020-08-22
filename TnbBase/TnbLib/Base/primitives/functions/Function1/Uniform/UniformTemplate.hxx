#pragma once
#ifndef _UniformTemplate_Header
#define _UniformTemplate_Header

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
	tnbLib::Function1Types::Uniform

Description
	Templated function that returns a constant value.

	Provides backward-compatibility for cases where a field is spatially
	"uniform" and may be treated as a constant value.

	Usage - for entry \<entryName\> returning the value <value>:
	\verbatim
		<entryName>    uniform  <value>
	\endverbatim

SourceFiles
	Uniform.C

\*---------------------------------------------------------------------------*/

//#include <Function1.hxx> disabled by amir
#include <Constant.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class Uniform Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class Uniform
			:
			public Constant<Type>
		{

		public:

			// Runtime type information
			TypeName("uniform");


			// Constructors

				//- Construct from entry name and dictionary
			Uniform(const word& entryName, const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const Uniform<Type>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <UniformTemplate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UniformTemplate_Header
