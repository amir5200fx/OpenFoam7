#pragma once
#ifndef _procLduMatrix_Header
#define _procLduMatrix_Header

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
	tnbLib::procLduMatrix

Description
	I/O for lduMatrix and interface values.

SourceFiles
	procLduMatrix.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <scalarList.hxx>
#include <FieldField.hxx>
#include <lduInterfaceFieldPtrsList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class procLduInterface;
	class lduMatrix;

	// Forward declaration of friend functions and operators

	class procLduMatrix;

	FoamBase_EXPORT Ostream& operator<<(Ostream&, const procLduMatrix&);


	/*---------------------------------------------------------------------------*\
							   Class procLduMatrix Declaration
	\*---------------------------------------------------------------------------*/

	class procLduMatrix
	{
		// Private Data

		labelList upperAddr_;
		labelList lowerAddr_;
		scalarField diag_;
		scalarField upper_;
		scalarField lower_;
		PtrList<procLduInterface> interfaces_;


		// Private Member Functions

			//- Dissallow construction as copy
		FoamBase_EXPORT procLduMatrix(const procLduMatrix&);


	public:

		friend class LUscalarMatrix;


		// Constructors

		FoamBase_EXPORT procLduMatrix
		(
			const lduMatrix& ldum,
			const FieldField<Field, scalar>& interfaceCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);

		FoamBase_EXPORT procLduMatrix(Istream& is);


		// Member Functions

		label size() const
		{
			return diag_.size();
		}


		// Ostream operator

		friend Ostream& operator<<(Ostream&, const procLduMatrix&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_procLduMatrix_Header
