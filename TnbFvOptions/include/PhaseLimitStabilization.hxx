#pragma once
#ifndef _PhaseLimitStabilization_Header
#define _PhaseLimitStabilization_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::fv::PhaseLimitStabilization

Description
	Stabilization source for phase transport equations

	Applies an implicit source to the phase transport equation for the specified
	\c field when the phase volume fraction is below \c residualAlpha.  The
	stabilization rate is provided by the registered
	uniformDimensionedScalarField \c rate, which could be extended to also
	support volScalarField and volScalarField::Internal field types.  The \c
	field is currently stabilized towards zero in the limit of the phase volume
	fraction approaching zero but this could be extended to support a
	specified value or a value or field looked-up from the database.

Usage
	Example usage:
	\verbatim
	stabilization
	{
		type            symmTensorPhaseLimitStabilization;

		field           sigma.liquid;
		rate            rLambda.liquid;
		residualAlpha   1e-3;
	}
	\endverbatim

SourceFiles
	PhaseLimitStabilization.C

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						Class PhaseLimitStabilization Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class PhaseLimitStabilization
			:
			public option
		{
			// Private Data

				//- Field name
			word fieldName_;

			//- Rate field name
			word rateName_;

			//- Residual alpha value below which stabilization is applied
			scalar residualAlpha_;


		public:

			//- Runtime type information
			//TypeName("PhaseLimitStabilization");
			static const char* typeName_() { return "PhaseLimitStabilization"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT PhaseLimitStabilization
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			PhaseLimitStabilization(const PhaseLimitStabilization&) = delete;


			//- Destructor
			virtual ~PhaseLimitStabilization()
			{}


			// Member Functions

				//- Source term to compressible phase equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<Type>& eqn,
				const label fieldi
			);

			//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const PhaseLimitStabilization&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <PhaseLimitStabilization.cxx>
//#endif

#include <PhaseLimitStabilization_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PhaseLimitStabilization_Header
