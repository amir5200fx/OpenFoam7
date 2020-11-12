#pragma once
#ifndef _SpalartAllmarasDES_Header
#define _SpalartAllmarasDES_Header

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
	tnbLib::LESModels::SpalartAllmarasDES

Description
	SpalartAllmarasDES DES turbulence model for incompressible and
	compressible flows

	Reference:
	\verbatim
		Spalart, P. R., Jou, W. H., Strelets, M., & Allmaras, S. R. (1997).
		Comments on the feasibility of LES for wings, and on a hybrid
		RANS/LES approach.
		Advances in DNS/LES, 1, 4-8.
	\endverbatim

SourceFiles
	SpalartAllmarasDES.C

\*---------------------------------------------------------------------------*/

#include <LESeddyViscosity.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamSpalartAllmarasDES_EXPORT __declspec(dllexport)
#else
#ifdef FoamSpalartAllmarasDES_EXPORT_DEFINE
#define FoamSpalartAllmarasDES_EXPORT __declspec(dllexport)
#else
#define FoamSpalartAllmarasDES_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								Class SpalartAllmarasDES Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class SpalartAllmarasDES
			:
			public LESeddyViscosity<BasicTurbulenceModel>
		{
		protected:

			// Protected data

				// Model constants

			dimensionedScalar sigmaNut_;
			dimensionedScalar kappa_;

			dimensionedScalar Cb1_;
			dimensionedScalar Cb2_;
			dimensionedScalar Cw1_;
			dimensionedScalar Cw2_;
			dimensionedScalar Cw3_;
			dimensionedScalar Cv1_;
			dimensionedScalar Cs_;
			dimensionedScalar CDES_;
			dimensionedScalar ck_;

			// Fields

			volScalarField nuTilda_;

			//- Wall distance
			//  Note: different to wall distance in parent RASModel
			//  which is for near-wall cells only
			const volScalarField& y_;


			// Protected Member Functions

			tmp<volScalarField> chi() const;

			tmp<volScalarField> fv1(const volScalarField& chi) const;

			tmp<volScalarField> fv2
			(
				const volScalarField& chi,
				const volScalarField& fv1
			) const;

			tmp<volScalarField> S(const volTensorField& gradU) const;

			tmp<volScalarField> Omega(const volTensorField& gradU) const;

			tmp<volScalarField> Stilda
			(
				const volScalarField& chi,
				const volScalarField& fv1,
				const volScalarField& Omega,
				const volScalarField& dTilda
			) const;

			tmp<volScalarField> r
			(
				const volScalarField& nur,
				const volScalarField& Omega,
				const volScalarField& dTilda
			) const;

			tmp<volScalarField> fw
			(
				const volScalarField& Omega,
				const volScalarField& dTilda
			) const;

			//- Length scale
			virtual tmp<volScalarField> dTilda
			(
				const volScalarField& chi,
				const volScalarField& fv1,
				const volTensorField& gradU
			) const;

			void correctNut(const volScalarField& fv1);
			virtual void correctNut();


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("SpalartAllmarasDES");
			static const char* typeName_() { return "SpalartAllmarasDES"; }
			static FoamSpalartAllmarasDES_EXPORT const ::tnbLib::word typeName;
			static FoamSpalartAllmarasDES_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			SpalartAllmarasDES
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName,
				const word& type = typeName
			);

			//- Disallow default bitwise copy construction
			SpalartAllmarasDES(const SpalartAllmarasDES&) = delete;


			//- Destructor
			virtual ~SpalartAllmarasDES()
			{}


			// Member Functions

				//- Read model coefficients if they have changed
			virtual bool read();

			//- Return the effective diffusivity for nuTilda
			tmp<volScalarField> DnuTildaEff() const;

			//- Return SGS kinetic energy
			virtual tmp<volScalarField> k() const;

			tmp<volScalarField> nuTilda() const
			{
				return nuTilda_;
			}

			//- Return the LES field indicator
			virtual tmp<volScalarField> LESRegion() const;

			//- Correct nuTilda and related properties
			virtual void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const SpalartAllmarasDES&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SpalartAllmarasDESI.hxx>

//#ifdef NoRepository
//#include <SpalartAllmarasDES.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SpalartAllmarasDES_Header
