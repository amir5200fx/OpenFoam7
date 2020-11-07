#pragma once
#ifndef _processorFvPatch_Header
#define _processorFvPatch_Header

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
	tnbLib::processorFvPatch

Description
	Processor patch.

SourceFiles
	processorFvPatch.C

\*---------------------------------------------------------------------------*/


#include <coupledFvPatch.hxx>
#include <processorLduInterface.hxx>
#include <processorPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class processorFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class processorFvPatch
		:
		public coupledFvPatch,
		public processorLduInterface
	{
		// Private Data

		const processorPolyPatch& procPolyPatch_;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		FoamFiniteVolume_EXPORT void makeWeights(scalarField&) const;


	public:

		//- Runtime type information
		/*TypeName(processorPolyPatch::typeName_());*/
		static const char* typeName_() { return processorPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		processorFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			coupledFvPatch(patch, bm),
			procPolyPatch_(refCast<const processorPolyPatch>(patch))
		{}


		// Member Functions

			//- Return communicator used for comms
		virtual label comm() const
		{
			return procPolyPatch_.comm();
		}

		//- Return processor number
		virtual int myProcNo() const
		{
			return procPolyPatch_.myProcNo();
		}

		//- Return neighbour processor number
		virtual int neighbProcNo() const
		{
			return procPolyPatch_.neighbProcNo();
		}

		//- Return message tag used for sending
		virtual int tag() const
		{
			return UPstream::msgType();
		}

		//- Return true if running parallel
		virtual bool coupled() const
		{
			if (Pstream::parRun())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		const processorPolyPatch& procPolyPatch() const
		{
			return procPolyPatch_;
		}

		//- Are the cyclic planes parallel
		virtual bool parallel() const
		{
			return procPolyPatch_.parallel();
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return procPolyPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor.
		virtual const tensorField& reverseT() const
		{
			return procPolyPatch_.reverseT();
		}

		//- Return delta (P to N) vectors across coupled patch
		FoamFiniteVolume_EXPORT virtual tmp<vectorField> delta() const;


		// Interface transfer functions

			//- Return the values of the given internal data adjacent to
			//  the interface as a field
		FoamFiniteVolume_EXPORT virtual tmp<labelField> interfaceInternalField
		(
			const labelUList& internalData
		) const;

		//- Inherit initInternalFieldTransfer from coupledFvPatch
		using coupledFvPatch::initInternalFieldTransfer;

		//- Initialise neighbour field transfer
		FoamFiniteVolume_EXPORT virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& internalData
		) const;

		//- Return neighbour field
		FoamFiniteVolume_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& internalData
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorFvPatch_Header
