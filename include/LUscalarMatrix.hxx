#pragma once
#ifndef _LUscalarMatrix_Header
#define _LUscalarMatrix_Header

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
	tnbLib::LUscalarMatrix

Description
	Class to perform the LU decomposition on a symmetric matrix.

SourceFiles
	LUscalarMatrix.C

\*---------------------------------------------------------------------------*/

#include <scalarMatrices.hxx>
#include <labelList.hxx>
#include <FieldField.hxx>
#include <lduInterfaceFieldPtrsList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class lduMatrix;
	class procLduMatrix;

	/*---------------------------------------------------------------------------*\
							   Class LUscalarMatrix Declaration
	\*---------------------------------------------------------------------------*/

	class LUscalarMatrix
		:
		public scalarSquareMatrix
	{
		// Private Data

			//- Communicator to use
		const label comm_;

		//- Processor matrix offsets
		labelList procOffsets_;

		//- The pivot indices used in the LU decomposition
		labelList pivotIndices_;


		// Private Member Functions

			//- Convert the given lduMatrix into this LUscalarMatrix
		FoamBase_EXPORT void convert
		(
			const lduMatrix& ldum,
			const FieldField<Field, scalar>& interfaceCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);

		//- Convert the given list of procLduMatrix into this LUscalarMatrix
		//  on the master processor
		FoamBase_EXPORT void convert(const PtrList<procLduMatrix>& lduMatrices);


		//- Print the ratio of the mag-sum of the off-diagonal coefficients
		//  to the mag-diagonal
		FoamBase_EXPORT void printDiagonalDominance() const;


	public:

		// Declare name of the class and its debug switch
		// ClassName("LUscalarMatrix");
		static const char* typeName_() { return "LUscalarMatrix"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct null
		FoamBase_EXPORT LUscalarMatrix();

		//- Construct from and perform LU decomposition of the matrix M
		FoamBase_EXPORT LUscalarMatrix(const scalarSquareMatrix& M);

		//- Construct from lduMatrix and perform LU decomposition
		FoamBase_EXPORT LUscalarMatrix
		(
			const lduMatrix&,
			const FieldField<Field, scalar>& interfaceCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);


		// Member Functions

			//- Perform the LU decomposition of the matrix M
		FoamBase_EXPORT void decompose(const scalarSquareMatrix& M);

		//- Solve the linear system with the given source
		//  and returning the solution in the Field argument x.
		//  This function may be called with the same field for x and source.
		template<class Type>
		void solve(Field<Type>& x, const Field<Type>& source) const;

		//- Solve the linear system with the given source
		//  returning the solution
		template<class Type>
		tmp<Field<Type>> solve(const Field<Type>& source) const;

		//- Set M to the inverse of this square matrix
		FoamBase_EXPORT void inv(scalarSquareMatrix& M) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LUscalarMatrixTemplatesI.hxx>

//#ifdef NoRepository
//#include <LUscalarMatrixTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LUscalarMatrix_Header
