#pragma once
#ifndef _interRegionExplicitPorositySource_Header
#define _interRegionExplicitPorositySource_Header

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
	tnbLib::fv::interRegionExplicitPorositySource

Description
	Inter-region explicit porosity source.

	Sources described by, for example using the DarcyForchheimer model:

	\verbatim
	interRegionExplicitPorositySourceCoeffs
	{
		type            DarcyForchheimer;
		DarcyForchheimerCoeffs
		{
			d   d [0 -2 0 0 0 0 0] (5e7 -1000 -1000);
			f   f [0 -1 0 0 0 0 0] (0 0 0);

			coordinateSystem
			{
				e1  (0.70710678 0.70710678 0);
				e2  (0 0 1);
			}
		}
	}
	\endverbatim

Note
	The porous region must be selected as a cellZone.

SourceFiles
	interRegionExplicitPorositySource.C

\*---------------------------------------------------------------------------*/

#include <interRegionOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class porosityModel;

	namespace fv
	{


		/*---------------------------------------------------------------------------*\
						   Class interRegionExplicitPorositySource Declaration
		\*---------------------------------------------------------------------------*/

		class interRegionExplicitPorositySource
			:
			public interRegionOption
		{

		protected:

			// Protected data

				//- Run-time selectable porosity model
			autoPtr<porosityModel> porosityPtr_;

			//- First iteration
			bool firstIter_;

			//- Velocity field name, default = U
			word UName_;

			//- Dynamic viscosity field name (compressible case only)
			//  default = thermo:mu
			word muName_;


			// Protected Member Functions

				//- Initialise
			FoamFvOptions_EXPORT void initialise();


		public:

			//- Runtime type information
			//TypeName("interRegionExplicitPorositySource");
			static const char* typeName_() { return "interRegionExplicitPorositySource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT interRegionExplicitPorositySource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			FoamFvOptions_EXPORT interRegionExplicitPorositySource
			(
				const interRegionExplicitPorositySource&
			);


			//- Destructor
			virtual ~interRegionExplicitPorositySource()
			{}


			// Member Functions

				// Add explicit and implicit contributions

					//- Vector
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// Add explicit and implicit contributions to compressible equation

				//- Vector
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const interRegionExplicitPorositySource&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interRegionExplicitPorositySource_Header
