#pragma once
#ifndef _layerAdditionRemoval_Header
#define _layerAdditionRemoval_Header

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
	tnbLib::layerAdditionRemoval

Description
	Cell layer addition mesh modifier

SourceFiles
	layerAdditionRemoval.C
	addCellLayer.C
	removeCellLayer.C

\*---------------------------------------------------------------------------*/

#include <polyMeshModifier.hxx>
#include <primitiveFacePatch.hxx>
#include <ZoneIDs.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class layerAdditionRemoval Declaration
	\*---------------------------------------------------------------------------*/

	class layerAdditionRemoval
		:
		public polyMeshModifier
	{
		// Private Data

			//- Master face zone ID
		faceZoneID faceZoneID_;

		//- Min thickness of extrusion layer.  Triggers layer removal
		mutable scalar minLayerThickness_;

		//- Max thickness of extrusion layer.  Triggers layer addition
		mutable scalar maxLayerThickness_;

		//- Switch to calculate thickness as volume/area
		//  If false, thickness calculated from edges
		const bool thicknessFromVolume_;

		//- Layer thickness from previous step
		//  Used to decide whether to add or remove layers
		mutable scalar oldLayerThickness_;

		//- Point pairing
		mutable labelList* pointsPairingPtr_;

		//- Face pairing
		mutable labelList* facesPairingPtr_;

		//- Layer removal trigger time index
		mutable label triggerRemoval_;

		//- Layer addition trigger time index
		mutable label triggerAddition_;


		// Private Member Functions

			//- Check validity of construction data
		FoamDynamicMesh_EXPORT void checkDefinition();


		// Topological changes

		//- Check for valid layer
		FoamDynamicMesh_EXPORT bool validCollapse() const;

		//- Set layer pairing.  Return true if a valid layer exists
		FoamDynamicMesh_EXPORT bool setLayerPairing() const;

		//- Return points pairing in a layer (not automatic!)
		FoamDynamicMesh_EXPORT const labelList& pointsPairing() const;

		//- Return faces pairing in a layer (not automatic!)
		FoamDynamicMesh_EXPORT const labelList& facesPairing() const;

		//- Calculate the offset to the next layer
		FoamDynamicMesh_EXPORT tmp<vectorField> extrusionDir() const;

		//- Add a layer of cells
		FoamDynamicMesh_EXPORT void addCellLayer(polyTopoChange&) const;

		//- Remove a layer of cells
		FoamDynamicMesh_EXPORT void removeCellLayer(polyTopoChange&) const;

		//- Clear addressing
		FoamDynamicMesh_EXPORT void clearAddressing() const;


		// Helpers

			//- Optionally read old thickness
		static FoamDynamicMesh_EXPORT scalar readOldThickness(const dictionary&);


		// Static Data Members

			//- Thickness insertion fraction for the pre-motion
		static FoamDynamicMesh_EXPORT const scalar addDelta_;

		//- Thickness removal fraction for the cell collapse
		//  Note: the cell will be collapsed to this relative
		//  thickness before the layer is removed.
		static FoamDynamicMesh_EXPORT const scalar removeDelta_;

	public:

		//- Runtime type information
		//TypeName("layerAdditionRemoval");
		static const char* typeName_() { return "layerAdditionRemoval"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamDynamicMesh_EXPORT layerAdditionRemoval
		(
			const word& name,
			const label index,
			const polyTopoChanger& ptc,
			const word& zoneName,
			const scalar minThickness,
			const scalar maxThickness,
			const Switch thicknessFromVolume = true
		);

		//- Construct from dictionary
		FoamDynamicMesh_EXPORT layerAdditionRemoval
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyTopoChanger& ptc
		);

		//- Disallow default bitwise copy construction
		layerAdditionRemoval(const layerAdditionRemoval&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~layerAdditionRemoval();


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


		// Edit

			//- Return min layer thickness which triggers removal
		scalar minLayerThickness() const
		{
			return minLayerThickness_;
		}

		//- Set min layer thickness which triggers removal
		FoamDynamicMesh_EXPORT void setMinLayerThickness(const scalar t) const;

		//- Return max layer thickness which triggers removal
		scalar maxLayerThickness() const
		{
			return maxLayerThickness_;
		}

		//- Set max layer thickness which triggers removal
		FoamDynamicMesh_EXPORT void setMaxLayerThickness(const scalar t) const;


		//- Write
		FoamDynamicMesh_EXPORT virtual void write(Ostream&) const;

		//- Write dictionary
		FoamDynamicMesh_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const layerAdditionRemoval&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_layerAdditionRemoval_Header
