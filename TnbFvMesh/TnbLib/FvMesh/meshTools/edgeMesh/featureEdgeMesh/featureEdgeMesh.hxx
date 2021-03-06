#pragma once
#ifndef _featureEdgeMesh_Header
#define _featureEdgeMesh_Header

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
	tnbLib::featureEdgeMesh

Description
	edgeMesh + IO.

See also
	tnbLib::extendedFeatureEdgeMesh

SourceFiles
	featureEdgeMesh.C

\*---------------------------------------------------------------------------*/

#include <edgeMesh.hxx>
#include <regIOobject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class featureEdgeMesh Declaration
	\*---------------------------------------------------------------------------*/

	class featureEdgeMesh
		:
		public regIOobject,
		public edgeMesh
	{

	public:

		/*TypeName("featureEdgeMesh");*/
		static const char* typeName_() { return "featureEdgeMesh"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct (read) given an IOobject
		FoamFvMesh_EXPORT featureEdgeMesh(const IOobject&);

		//- Construct from featureEdgeMesh data
		FoamFvMesh_EXPORT featureEdgeMesh
		(
			const IOobject&,
			const pointField&,
			const edgeList&
		);

		//- Copy constructor
		FoamFvMesh_EXPORT featureEdgeMesh(const IOobject&, const featureEdgeMesh&);


		// IO

			//- ReadData function required for regIOobject read operation
		FoamFvMesh_EXPORT virtual bool readData(Istream&);

		//- WriteData function required for regIOobject write operation
		FoamFvMesh_EXPORT virtual bool writeData(Ostream&) const;

		//- Is object global
		virtual bool global() const
		{
			return true;
		}

		//- Return complete path + object name if the file exists
		//  either in the case/processor or case otherwise null
		virtual fileName filePath() const
		{
			return globalFilePath(type());
		}
	};


	//- Template function for obtaining global status
	template<>
	inline bool typeGlobal<featureEdgeMesh>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_featureEdgeMesh_Header
