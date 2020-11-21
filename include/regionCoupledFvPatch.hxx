#pragma once
#ifndef _regionCoupledFvPatch_Header
#define _regionCoupledFvPatch_Header

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
	tnbLib::regionCoupledFvPatch

Description
	Common functionality for regionCoupleFvPatch and regionCoupledWallFvPatch

SourceFiles
	regionCoupledFvPatch.C

\*---------------------------------------------------------------------------*/

#include <fvPatch.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>
#include <regionCoupledPolyPatch.hxx>
#include <regionCoupledBaseFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class regionCoupledFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledFvPatch
		:
		public lduInterface,
		public fvPatch,
		public regionCoupledBaseFvPatch
	{
		// Private Data

		const regionCoupledPolyPatch& regionCoupledPolyPatch_;

		// Private members

			//- Return regionCoupledFvPatch nbr
		const regionCoupledFvPatch& neighbFvPatch() const
		{
			return refCast<const regionCoupledFvPatch>
				(
					nbrFvMesh().boundary()
					[
						neighbPatchID()
					]
			);
		}


	public:

		//- Runtime type information
		/*TypeName(regionCoupledPolyPatch::typeName_());*/
		static const char* typeName_() { return regionCoupledPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from polyPatch
		regionCoupledFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm),
			regionCoupledBaseFvPatch
			(
				patch,
				*this
			),
			regionCoupledPolyPatch_
			(
				refCast<const regionCoupledPolyPatch>(patch)
			)
		{}


		//- Destructor
		~regionCoupledFvPatch()
		{}


		// Member Functions


		// Access

		//- Return faceCell addressing
		virtual const labelUList& faceCells() const
		{
			return fvPatch::faceCells();
		}

		//- Return true because this patch is coupled
		virtual bool coupled() const
		{
			return regionCoupledPolyPatch_.coupled();
		}


		// Interface transfer functions

		//- Return the values of the given internal data adjacent to
		//  the interface as a field
		FoamFiniteVolume_EXPORT virtual tmp<labelField> interfaceInternalField
		(
			const labelUList& internalData
		) const;

		//- Inherit initInternalFieldTransfer from lduInterface
		using lduInterface::initInternalFieldTransfer;

		//- Initialise neighbour field transfer
		virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			labelUList& iF
		) const
		{}

		//- Return neighbour field
		FoamFiniteVolume_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledFvPatch_Header
