#pragma once
#ifndef _Barycentric2DTemplate_Header
#define _Barycentric2DTemplate_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	tnbLib::Barycentric2D

Description
	Templated 2D Barycentric derived from VectorSpace. Has 3 components, one of
	which is redundant.

SourceFiles
	Barycentric2DI.H

\*---------------------------------------------------------------------------*/

#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class Barycentric2D Declaration
	\*---------------------------------------------------------------------------*/

	template<class Cmpt>
	class Barycentric2D
		:
		public VectorSpace<Barycentric2D<Cmpt>, Cmpt, 3>
	{
	public:

		//- Equivalent type of labels used for valid component indexing
		typedef Barycentric2D<label> labelType;


		// Member constants

			//- Rank of Barycentric2D is 1
		static const direction rank = 1;


		//- Component labeling enumeration
		enum components { A, B, C };


		// Constructors

			//- Construct null
		inline Barycentric2D();

		//- Construct initialized to zero
		inline Barycentric2D(const tnbLib::zero);

		//- Construct given four components
		inline Barycentric2D
		(
			const Cmpt& va,
			const Cmpt& vb,
			const Cmpt& vc
		);


		// Member Functions

			// Access

		inline const Cmpt& a() const;
		inline const Cmpt& b() const;
		inline const Cmpt& c() const;

		inline Cmpt& a();
		inline Cmpt& b();
		inline Cmpt& c();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <Barycentric2DTemplateI.hxx>

#endif // !_Barycentric2DTemplate_Header
