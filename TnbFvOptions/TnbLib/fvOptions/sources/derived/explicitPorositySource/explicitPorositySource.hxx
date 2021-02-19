#pragma once
#ifndef _explicitPorositySource_Header
#define _explicitPorositySource_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fv::explicitPorositySource

Description
	Explicit porosity source

Usage
	Example usage, here employing the Darcy-Forchheimer model:
	\verbatim
	explicitPorositySourceCoeffs
	{
		type            DarcyForchheimer;

		DarcyForchheimerCoeffs
		{
			d   d [0 -2 0 0 0 0 0] (5e7 -1000 -1000);
			f   f [0 -1 0 0 0 0 0] (0 0 0);

			coordinateSystem
			{
				type    cartesian;
				origin  (0 0 0);
				coordinateRotation
				{
					type    axesRotation;
					e1  (0.70710678 0.70710678 0);
					e2  (0 0 1);
				}
			}
		}
	}
	\endverbatim

Note:
	The porous region must be selected as a cellZone.

SourceFiles
	explicitPorositySource.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class porosityModel;

	namespace fv
	{


		/*---------------------------------------------------------------------------*\
						   Class explicitPorositySource Declaration
		\*---------------------------------------------------------------------------*/

		class explicitPorositySource
			:
			public cellSetOption
		{
		protected:

			// Protected data

				//- Run-time selectable porosity model
			autoPtr<porosityModel> porosityPtr_;


		public:

			//- Runtime type information
			//TypeName("explicitPorositySource");
			static const char* typeName_() { return "explicitPorositySource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT explicitPorositySource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			explicitPorositySource(const explicitPorositySource&) = delete;


			//- Destructor
			virtual ~explicitPorositySource()
			{}


			// Member Functions

			const porosityModel& model() const
			{
				return porosityPtr_();
			}

			// Add explicit and implicit contributions

				//- Add implicit contribution to momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Add implicit contribution to compressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Add implicit contribution to phase momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const explicitPorositySource&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_explicitPorositySource_Header
