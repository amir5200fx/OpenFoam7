#pragma once
#ifndef _tabulatedAccelerationSource_Header
#define _tabulatedAccelerationSource_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::fv::tabulatedAccelerationSource

Description
	Solid-body 6-DoF acceleration source

Usage
	Example usage:
	\verbatim
	SBM
	{
		type            tabulatedAccelerationSource;
		active          yes;

		timeDataFileName "constant/acceleration-terms.dat";
	}
	\endverbatim

SourceFiles
	tabulatedAccelerationSource.C

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>
#include <tabulated6DoFAcceleration.hxx>
#include <dimensionedTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								  Class tabulatedAccelerationSource Declaration
		\*---------------------------------------------------------------------------*/

		class tabulatedAccelerationSource
			:
			public option
		{

		protected:

			// Protected data

				//- Run-time selectable acceleration model
			tabulated6DoFAcceleration motion_;

			//- Velocity field name, default = U
			word UName_;

			dimensionedVector g0_;

		private:

			// Private Member Functions

				//- Source term to momentum equation
			template<class RhoFieldType>
			void addSup
			(
				const RhoFieldType& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


		public:

			//- Runtime type information
			//TypeName("tabulatedAccelerationSource");
			static const char* typeName_() { return "tabulatedAccelerationSource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT tabulatedAccelerationSource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			tabulatedAccelerationSource
			(
				const tabulatedAccelerationSource&
			) = delete;


			//- Destructor
			virtual ~tabulatedAccelerationSource()
			{}


			// Member Functions

				//- Source term to momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Source term to compressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const tabulatedAccelerationSource&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <tabulatedAccelerationSourceTemplates.cxx>
//#endif

#include <tabulatedAccelerationSourceTemplatesI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tabulatedAccelerationSource_Header
