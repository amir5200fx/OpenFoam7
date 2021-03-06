#pragma once
#ifndef _attachDetach_Header
#define _attachDetach_Header

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
	tnbLib::attachDetach

Description
	Attach/detach boundary mesh modifier.  This modifier takes a set of
	internal faces and converts them into boundary faces and vice versa
	based on the given activation switch.

	The patch is oriented using the flip map in the face zone.  The
	oriented faces are put into the master patch and their mirror
	images into the slave.

SourceFiles
	attachDetach.C
	attachInterface.C
	detachInterface.C
	attachDetachPointMatchMap.C

\*---------------------------------------------------------------------------*/

#include <polyMeshModifier.hxx>
#include <polyPatchID.hxx>
#include <ZoneIDs.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class attachDetach Declaration
	\*---------------------------------------------------------------------------*/

	class attachDetach
		:
		public polyMeshModifier
	{
		// Data types

			//- State of the modifier
		enum modifierState
		{
			UNKNOWN,
			ATTACHED,
			DETACHED
		};


		// Private Data

			//- Master face zone ID
		faceZoneID faceZoneID_;

		//- Master patch ID.  Holds faces with original orientation
		polyPatchID masterPatchID_;

		//- Slave patch ID.  Holds mirrored faces
		polyPatchID slavePatchID_;

		//- List of trigger times
		scalarField triggerTimes_;

		//- Use manual trigger
		Switch manualTrigger_;

		//- Trigger time index
		mutable label triggerIndex_;

		//- State of the modifier
		mutable modifierState state_;

		//- Attach/detach trigger
		mutable bool trigger_;


		// Private addressing data.  Created on topology change

			//- Map of matching points
		mutable Map<label>* pointMatchMapPtr_;


		// Private Member Functions

			//- Check validity of construction data
		FoamDynamicMesh_EXPORT void checkDefinition();

		// Topological changes

			//- Attach interface
		FoamDynamicMesh_EXPORT void attachInterface(polyTopoChange&) const;

		//- Detach interface
		FoamDynamicMesh_EXPORT void detachInterface(polyTopoChange&) const;

		//- Calculate point match addressing
		FoamDynamicMesh_EXPORT void calcPointMatchMap() const;

		//- Return point match map
		FoamDynamicMesh_EXPORT const Map<label>& pointMatchMap() const;

		//- Clear addressing
		FoamDynamicMesh_EXPORT void clearAddressing() const;


		// Static Data Members

			//- Relative vertex position tolerance
		static FoamDynamicMesh_EXPORT const scalar positionDifference_;


	public:

		//- Runtime type information
		//TypeName("attachDetach");
		static const char* typeName_() { return "attachDetach"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamDynamicMesh_EXPORT attachDetach
		(
			const word& name,
			const label index,
			const polyTopoChanger& mme,
			const word& faceZoneName,
			const word& masterPatchName,
			const word& slavePatchName,
			const scalarField& triggerTimes,
			const bool manualTrigger = false
		);

		//- Construct from dictionary
		FoamDynamicMesh_EXPORT attachDetach
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyTopoChanger& mesh
		);

		//- Disallow default bitwise copy construction
		attachDetach(const attachDetach&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~attachDetach();


		// Member Functions

			//- Return master patch ID
		const polyPatchID& masterPatchID() const
		{
			return masterPatchID_;
		}

		//- Return slave patch ID
		const polyPatchID& slavePatchID() const
		{
			return slavePatchID_;
		}

		//- Is the interface attached?
		bool attached() const
		{
			return state_ == ATTACHED;
		}

		const Switch& manualTrigger() const
		{
			return manualTrigger_;
		}

		// Manually set attach.  Use only with manual trigger
		FoamDynamicMesh_EXPORT bool setAttach() const;

		// Manually set detach.  Use only with manual trigger
		FoamDynamicMesh_EXPORT bool setDetach() const;

		//- Check for topology change
		FoamDynamicMesh_EXPORT virtual bool changeTopology() const;

		//- Insert the layer addition/removal instructions
		//  into the topological change
		FoamDynamicMesh_EXPORT virtual void setRefinement(polyTopoChange&) const;

		//- Modify motion points to comply with the topological change
		FoamDynamicMesh_EXPORT virtual void modifyMotionPoints(pointField& motionPoints) const;

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);

		//- Get reference to trigger times
		const scalarField& triggerTimes() const
		{
			return triggerTimes_;
		}

		//- Write
		FoamDynamicMesh_EXPORT virtual void write(Ostream&) const;

		//- Write dictionary
		FoamDynamicMesh_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const attachDetach&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_attachDetach_Header
