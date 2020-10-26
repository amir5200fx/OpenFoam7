#pragma once
#ifndef _SVD_Header
#define _SVD_Header

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
	tnbLib::SVD

Description
	Singular value decomposition of a rectangular matrix.

SourceFiles
	SVDI.H
	SVD.C

\*---------------------------------------------------------------------------*/

#include <scalarMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	/*---------------------------------------------------------------------------*\
						  Class SVD Declaration
	\*---------------------------------------------------------------------------*/

	class SVD
	{
		// Private Data

			//- Rectangular matrix with the same dimensions as the input
		scalarRectangularMatrix U_;

		//- Square matrix V
		scalarRectangularMatrix V_;

		//- The singular values
		DiagonalMatrix<scalar> S_;

		//- Convergence flag
		bool converged_;

		//- The number of zero singular values
		label nZeros_;


		// Private Member Functions

		template<class T>
		inline const T sign(const T& a, const T& b);


	public:

		// Constructors

			//- Construct from a rectangular Matrix
		FoamBase_EXPORT SVD(const scalarRectangularMatrix& A, const scalar minCondition = 0);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT SVD(const SVD&) = delete;


		// Access functions

			//- Return U
		inline const scalarRectangularMatrix& U() const;

		//- Return the square matrix V
		inline const scalarRectangularMatrix& V() const;

		//- Return the singular values
		inline const scalarDiagonalMatrix& S() const;

		//- Return the minimum non-zero singular value
		inline bool converged() const;

		//- Return the number of zero singular values
		inline label nZeros() const;

		//- Return the minimum non-zero singular value
		inline scalar minNonZeroS() const;

		//- Return the matrix product V S^(-1) U^T (the pseudo inverse)
		FoamBase_EXPORT scalarRectangularMatrix VSinvUt() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const SVD&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SVDI.hxx>

#endif // !_SVD_Header
