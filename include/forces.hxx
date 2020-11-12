#pragma once
#ifndef _forces_Header
#define _forces_Header

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
	tnbLib::functionObjects::forces

Description
	Calculates the forces and moments by integrating the pressure and
	skin-friction forces over a given list of patches.

	Member function forces::write() calculates the forces/moments and
	writes the forces/moments into the file \<timeDir\>/forces.dat and bin
	data (if selected) to the file \<timeDir\>/forces_bin.dat

	Example of function object specification:
	\verbatim
	forces1
	{
		type        forces;
		libs        ("libforces.so");
		...
		log         yes;
		patches     (walls);

		binData
		{
			nBin        20;
			direction   (1 0 0);
			cumulative  yes;
		}
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required    | Default value
		type         | Type name: forces       | yes         |
		log          | Write force data to standard output | no | no
		patches      | Patches included in the forces calculation | yes |
		p            | Pressure field name     | no          | p
		U            | Velocity field name     | no          | U
		rho          | Density field name (see below) | no   | rho
		CofR         | Centre of rotation (see below) | no   |
		directForceDensity | Force density supplied directly (see below)|no|no
		fD           | Name of force density field (see below) | no | fD
	\endtable

	Bin data is optional, but if the dictionary is present, the entries must
	be defined according o
	\table
		nBin         | number of data bins     | yes         |
		direction    | direction along which bins are defined | yes |
		cumulative   | bin data accumulated with incresing distance | yes |
	\endtable

Note
  - For incompressible cases, set \c rho to \c rhoInf.  You will then be
	required to provide a \c rhoInf value corresponding to the free-stream
	constant density.
  - If the force density is supplied directly, set the \c directForceDensity
	flag to 'yes', and supply the force density field using the \c
	fDName entry
  - The centre of rotation (CofR) for moment calculations can either be
	specified by an \c CofR entry, or be taken from origin of the local
	coordinate system.  For example,
	\verbatim
		CofR        (0 0 0);
	\endverbatim
	or
	\verbatim
		coordinateSystem
		{
			origin  (0 0 0);
			e3      (0 0 1);
			e1      (1 0 0);
		}
	\endverbatim

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::timeControl
	tnbLib::forceCoeffs

SourceFiles
	forces.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <coordinateSystem.hxx>
#include <volFieldsFwd.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								   Class forces Declaration
		\*---------------------------------------------------------------------------*/

		class forces
			:
			public fvMeshFunctionObject,
			public logFiles
		{

		protected:

			// Protected data

				//- Enumeration for ensuring the right file is accessed
			enum class fileID
			{
				mainFile = 0,
				binsFile = 1
			};

			//- Pressure, viscous and porous force per bin
			List<Field<vector>> force_;

			//- Pressure, viscous and porous moment per bin
			List<Field<vector>> moment_;


			// Read from dictionary

				//- Patches to integrate forces over
			labelHashSet patchSet_;

			//- Name of pressure field
			word pName_;

			//- Name of velocity field
			word UName_;

			//- Name of density field (optional)
			word rhoName_;

			//- Is the force density being supplied directly?
			Switch directForceDensity_;

			//- The name of the force density (fD) field
			word fDName_;

			//- Reference density needed for incompressible calculations
			scalar rhoRef_;

			//- Reference pressure
			scalar pRef_;

			//- Coordinate system used when evaluating forces/moments
			coordinateSystem coordSys_;

			//- Flag to indicate whether we are using a local co-ordinate sys
			bool localSystem_;

			//- Flag to include porosity effects
			bool porosity_;


			// Bin information

				//- Number of bins
			label nBin_;

			//- Direction used to determine bin orientation
			vector binDir_;

			//- Distance between bin divisions
			scalar binDx_;

			//- Minimum bin bounds
			scalar binMin_;

			//- Bin positions along binDir
			List<point> binPoints_;

			//- Should bin data be cumulative?
			bool binCumulative_;


			//- Initialised flag
			bool initialised_;


			// Protected Member Functions

			using logFiles::file;

			Ostream& file(const fileID fid)
			{
				return logFiles::file(label(fid));
			}

			//- Create file names for forces and bins
			FoamFunctionObjects_EXPORT wordList createFileNames(const dictionary& dict) const;

			//- Output file header information
			FoamFunctionObjects_EXPORT virtual void writeFileHeader(const label i);

			//- Initialise the fields
			FoamFunctionObjects_EXPORT void initialise();

			//- Return the effective viscous stress (laminar + turbulent).
			FoamFunctionObjects_EXPORT tmp<volSymmTensorField> devRhoReff() const;

			//- Dynamic viscosity field
			FoamFunctionObjects_EXPORT tmp<volScalarField> mu() const;

			//- Return rho if specified otherwise rhoRef
			FoamFunctionObjects_EXPORT tmp<volScalarField> rho() const;

			//- Return rhoRef if the pressure field is dynamic, i.e. p/rho
			//  otherwise return 1
			FoamFunctionObjects_EXPORT scalar rho(const volScalarField& p) const;

			//- Accumulate bin data
			FoamFunctionObjects_EXPORT void applyBins
			(
				const vectorField& Md,
				const vectorField& fN,
				const vectorField& fT,
				const vectorField& fP,
				const vectorField& d
			);

			//- Helper function to write force data
			FoamFunctionObjects_EXPORT void writeForces();

			//- Helper function to write bin data
			FoamFunctionObjects_EXPORT void writeBins();


		public:

			//- Runtime type information
			//TypeName("forces");
			static const char* typeName_() { return "forces"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT forces
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Construct from objectRegistry and dictionary
			FoamFunctionObjects_EXPORT forces
			(
				const word& name,
				const objectRegistry& obr,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT forces(const forces&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~forces();


			// Member Functions

				//- Read the forces data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the forces and moments
			FoamFunctionObjects_EXPORT virtual void calcForcesMoment();

			//- Return the total force
			FoamFunctionObjects_EXPORT virtual vector forceEff() const;

			//- Return the total moment
			FoamFunctionObjects_EXPORT virtual vector momentEff() const;

			//- Execute, currently does nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the forces
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const forces&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_forces_Header
