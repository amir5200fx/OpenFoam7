#pragma once
#ifndef _SphericalTensorTemplate_Header
#define _SphericalTensorTemplate_Header

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
	tnbLib::SphericalTensor

Description
	Templated 3D SphericalTensor derived from VectorSpace adding construction
	from 1 component, element access using th ii() member function and the
	inner-product (dot-product) and outer-product operators.

SourceFiles
	SphericalTensorI.H

\*---------------------------------------------------------------------------*/

#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class SphericalTensor Declaration
	\*---------------------------------------------------------------------------*/

	template<class Cmpt>
	class SphericalTensor
		:
		public VectorSpace<SphericalTensor<Cmpt>, Cmpt, 1>
	{

	public:

		//- Equivalent type of labels used for valid component indexing
		typedef SphericalTensor<label> labelType;


		// Member constants

			//- Rank of SphericalTensor is 2
		static const direction rank = 2;


		// Static Data Members

		static const SphericalTensor I;
		static const SphericalTensor oneThirdI;
		static const SphericalTensor twoThirdsI;


		//- Component labeling enumeration
		enum components { II };


		// Constructors

			//- Construct null
		inline SphericalTensor();

		//- Construct initialized to zero
		inline SphericalTensor(const tnbLib::zero);

		//- Construct given VectorSpace
		template<class Cmpt2>
		inline SphericalTensor
		(
			const VectorSpace<SphericalTensor<Cmpt2>, Cmpt2, 1>&
		);

		//- Construct given the component
		inline SphericalTensor(const Cmpt& tii);

		//- Construct from Istream
		inline SphericalTensor(Istream&);


		// Member Functions

			// Access

		inline const Cmpt& ii() const;
		inline Cmpt& ii();


		//- Transpose
		inline const SphericalTensor<Cmpt>& T() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SphericalTensorTemplateI.hxx>

#endif // !_SphericalTensorTemplate_Header
