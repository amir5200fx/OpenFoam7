#pragma once
#ifndef _SpalartAllmarasIDDES_Header
#define _SpalartAllmarasIDDES_Header

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
	tnbLib::LESModels::SpalartAllmarasIDDES

Description
	SpalartAllmaras IDDES turbulence model for incompressible and compressible
	flows

	Reference:
	\verbatim
		Shur, M. L., Spalart, P. R., Strelets, M. K., & Travin, A. K. (2008).
		A hybrid RANS-LES approach with delayed-DES and wall-modelled LES
		capabilities.
		International Journal of Heat and Fluid Flow, 29(6), 1638-1649.
	\endverbatim

SourceFiles
	SpalartAllmarasIDDES.C

\*---------------------------------------------------------------------------*/

#include <SpalartAllmarasDES.hxx>
#include <IDDESDelta.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamSpalartAllmarasIDDES_EXPORT __declspec(dllexport)
#else
#ifdef FoamSpalartAllmarasIDDES_EXPORT_DEFINE
#define FoamSpalartAllmarasIDDES_EXPORT __declspec(dllexport)
#else
#define FoamSpalartAllmarasIDDES_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								Class SpalartAllmarasIDDES Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class SpalartAllmarasIDDES
			:
			public SpalartAllmarasDES<BasicTurbulenceModel>
		{
			// Private Data

				// Model constants

			dimensionedScalar fwStar_;
			dimensionedScalar cl_;
			dimensionedScalar ct_;

			// Fields

			const IDDESDelta& IDDESDelta_;


			// Private Member Functions

			tmp<volScalarField> alpha() const;
			tmp<volScalarField> ft(const volScalarField& magGradU) const;
			tmp<volScalarField> fl(const volScalarField& magGradU) const;

			tmp<volScalarField> rd
			(
				const volScalarField& nur,
				const volScalarField& magGradU
			) const;

			//- Delay function
			tmp<volScalarField> fd(const volScalarField& magGradU) const;


		protected:

			// Protected Member Functions

				//- Length scale
			virtual tmp<volScalarField> dTilda
			(
				const volScalarField& chi,
				const volScalarField& fv1,
				const volTensorField& gradU
			) const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("SpalartAllmarasIDDES");
			static const char* typeName_() { return "SpalartAllmarasIDDES"; }
			static FoamSpalartAllmarasIDDES_EXPORT const ::tnbLib::word typeName;
			static FoamSpalartAllmarasIDDES_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			SpalartAllmarasIDDES
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
			SpalartAllmarasIDDES(const SpalartAllmarasIDDES&) = delete;


			//- Destructor
			virtual ~SpalartAllmarasIDDES()
			{}


			// Member Functions

				//- Read model coefficients if they have changed
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const SpalartAllmarasIDDES&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SpalartAllmarasIDDESI.hxx>

//#ifdef NoRepository
//#include <SpalartAllmarasIDDES.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SpalartAllmarasIDDES_Header
