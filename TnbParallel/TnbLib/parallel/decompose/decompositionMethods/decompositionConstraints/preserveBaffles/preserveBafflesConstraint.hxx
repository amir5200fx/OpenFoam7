#pragma once
#ifndef _preserveBafflesConstraint_Header
#define _preserveBafflesConstraint_Header

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
	tnbLib::decompositionConstraints::preserveBafflesConstraint

Description
	Detects baffles and keeps owner and neighbour on same processor.

SourceFiles
	preserveBafflesConstraint.C

\*---------------------------------------------------------------------------*/

#include <decompositionConstraint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace decompositionConstraints
	{

		/*---------------------------------------------------------------------------*\
						Class preserveBafflesConstraint Declaration
		\*---------------------------------------------------------------------------*/

		class preserveBafflesConstraint
			:
			public decompositionConstraint
		{
			// Private Data

		public:

			//- Runtime type information
			//TypeName("preserveBaffles");
			static const char* typeName_() { return "preserveBaffles"; }
			static FoamParallel_EXPORT const ::tnbLib::word typeName;
			static FoamParallel_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct with generic dictionary with optional entry for type
			FoamParallel_EXPORT preserveBafflesConstraint
			(
				const dictionary& constraintsDict,
				const word& type
			);

			//- Construct from components
			FoamParallel_EXPORT preserveBafflesConstraint();


			//- Destructor
			virtual ~preserveBafflesConstraint()
			{}


			// Member Functions

				//- Add my constraints to list of constraints
			FoamParallel_EXPORT virtual void add
			(
				const polyMesh& mesh,
				boolList& blockedFace,
				PtrList<labelList>& specifiedProcessorFaces,
				labelList& specifiedProcessor,
				List<labelPair>& explicitConnections
			) const;

			//- Apply any additional post-decomposition constraints
			FoamParallel_EXPORT virtual void apply
			(
				const polyMesh& mesh,
				const boolList& blockedFace,
				const PtrList<labelList>& specifiedProcessorFaces,
				const labelList& specifiedProcessor,
				const List<labelPair>& explicitConnections,
				labelList& decomposition
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace decompositionConstraints
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_preserveBafflesConstraint_Header
