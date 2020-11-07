#pragma once
#ifndef _CentredFitData_Header
#define _CentredFitData_Header

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
	tnbLib::CentredFitData

Description
	Data for the quadratic fit correction interpolation scheme

SourceFiles
	CentredFitData.C

\*---------------------------------------------------------------------------*/

#include <FitData.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCentredFitData_EXPORT __declspec(dllexport)
#else
#ifdef FoamCentredFitData_EXPORT_DEFINE
#define FoamCentredFitData_EXPORT __declspec(dllexport)
#else
#define FoamCentredFitData_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class extendedCentredCellToFaceStencil;

	/*---------------------------------------------------------------------------*\
						Class CentredFitData Declaration
	\*---------------------------------------------------------------------------*/

	template<class Polynomial>
	class CentredFitData
		:
		public FitData
		<
		CentredFitData<Polynomial>,
		extendedCentredCellToFaceStencil,
		Polynomial
		>
	{
		// Private Data

			//- For each cell in the mesh store the values which multiply the
			//  values of the stencil to obtain the gradient for each direction
		List<scalarList> coeffs_;


		// Private Member Functions

			//- Calculate the fit for the all the mesh faces
			//  and set the coefficients
		void calcFit();


	public:

		/*TypeName("CentredFitData");*/
		static const char* typeName_() { return "CentredFitData"; }
		static FoamCentredFitData_EXPORT const ::tnbLib::word typeName;
		static FoamCentredFitData_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		CentredFitData
		(
			const fvMesh& mesh,
			const extendedCentredCellToFaceStencil& stencil,
			const scalar linearLimitFactor,
			const scalar centralWeight
		);


		//- Destructor
		virtual ~CentredFitData()
		{}


		// Member Functions

			//- Return reference to fit coefficients
		const List<scalarList>& coeffs() const
		{
			return coeffs_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <CentredFitData.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CentredFitData_Header
