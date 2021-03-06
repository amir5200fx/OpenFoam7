#pragma once
#ifndef _cyclicAMIGAMGInterfaceField_Header
#define _cyclicAMIGAMGInterfaceField_Header

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
	tnbLib::cyclicAMIGAMGInterfaceField

Description
	GAMG agglomerated cyclic interface field.

SourceFiles
	cyclicAMIGAMGInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <GAMGInterfaceField.hxx>
#include <cyclicAMIGAMGInterface.hxx>
#include <cyclicAMILduInterfaceField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class cyclicAMIGAMGInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicAMIGAMGInterfaceField
		:
		public GAMGInterfaceField,
		public cyclicAMILduInterfaceField
	{
		// Private Data

			//- Local reference cast into the cyclic interface
		const cyclicAMIGAMGInterface& cyclicAMIInterface_;

		//- Is the transform required
		bool doTransform_;

		//- Rank of component for transformation
		int rank_;


	public:

		//- Runtime type information
		//TypeName("cyclicAMI");
		static const char* typeName_() { return "cyclicAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from GAMG interface and fine level interface field
		FoamFvMesh_EXPORT cyclicAMIGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField& fineInterfaceField
		);

		//- Construct from GAMG interface and fine level interface field
		FoamFvMesh_EXPORT cyclicAMIGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT cyclicAMIGAMGInterfaceField
		(
			const cyclicAMIGAMGInterfaceField&
		) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicAMIGAMGInterfaceField();


		// Member Functions

			// Access

				//- Return size
		label size() const
		{
			return cyclicAMIInterface_.size();
		}


		// Interface matrix update

			//- Update result field based on interface functionality
		FoamFvMesh_EXPORT virtual void updateInterfaceMatrix
		(
			scalarField& result,
			const scalarField& psiInternal,
			const scalarField& coeffs,
			const direction cmpt,
			const Pstream::commsTypes commsType
		) const;


		//- Cyclic interface functions

			//- Does the interface field perform the transformation
		virtual bool doTransform() const
		{
			return doTransform_;
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return cyclicAMIInterface_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return cyclicAMIInterface_.reverseT();
		}

		//- Return rank of component for transform
		virtual int rank() const
		{
			return rank_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const cyclicAMIGAMGInterfaceField&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMIGAMGInterfaceField_Header
