#pragma once
#ifndef _mapDistributeBase_Header
#define _mapDistributeBase_Header

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
	tnbLib::mapDistributeBase

Description
	Class containing processor-to-processor mapping information.

	We store mapping from the bits-to-send to the complete starting list
	(subXXXMap) and from the received bits to their location in the new
	list (constructXXXMap).

Note:
	Schedule is a list of processor pairs (one send, one receive. One of
	them will be myself) which forms a scheduled (i.e. non-buffered) exchange.
	See distribute on how to use it.
	Note2: number of items sent on one processor have to equal the number
	of items received on the other processor.

	To aid constructing these maps there are the constructors from global
	numbering, either with or without transforms.

	Constructors using compact numbering: layout is
	- all my own elements first (whether used or not)
	- followed by used-only remote elements sorted by remote processor.
	So e.g 4 procs and on proc 1 the compact
	table will first have all globalIndex.localSize() elements from proc1
	followed by used-only elements of proc0, proc2, proc3.
	The constructed mapDistributeBase sends the local elements from and
	receives the remote elements into their compact position.
	compactMap[proci] is the position of elements from proci in the compact
	map. compactMap[myProcNo()] is empty since trivial addressing.

	It rewrites the input global indices into indices into the constructed
	data.

	When constructing from components optionally a 'flip' on
	the maps can be specified. This will interpret the map
	values as index+flip, similar to e.g. faceProcAddressing. The flip
	will only be applied to fieldTypes (scalar, vector, .. triad)


SourceFiles
	mapDistributeBase.C
	mapDistributeBaseTemplates.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <labelPair.hxx>
#include <Pstream.hxx>
#include <boolList.hxx>
#include <Map.hxx>

