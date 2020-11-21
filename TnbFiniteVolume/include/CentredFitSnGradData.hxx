#pragma once
#ifndef _CentredFitSnGradData_Header
#define _CentredFitSnGradData_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::CentredFitSnGradData

Description
	Data for centred fit snGrad schemes

SourceFiles
	CentredFitSnGradData.C

\*---------------------------------------------------------------------------*/

#include <FitData.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCentredFitSnGradData_EXPORT __declspec(dllexport)
#else
#ifdef FoamCentredFitSnGradData_EXPORT_DEFINE
#define FoamCentredFitSnGradData_EXPORT __declspec(dllexport)
#else
#define FoamCentredFitSnGradData_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class extendedCentredCellToFaceStencil;

	/*---------------------------------------------------------------------------*\
						Class CentredFitSnGradData Declaration
	\*---------------------------------------------------------------------------*/

	template<class Polynomial>
	class CentredFitSnGradData
		:
		public FitData
		<
		CentredFitSnGradData<Polynomial>,
		extendedCentredCellToFaceStencil,
		Polynomial
		>
	{
		// Private Data

			//- For each cell in the mesh store the values which multiply the
			//  values of the stencil to obtain the gradient for each direction
		List<scalarList> coeffs_;


	public:

		/*TypeName("CentredFitSnGradData");*/
		static const char* typeName_() { return "CentredFitSnGradData"; }
		static FoamCentredFitSnGradData_EXPORT const ::tnbLib::word typeName;
		static FoamCentredFitSnGradData_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		CentredFitSnGradData
		(
			const fvMesh& mesh,
			const extendedCentredCellToFaceStencil& stencil,
			const scalar linearLimitFactor,
			const scalar centralWeight
		);


		//- Destructor
		virtual ~CentredFitSnGradData()
		{}


		// Member Functions

			//- Return reference to fit coefficients
		const List<scalarList>& coeffs() const
		{
			return coeffs_;
		}

		//- Calculate the fit for the specified face and set the coefficients
		void calcFit
		(
			scalarList& coeffsi, // coefficients to be set
			const List<point>&,  // Stencil points
			const scalar wLin,   // Weight for linear approximation (weights
								 // nearest neighbours)
			const scalar deltaCoeff, // uncorrected delta coefficient
			const label faci     // Current face index
		);

		void calcFit();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CentredFitSnGradDataI.hxx>

//#ifdef NoRepository
//#include <CentredFitSnGradData.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CentredFitSnGradData_Header
