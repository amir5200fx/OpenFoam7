#pragma once
#ifndef _viewFactor_Header
#define _viewFactor_Header

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
	tnbLib::radiationModels::viewFactor

Description
	View factor radiation model. The system solved is: C q = b
	where:
			Cij  = deltaij/Ej - (1/Ej - 1)Fij
			q    = heat flux
			b    = A eb - Ho
	and:
			eb   = sigma*T^4
			Ej   = emissivity
			Aij  = deltaij - Fij
			Fij  = view factor matrix


SourceFiles
	viewFactor.C

\*---------------------------------------------------------------------------*/

#include <radiationModel.hxx>
#include <singleCellFvMesh.hxx>
#include <scalarMatrices.hxx>
#include <globalIndex.hxx>
#include <scalarListIOList.hxx>
#include <mapDistribute.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
								   Class viewFactor Declaration
		\*---------------------------------------------------------------------------*/

		class viewFactor
			:
			public radiationModel
		{
			// Private Data

				//- Agglomeration List
			labelListIOList finalAgglom_;

			//- Map distributed
			autoPtr<mapDistribute> map_;

			//- Coarse mesh
			singleCellFvMesh coarseMesh_;

			//- Net radiative heat flux [W/m^2]
			volScalarField qr_;

			//- View factor matrix
			autoPtr<scalarSquareMatrix> Fmatrix_;

			//- Inverse of C matrix
			autoPtr<scalarSquareMatrix> CLU_;

			//- Selected patches
			labelList selectedPatches_;

			//- Total global coarse faces
			label totalNCoarseFaces_;

			//- Total local coarse faces
			label nLocalCoarseFaces_;

			//- Constant emissivity
			bool constEmissivity_;

			//- Iterations Counter
			label iterCounter_;

			//- Pivot Indices for LU decomposition
			labelList pivotIndices_;


			// Private Member Functions

				//- Initialise
			FoamRadiationModels_EXPORT void initialise();

			//- Insert view factors into main matrix
			FoamRadiationModels_EXPORT void insertMatrixElements
			(
				const globalIndex& index,
				const label fromProci,
				const labelListList& globalFaceFaces,
				const scalarListList& viewFactors,
				scalarSquareMatrix& matrix
			);


		public:

			//- Runtime type information
			//TypeName("viewFactor");
			static const char* typeName_() { return "viewFactor"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamRadiationModels_EXPORT viewFactor(const volScalarField& T);

			//- Construct from components
			FoamRadiationModels_EXPORT viewFactor(const dictionary& dict, const volScalarField& T);

			//- Disallow default bitwise copy construction
			FoamRadiationModels_EXPORT viewFactor(const viewFactor&) = delete;


			//- Destructor
			FoamRadiationModels_EXPORT virtual ~viewFactor();


			// Member Functions

				// Edit

					//- Solve system of equation(s)
			FoamRadiationModels_EXPORT void calculate();

			//- Read radiation properties dictionary
			FoamRadiationModels_EXPORT bool read();

			//- Source term component (for power of T^4)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> Rp() const;

			//- Source term component (constant)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField::Internal> Ru() const;


			// Access

				//- Const access to total radiative heat flux field
			inline const volScalarField& qr() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamRadiationModels_EXPORT void operator=(const viewFactor&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <viewFactorI.hxx>

#endif // !_viewFactor_Header
