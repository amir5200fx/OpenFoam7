#pragma once
#ifndef _Giesekus_Header
#define _Giesekus_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::laminarModels::Giesekus

Description
	Giesekus model for viscoelasticity.

	Reference:
	\verbatim
		Giesekus, H., 1982.
		A simple constitutive equation for polymer fluids based on the
		concept of deformation-dependent tensional mobility.
		J. Non-Newton. Fluid. 11, 69�109.
	\endverbatim

See also
	tnbLib::laminarModels::Maxwell

SourceFiles
	Giesekus.C

\*---------------------------------------------------------------------------*/

#include <Maxwell.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamGiesekus_EXPORT __declspec(dllexport)
#else
#ifdef FoamGiesekus_EXPORT_DEFINE
#define FoamGiesekus_EXPORT __declspec(dllexport)
#else
#define FoamGiesekus_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		/*---------------------------------------------------------------------------*\
								   Class Giesekus Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class Giesekus
			:
			public Maxwell<BasicTurbulenceModel>
		{
		protected:

			// Protected data

				// Model coefficients

			dimensionedScalar alphaG_;


			// Protected Member Functions

			virtual tmp<fvSymmTensorMatrix> sigmaSource() const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("Giesekus");
			static const char* typeName_() { return "Giesekus"; }
			static FoamGiesekus_EXPORT const ::tnbLib::word typeName;
			static FoamGiesekus_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			Giesekus
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
			Giesekus(const Giesekus&) = delete;



			//- Destructor
			virtual ~Giesekus()
			{}


			// Member Functions

				//- Re-read model coefficients if they have changed
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const Giesekus&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GiesekusI.hxx>

//#ifdef NoRepository
//#include <Giesekus.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Giesekus_Header
