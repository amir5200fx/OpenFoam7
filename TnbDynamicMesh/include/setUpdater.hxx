#pragma once
#ifndef _setUpdater_Header
#define _setUpdater_Header

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
	tnbLib::setUpdater

Description
	Keeps cell/face/vertex sets uptodate. Both the ones loaded and the ones
	on disk.

SourceFiles
	setUpdater.C
	setUpdaterTemplates.C

\*---------------------------------------------------------------------------*/

#include <polyMeshModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class setUpdater Declaration
	\*---------------------------------------------------------------------------*/

	class setUpdater
		:
		public polyMeshModifier
	{
		// Private Member Functions

			//- Updates all sets
		template<class Type>
		void updateSets(const mapPolyMesh& morphMap) const;


	public:

		//- Runtime type information
		//TypeName("setUpdater");
		static const char* typeName_() { return "setUpdater"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		FoamDynamicMesh_EXPORT setUpdater
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyTopoChanger& mme
		);

		//- Disallow default bitwise copy construction
		setUpdater(const setUpdater&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~setUpdater();


		// Member Functions

			//- Check for topology change
		FoamDynamicMesh_EXPORT virtual bool changeTopology() const;

		//- Insert the layer addition/removal instructions
		//  into the topological change
		FoamDynamicMesh_EXPORT virtual void setRefinement(polyTopoChange&) const;

		//- Modify motion points to comply with the topological change
		FoamDynamicMesh_EXPORT virtual void modifyMotionPoints(pointField& motionPoints) const;

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);

		//- Write
		FoamDynamicMesh_EXPORT virtual void write(Ostream&) const;

		//- Write dictionary
		FoamDynamicMesh_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const setUpdater&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <setUpdaterI.hxx>

//#ifdef NoRepository
//#include <setUpdaterTemplates.cxx>
//#endif

#endif // !_setUpdater_Header