#include <globalIndex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapPolyMesh;
	class globalIndex;
	class PstreamBuffers;


	// Forward declaration of friend functions and operators

	class mapDistributeBase;

	FoamBase_EXPORT Istream& operator>>(Istream&, mapDistributeBase&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const mapDistributeBase&);


	/*---------------------------------------------------------------------------*\
							   Class mapDistributeBase Declaration
	\*---------------------------------------------------------------------------*/

	class mapDistributeBase
	{
	protected:

		// Protected data

			//- Size of reconstructed data
		label constructSize_;

		//- Maps from subsetted data back to original data
		labelListList subMap_;

		//- Maps from subsetted data to new reconstructed data
		labelListList constructMap_;

		//- Whether subMap includes flip or not
		bool subHasFlip_;

		//- Whether constructMap includes flip or not
		bool constructHasFlip_;


		//- Schedule
		mutable autoPtr<List<labelPair>> schedulePtr_;


		// Private Member Functions

		static FoamBase_EXPORT void checkReceivedSize
		(
			const label proci,
			const label expectedSize,
			const label receivedSize
		);

		//- Construct per processor compact addressing of the global elements
		//  needed. The ones from the local processor are not included since
		//  these are always all needed.
		FoamBase_EXPORT void calcCompactAddressing
		(
			const globalIndex& globalNumbering,
			const labelList& elements,
			List<Map<label>>& compactMap
		) const;

		FoamBase_EXPORT void calcCompactAddressing
		(
			const globalIndex& globalNumbering,
			const labelListList& elements,
			List<Map<label>>& compactMap
		) const;

		FoamBase_EXPORT void exchangeAddressing
		(
			const int tag,
			const globalIndex& globalNumbering,
			labelList& elements,
			List<Map<label>>& compactMap,
			labelList& compactStart
		);
		FoamBase_EXPORT void exchangeAddressing
		(
			const int tag,
			const globalIndex& globalNumbering,
			labelListList& elements,
			List<Map<label>>& compactMap,
			labelList& compactStart
		);

		template<class T, class CombineOp, class negateOp>
		static void flipAndCombine
		(
			const UList<label>& map,
			const bool hasFlip,
			const UList<T>& rhs,
			const CombineOp& cop,
			const negateOp& negOp,
			List<T>& lhs
		);

		template<class T, class negateOp>
		static T accessAndFlip
		(
			const UList<T>& fld,
			const label index,
			const bool hasFlip,
			const negateOp& negOp
		);

	public:

		// Declare name of the class and its debug switch
		//ClassName("mapDistributeBase");
		static const char* typeName_() { return "mapDistributeBase"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct null
		FoamBase_EXPORT mapDistributeBase();

		//- Move construct from components
		FoamBase_EXPORT mapDistributeBase
		(
			const label constructSize,
			const labelListList&& subMap,
			const labelListList&& constructMap,
			const bool subHasFlip = false,
			const bool constructHasFlip = false
		);

		//- Construct from reverse addressing: per data item the send
		//  processor and the receive processor. (note: data is not stored
		//  sorted per processor so cannot use printLayout).
		FoamBase_EXPORT mapDistributeBase
		(
			const labelList& sendProcs,
			const labelList& recvProcs
		);

		//- Construct from list of (possibly) remote elements in globalIndex
		//  numbering (or -1). Determines compact numbering (see above) and
		//  distribute map to get data into this ordering and renumbers the
		//  elements to be in compact numbering.
		FoamBase_EXPORT mapDistributeBase
		(
			const globalIndex&,
			labelList& elements,
			List<Map<label>>& compactMap,
			const int tag = Pstream::msgType()
		);

		//- Special variant that works with the info sorted into bins
		//  according to local indices. E.g. think cellCells where
		//  cellCells[localCellI] is a list of global cells
		FoamBase_EXPORT mapDistributeBase
		(
			const globalIndex&,
			labelListList& cellCells,
			List<Map<label>>& compactMap,
			const int tag = Pstream::msgType()
		);

		//- Construct copy
		FoamBase_EXPORT mapDistributeBase(const mapDistributeBase&);

		//- Move constructor
		FoamBase_EXPORT mapDistributeBase(mapDistributeBase&&);

		//- Construct from Istream
		FoamBase_EXPORT mapDistributeBase(Istream&);


		// Member Functions

			// Access

				//- Constructed data size
		label constructSize() const
		{
			return constructSize_;
		}

		//- Constructed data size
		label& constructSize()
		{
			return constructSize_;
		}

		//- From subsetted data back to original data
		const labelListList& subMap() const
		{
			return subMap_;
		}

		//- From subsetted data back to original data
		labelListList& subMap()
		{
			return subMap_;
		}

		//- From subsetted data to new reconstructed data
		const labelListList& constructMap() const
		{
			return constructMap_;
		}

		//- From subsetted data to new reconstructed data
		labelListList& constructMap()
		{
			return constructMap_;
		}

		//- Does subMap include a sign
		bool subHasFlip() const
		{
			return subHasFlip_;
		}

		//- Does subMap include a sign
		bool& subHasFlip()
		{
			return subHasFlip_;
		}

		//- Does constructMap include a sign
		bool constructHasFlip() const
		{
			return constructHasFlip_;
		}

		//- Does constructMap include a sign
		bool& constructHasFlip()
		{
			return constructHasFlip_;
		}

		//- Calculate a schedule. See above.
		static FoamBase_EXPORT List<labelPair> schedule
		(
			const labelListList& subMap,
			const labelListList& constructMap,
			const int tag
		);

		//- Return a schedule. Demand driven. See above.
		FoamBase_EXPORT const List<labelPair>& schedule() const;


		// Other

			//- Transfer the contents of the argument and annul the argument.
		FoamBase_EXPORT void transfer(mapDistributeBase&);

		//- Helper for construct from globalIndex. Renumbers element
		//  (in globalIndex numbering) into compact indices.
		static FoamBase_EXPORT label renumber
		(
			const globalIndex&,
			const List<Map<label>>& compactMap,
			const label globalElement
		);

		//- Compact maps. Gets per field a bool whether it is used (locally)
		//  and works out itself what this side and sender side can remove
		//  from maps. Only compacts non-local elements (i.e. the stuff
		//  that gets sent over), does not change the local layout
		FoamBase_EXPORT void compact
		(
			const boolList& elemIsUsed,
			const int tag = UPstream::msgType()
		);

		//- Compact all maps and layout. Returns compaction maps for
		//  subMap and constructMap
		FoamBase_EXPORT void compact
		(
			const boolList& elemIsUsed,
			const label localSize,            // max index for subMap
			labelList& oldToNewSub,
			labelList& oldToNewConstruct,
			const int tag = UPstream::msgType()
		);

		//- Distribute data. Note:schedule only used for
		//  Pstream::commsTypes::scheduled for now, all others just use
		//  send-to-all, receive-from-all.
		template<class T, class negateOp>
		static void distribute
		(
			const Pstream::commsTypes commsType,
			const List<labelPair>& schedule,
			const label constructSize,
			const labelListList& subMap,
			const bool subHasFlip,
			const labelListList& constructMap,
			const bool constructHasFlip,
			List<T>&,
			const negateOp& negOp,
			const int tag = UPstream::msgType()
		);

		//- Distribute data. If multiple processors writing to same
		//  position adds contributions using cop.
		template<class T, class CombineOp, class negateOp>
		static void distribute
		(
			const Pstream::commsTypes commsType,
			const List<labelPair>& schedule,
			const label constructSize,
			const labelListList& subMap,
			const bool subHasFlip,
			const labelListList& constructMap,
			const bool constructHasFlip,
			List<T>&,
			const CombineOp& cop,
			const negateOp& negOp,
			const T& nullValue,
			const int tag = UPstream::msgType()
		);

		//- Distribute data using default commsType.
		template<class T>
		void distribute
		(
			List<T>& fld,
			const int tag = UPstream::msgType()
		) const;

		//- Distribute data using default commsType.
		template<class T, class negateOp>
		void distribute
		(
			List<T>& fld,
			const negateOp& negOp,
			const int tag = UPstream::msgType()
		) const;

		//- Distribute data using default commsType.
		template<class T>
		void distribute
		(
			DynamicList<T>& fld,
			const int tag = UPstream::msgType()
		) const;

		//- Reverse distribute data using default commsType.
		template<class T>
		void reverseDistribute
		(
			const label constructSize,
			List<T>&,
			const int tag = UPstream::msgType()
		) const;

		//- Reverse distribute data using default commsType.
		//  Since constructSize might be larger than supplied size supply
		//  a nullValue
		template<class T>
		void reverseDistribute
		(
			const label constructSize,
			const T& nullValue,
			List<T>& fld,
			const int tag = UPstream::msgType()
		) const;

		//- Do all sends using PstreamBuffers
		template<class T>
		void send(PstreamBuffers&, const List<T>&) const;
		//- Do all receives using PstreamBuffers
		template<class T>
		void receive(PstreamBuffers&, List<T>&) const;

		//- Debug: print layout. Can only be used on maps with sorted
		//  storage (local data first, then non-local data)
		FoamBase_EXPORT void printLayout(Ostream& os) const;

		//- Correct for topo change.
		void updateMesh(const mapPolyMesh&)
		{
			NotImplemented;
		}


		// Member Operators

		FoamBase_EXPORT void operator=(const mapDistributeBase&);
		FoamBase_EXPORT void operator=(mapDistributeBase&&);


		// IOstream Operators

			//- Read dictionary from Istream
		friend FoamBase_EXPORT Istream& operator>>(Istream&, mapDistributeBase&);

		//- Write dictionary to Ostream
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const mapDistributeBase&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <mapDistributeBaseTemplatesI.hxx>

//#ifdef NoRepository
//#include <mapDistributeBaseTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mapDistributeBase_Header
