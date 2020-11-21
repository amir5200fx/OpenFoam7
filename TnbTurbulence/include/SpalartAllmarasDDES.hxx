#pragma once
#ifndef _SpalartAllmarasDDES_Header
#define _SpalartAllmarasDDES_Header

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
	tnbLib::LESModels::SpalartAllmarasDDES

Description
	SpalartAllmaras DDES turbulence model for incompressible and compressible
	flows

	Reference:
	\verbatim
		Spalart, P. R., Deck, S., Shur, M. L., Squires, K. D., Strelets, M. K.,
		& Travin, A. (2006).
		A new version of detached-eddy simulation, resistant to ambiguous grid
		densities.
		Theoretical and computational fluid dynamics, 20(3), 181-195.
	\endverbatim

SourceFiles
	SpalartAllmarasDDES.C

\*---------------------------------------------------------------------------*/

#include <SpalartAllmarasDES.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamSpalartAllmarasDDES_EXPORT __declspec(dllexport)
#else
#ifdef FoamSpalartAllmarasDDES_EXPORT_DEFINE
#define FoamSpalartAllmarasDDES_EXPORT __declspec(dllexport)
#else
#define FoamSpalartAllmarasDDES_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
							 Class SpalartAllmarasDDES Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class SpalartAllmarasDDES
			:
			public SpalartAllmarasDES<BasicTurbulenceModel>
		{
			// Private Member Functions

			tmp<volScalarField> fd(const volScalarField& magGradU) const;

			tmp<volScalarField> rd(const volScalarField& magGradU) const;


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
			//TypeName("SpalartAllmarasDDES");
			static const char* typeName_() { return "SpalartAllmarasDDES"; }
			static FoamSpalartAllmarasDDES_EXPORT const ::tnbLib::word typeName;
			static FoamSpalartAllmarasDDES_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			SpalartAllmarasDDES
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
			SpalartAllmarasDDES(const SpalartAllmarasDDES&) = delete;


			//- Destructor
			virtual ~SpalartAllmarasDDES()
			{}


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const SpalartAllmarasDDES&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SpalartAllmarasDDESI.hxx>

//#ifdef NoRepository
//#include <SpalartAllmarasDDES.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SpalartAllmarasDDES_Header
