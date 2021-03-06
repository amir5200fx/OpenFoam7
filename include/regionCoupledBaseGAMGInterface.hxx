#pragma once
#ifndef _regionCoupledBaseGAMGInterface_Header
#define _regionCoupledBaseGAMGInterface_Header

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
	tnbLib::regionCoupledBaseGAMGInterface

Description
	Base class for GAMG agglomerated coupled region interface.

SourceFiles
	regionCoupledBaseGAMGInterface.C

\*---------------------------------------------------------------------------*/

#include <GAMGInterface.hxx>
#include <regionCoupledLduInterface.hxx>
#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class regionCoupledBaseGAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledBaseGAMGInterface
		:
		public GAMGInterface,
		virtual public regionCoupledLduInterface
	{
		// Private Data

			//- Reference for the regionCoupledBaseFvPatch from which this is
			//  agglomerated
		const regionCoupledLduInterface& fineRegionCoupledLduInterface_;


	public:


		// Constructors

			//- Construct from fine level interface,
			//  local and neighbour restrict addressing
		FoamFvMesh_EXPORT regionCoupledBaseGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const lduInterface& fineInterface,
			const labelField& restrictAddressing,
			const labelField& neighbourRestrictAddressing,
			const label fineLevelIndex,
			const label coarseComm
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT regionCoupledBaseGAMGInterface
		(
			const regionCoupledBaseGAMGInterface&
		) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~regionCoupledBaseGAMGInterface();


		// Member Functions

			// Interface transfer functions

				//- Transfer and return internal field adjacent to the interface
		FoamFvMesh_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const;


		//- Cyclic interface functions

			//- Return neighbour processor number
		virtual label neighbPatchID() const
		{
			return fineRegionCoupledLduInterface_.neighbPatchID();
		}

		virtual bool owner() const
		{
			return fineRegionCoupledLduInterface_.owner();
		}

		virtual const regionCoupledBaseGAMGInterface& neighbPatch() const
		{
			return dynamic_cast<const regionCoupledBaseGAMGInterface&>
				(
					fineRegionCoupledLduInterface_.neighbPatch()
					);
		}

		// virtual const AMIInterpolation& AMI() const
		//{
		//    return amiPtr_();
		//}

		virtual const polyMesh& nbrMesh() const
		{
			return fineRegionCoupledLduInterface_.nbrMesh();
		}

		const lduInterface& nbrLduInterface
		(
			const label fineLevelIndex,
			const label index
		) const
		{
			const GAMGAgglomeration& agg = nbrMesh().thisDb().lookupObject
				<
				GAMGAgglomeration
				>
				(
					GAMGAgglomeration::typeName
					);

			const lduMesh& mesh = agg.meshLevel(fineLevelIndex);
			return mesh.interfaces()[index];
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const regionCoupledBaseGAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledBaseGAMGInterface_Header
