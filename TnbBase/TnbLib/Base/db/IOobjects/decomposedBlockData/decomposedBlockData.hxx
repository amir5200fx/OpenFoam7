#pragma once
#ifndef _decomposedBlockData_Header
#define _decomposedBlockData_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::decomposedBlockData

Description
	decomposedBlockData is a List<char> with IO on the master processor only.

SourceFiles
	decomposedBlockData.C

\*---------------------------------------------------------------------------*/

#include <IOList.hxx>
#include <regIOobject.hxx>
#include <UPstream.hxx>

#include <PtrList.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class decomposedBlockData Declaration
	\*---------------------------------------------------------------------------*/

	class decomposedBlockData
		:
		public regIOobject,
		public List<char>
	{
	protected:

		// Protected data

			//- Type to use for gather
		const UPstream::commsTypes commsType_;

		//- Communicator for all parallel comms
		const label comm_;


		// Protected member functions

			//- Helper: determine number of processors whose recvSizes fits
			//  ito maxBufferSize
		static FoamBase_EXPORT label calcNumProcs
		(
			const label comm,
			const off_t maxBufferSize,
			const labelUList& recvSizes,
			const label startProci
		);

		//- Read data into *this. ISstream is only valid on master.
		static FoamBase_EXPORT bool readBlocks
		(
			const label comm,
			autoPtr<ISstream>& isPtr,
			List<char>& data,
			const UPstream::commsTypes commsType
		);


	public:

		//TypeName("decomposedBlockData");
		static const char* typeName_() { return "decomposedBlockData"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given an IOobject
		FoamBase_EXPORT decomposedBlockData
		(
			const label comm,
			const IOobject&,
			const UPstream::commsTypes = UPstream::commsTypes::scheduled
		);

		//- Construct given an IOobject and for READ_IF_MODIFIED a List<char>
		FoamBase_EXPORT decomposedBlockData
		(
			const label comm,
			const IOobject&,
			const UList<char>&,
			const UPstream::commsTypes = UPstream::commsTypes::scheduled
		);

		//- Move construct by transferring the IOList contents
		FoamBase_EXPORT decomposedBlockData
		(
			const label comm,
			const IOobject&,
			List<char>&&,
			const UPstream::commsTypes = UPstream::commsTypes::scheduled
		);


		//- Destructor
		FoamBase_EXPORT virtual ~decomposedBlockData();


		// Member Functions

			//- Read object
		FoamBase_EXPORT virtual bool read();

		//- Write separated content. Assumes content is the serialised data
		//  and that the master data contains a header
		FoamBase_EXPORT virtual bool writeData(Ostream&) const;

		//- Write using given format, version and compression
		FoamBase_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat,
			IOstream::versionNumber,
			IOstream::compressionType,
			const bool write
		) const;


		// Helpers

			//- Read header. Call only on master.
		static FoamBase_EXPORT bool readMasterHeader(IOobject&, Istream&);

		//- Helper: write FoamFile IOobject header
		static FoamBase_EXPORT void writeHeader
		(
			Ostream& os,
			const IOstream::versionNumber version,
			const IOstream::streamFormat format,
			const word& type,
			const string& note,
			const fileName& location,
			const word& name
		);

		//- Read selected block (non-seeking) + header information
		static FoamBase_EXPORT autoPtr<ISstream> readBlock
		(
			const label blocki,
			Istream& is,
			IOobject& headerIO
		);

		//- Read master header information (into headerIO) and return
		//  data in stream. Note: isPtr is only valid on master.
		static FoamBase_EXPORT autoPtr<ISstream> readBlocks
		(
			const label comm,
			const fileName& fName,
			autoPtr<ISstream>& isPtr,
			IOobject& headerIO,
			const UPstream::commsTypes commsType
		);

		//- Helper: gather single label. Note: using native Pstream.
		//  datas sized with num procs but undefined contents on
		//  slaves
		static FoamBase_EXPORT void gather
		(
			const label comm,
			const label data,
			labelList& datas
		);

		//- Helper: gather data from (subset of) slaves. Returns
		//  recvData : received data
		//  recvOffsets : offset in data. recvOffsets is nProcs+1
		static FoamBase_EXPORT void gatherSlaveData
		(
			const label comm,
			const UList<char>& data,
			const labelUList& recvSizes,

			const label startProc,
			const label nProcs,

			List<int>& recvOffsets,
			List<char>& recvData
		);

		//- Write *this. Ostream only valid on master. Returns starts of
		//  processor blocks
		static FoamBase_EXPORT bool writeBlocks
		(
			const label comm,
			autoPtr<OSstream>& osPtr,
			List<std::streamoff>& start,
			const UList<char>& masterData,

			const labelUList& recvSizes,

			// optional slave data (on master)
			const PtrList<SubList<char>>& slaveData,

			const UPstream::commsTypes,
			const bool syncReturnState = true
		);

		//- Detect number of blocks in a file
		static FoamBase_EXPORT label numBlocks(const fileName&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_decomposedBlockData_Header
