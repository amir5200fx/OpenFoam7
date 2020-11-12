#pragma once
#ifndef _pyrolysisModelCollection_Header
#define _pyrolysisModelCollection_Header

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
	tnbLib::regionModels::pyrolysisModels::pyrolysisModelCollection

Description
	A centralized pyrolysis collection.

	Container class for a set of pyrolysis with functions implemented
	to loop over the functions for each type.

SourceFiles
	pyrolysisModelCollection.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <pyrolysisModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	class fvMesh;

	namespace regionModels
	{
		namespace pyrolysisModels
		{

			/*---------------------------------------------------------------------------*\
							  Class pyrolysisModelCollection Declaration
			\*---------------------------------------------------------------------------*/

			class pyrolysisModelCollection
				:
				public PtrList<pyrolysisModel>
			{
			public:

				// Runtime type information
				//TypeName("pyrolysisModelCollection");
				static const char* typeName_() { return "pyrolysisModelCollection"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from mesh
				FoamLagrangian_EXPORT pyrolysisModelCollection(const fvMesh&);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT pyrolysisModelCollection(const pyrolysisModelCollection&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~pyrolysisModelCollection();


				// Member Functions

					//- Pre-evolve regions
				FoamLagrangian_EXPORT virtual void preEvolveRegion();

				//- Evolve the pyrolysis equation regions
				FoamLagrangian_EXPORT virtual void evolveRegion();

				//- Evolve regions
				FoamLagrangian_EXPORT virtual void evolve();

				//- Provide some feedback from pyrolysis regions
				FoamLagrangian_EXPORT virtual void info();

				//- Return max diffusivity allowed in the solid
				FoamLagrangian_EXPORT virtual scalar maxDiff() const;

				//- Mean diffusion number of the solid regions
				FoamLagrangian_EXPORT virtual scalar solidRegionDiffNo() const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const pyrolysisModelCollection&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib


#endif // !_pyrolysisModelCollection_Header
