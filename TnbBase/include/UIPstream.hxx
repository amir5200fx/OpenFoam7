#pragma once
#ifndef _UIPstream_Header
#define _UIPstream_Header

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
	tnbLib::UIPstream

Description
	Input inter-processor communications stream operating on external
	buffer.

SourceFiles
	UIPstream.C

\*---------------------------------------------------------------------------*/

#include <UPstream.hxx>
#include <Istream.hxx>
#include <PstreamBuffers.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class UIPstream Declaration
	\*---------------------------------------------------------------------------*/

	class UIPstream
		:
		public UPstream,
		public Istream
	{
		// Private Data

		int fromProcNo_;

		DynamicList<char>& externalBuf_;

		label& externalBufPosition_;

		const int tag_;

		const label comm_;

		const bool clearAtEnd_;

		int messageSize_;


		// Private Member Functions

			//- Check the bufferPosition against messageSize_ for EOF
		inline void checkEof();

		//- Read a T from the transfer buffer
		template<class T>
		inline void readFromBuffer(T&);

		//- Read data from the transfer buffer
		inline void readFromBuffer(void* data, size_t count, size_t align);


	public:

		// Constructors

			//- Construct given process index to read from and optional buffer size,
			//  read format and IO version
		FoamBase_EXPORT UIPstream
		(
			const commsTypes commsType,
			const int fromProcNo,
			DynamicList<char>& externalBuf,
			label& externalBufPosition,
			const int tag = UPstream::msgType(),
			const label comm = UPstream::worldComm,
			const bool clearAtEnd = false,   // destroy externalBuf if at end
			streamFormat format = BINARY,
			versionNumber version = currentVersion
		);

		//- Construct given buffers
		FoamBase_EXPORT UIPstream(const int fromProcNo, PstreamBuffers&);


		//- Destructor
		FoamBase_EXPORT ~UIPstream();


		// Member Functions

			// Inquiry

				//- Return flags of output stream
		ios_base::fmtflags flags() const
		{
			return ios_base::fmtflags(0);
		}


		// Read functions

			//- Read into given buffer from given processor and return the
			//  message size
		static FoamBase_EXPORT label read
		(
			const commsTypes commsType,
			const int fromProcNo,
			char* buf,
			const std::streamsize bufSize,
			const int tag = UPstream::msgType(),
			const label communicator = 0
		);

		//- Return next token from stream
		FoamBase_EXPORT Istream& read(token&);

		//- Read a character
		FoamBase_EXPORT Istream& read(char&);

		//- Read a word
		FoamBase_EXPORT Istream& read(word&);

		// Read a string (including enclosing double-quotes)
		FoamBase_EXPORT Istream& read(string&);

		//- Read a label
		FoamBase_EXPORT Istream& read(label&);

		//- Read a floatScalar
		FoamBase_EXPORT Istream& read(floatScalar&);

		//- Read a doubleScalar
		FoamBase_EXPORT Istream& read(doubleScalar&);

		//- Read a longDoubleScalar
		FoamBase_EXPORT Istream& read(longDoubleScalar&);

		//- Read binary block
		FoamBase_EXPORT Istream& read(char*, std::streamsize);

		//- Rewind and return the stream so that it may be read again
		FoamBase_EXPORT Istream& rewind();


		// Edit

			//- Set flags of stream
		ios_base::fmtflags flags(const ios_base::fmtflags)
		{
			return ios_base::fmtflags(0);
		}


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT void print(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UIPstream_Header
