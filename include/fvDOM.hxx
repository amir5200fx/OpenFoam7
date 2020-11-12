#pragma once
#ifndef _fvDOM_Header
#define _fvDOM_Header

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
	tnbLib::radiationModels::fvDOM

Description

	Finite Volume Discrete Ordinates Method. Solves the RTE equation for n
	directions in a participating media, not including scatter.

	Available absorption models:
		constantAbsorptionEmission
		greyMeanAbsoprtionEmission
		wideBandAbsorptionEmission

	i.e. dictionary
	\verbatim
		fvDOMCoeffs
		{
			nPhi        4;          // azimuthal angles in PI/2 on X-Y.
									//(from Y to X)
			nTheta      0;          // polar angles in PI (from Z to X-Y plane)
			convergence 1e-3;       // convergence criteria for radiation
									// iteration
			maxIter     4;          // maximum number of iterations
		}

		solverFreq   1; // Number of flow iterations per radiation iteration
	\endverbatim

	In 1-D the ray directions are bound to one of the X, Y or Z directions. The
	total number of solid angles is 2. nPhi and nTheta are ignored.

	In 2-D the ray directions are within one of the X-Y, X-Z or Y-Z planes. The
	total number of solid angles is 4*nPhi. nTheta is ignored.

	In 3D the rays span all directions. The total number of solid angles is
	4*nPhi*nTheta.

SourceFiles
	fvDOM.C

\*---------------------------------------------------------------------------*/

#include <radiativeIntensityRay.hxx>
#include <radiationModel.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
								   Class fvDOM Declaration
		\*---------------------------------------------------------------------------*/

		class fvDOM
			:
			public radiationModel
		{
			// Private Data


				//- Incident radiation  [W/m^2]
			volScalarField G_;

			//- Total radiative heat flux [W/m^2]
			volScalarField qr_;

			//- Emitted radiative heat flux [W/m^2]
			volScalarField qem_;

			//- Incidet radiative heat flux [W/m^2]
			volScalarField qin_;

			//- Total absorption coefficient [1/m]
			volScalarField a_;

			//- Number of solid angles in theta
			label nTheta_;

			//- Number of solid angles in phi
			label nPhi_;

			//- Total number of rays (1 per direction)
			label nRay_;

			//- Number of wavelength bands
			label nLambda_;

			//- Wavelength total absorption coefficient [1/m]
			PtrList<volScalarField> aLambda_;

			//- Black body
			blackBodyEmission blackBody_;

			//- List of pointers to radiative intensity rays
			PtrList<radiativeIntensityRay> IRay_;

			//- Convergence tolerance
			scalar tolerance_;

			//- Maximum number of iterations
			label maxIter_;

			//- Maximum omega weight
			scalar omegaMax_;


			// Private Member Functions

				//- Initialise
			FoamRadiationModels_EXPORT void initialise();

			//- Update nlack body emission
			FoamRadiationModels_EXPORT void updateBlackBodyEmission();


		public:

			//- Runtime type information
			//TypeName("fvDOM");
			static const char* typeName_() { return "fvDOM"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamRadiationModels_EXPORT fvDOM(const volScalarField& T);

			//- Construct from components
			FoamRadiationModels_EXPORT fvDOM(const dictionary& dict, const volScalarField& T);

			//- Disallow default bitwise copy construction
			FoamRadiationModels_EXPORT fvDOM(const fvDOM&) = delete;


			//- Destructor
			FoamRadiationModels_EXPORT virtual ~fvDOM();


			// Member Functions

				// Edit

					//- Solve radiation equation(s)
			FoamRadiationModels_EXPORT void calculate();

			//- Read radiation properties dictionary
			FoamRadiationModels_EXPORT bool read();

			//- Update G and calculate total heat flux on boundary
			FoamRadiationModels_EXPORT void updateG();

			//- Set the rayId and lambdaId from by decomposing an intensity
			//  field name
			FoamRadiationModels_EXPORT void setRayIdLambdaId
			(
				const word& name,
				label& rayId,
				label& lambdaId
			) const;

			//- Source term component (for power of T^4)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> Rp() const;

			//- Source term component (constant)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField::Internal> Ru() const;


			// Access

				//- Ray intensity for rayI
			inline const radiativeIntensityRay& IRay(const label rayI) const;

			//- Ray intensity for rayI and lambda bandwidth
			inline const volScalarField& IRayLambda
			(
				const label rayI,
				const label lambdaI
			) const;

			//- Number of angles in theta
			inline label nTheta() const;

			//- Number of angles in phi
			inline label nPhi() const;

			//- Number of rays
			inline label nRay() const;

			//- Number of wavelengths
			inline label nLambda() const;

			//- Const access to total absorption coefficient
			inline const volScalarField& a() const;

			//- Const access to wavelength total absorption coefficient
			inline const volScalarField& aLambda(const label lambdaI) const;

			//- Const access to incident radiation field
			inline const volScalarField& G() const;

			//- Const access to total radiative heat flux field
			inline const volScalarField& qr() const;

			//- Const access to incident radiative heat flux field
			inline const volScalarField& qin() const;

			//- Const access to emitted radiative heat flux field
			inline const volScalarField& qem() const;

			//- Const access to black body
			inline const blackBodyEmission& blackBody() const;

			//- Return omegaMax
			inline scalar omegaMax() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamRadiationModels_EXPORT void operator=(const fvDOM&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvDOMI.hxx>

#endif // !_fvDOM_Header
