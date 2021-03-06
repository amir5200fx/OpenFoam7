#pragma once
#ifndef _regionModel1D_Header
#define _regionModel1D_Header

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
	tnbLib::regionModels::regionModel1D

Description
	Base class for 1-D region models

SourceFiles
	regionModel1D.C

\*---------------------------------------------------------------------------*/

#include <regionModel.hxx>
#include <surfaceFields.hxx>
#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{

		/*---------------------------------------------------------------------------*\
							   Class regionModel1D Declaration
		\*---------------------------------------------------------------------------*/

		class regionModel1D
			:
			public regionModel
		{
			// Private Member Functions

				//- Disallow default bitwise copy construction
			FoamLagrangian_EXPORT regionModel1D(const regionModel1D&) = delete;

			//- Disallow default bitwise assignment
			FoamLagrangian_EXPORT void operator=(const regionModel1D&) = delete;

			//- Construct region mesh and fields
			FoamLagrangian_EXPORT void constructMeshObjects();

			//- Initialise the region
			FoamLagrangian_EXPORT void initialise();


		protected:

			// Protected data

				// Region addressing - per internally coupled patch face walking out

					//- Global face IDs
			labelListList boundaryFaceFaces_;

			//- Global cell IDs
			labelListList boundaryFaceCells_;

			//- Global boundary face IDs oppossite coupled patch
			labelList boundaryFaceOppositeFace_;

			//- Number of layers in the region
			label nLayers_;


			// Geometry

				//- Face area magnitude normal to patch
			autoPtr<surfaceScalarField> nMagSfPtr_;

			//- Flag to allow mesh movement
			Switch moveMesh_;


			// Protected member functions

				//- Read control parameters from dictionary
			FoamLagrangian_EXPORT virtual bool read();

			//- Read control parameters from dictionary
			FoamLagrangian_EXPORT virtual bool read(const dictionary& dict);

			//- Move mesh points according to change in cell volumes
			//  Returns map ordered by cell where 1 = cell moved, 0 = cell unchanged
			FoamLagrangian_EXPORT tmp<labelField> moveMesh
			(
				const scalarList& deltaV,
				const scalar minDelta = 0.0
			);


		public:

			//- Runtime type information
			//TypeName("regionModel1D");
			static const char* typeName_() { return "regionModel1D"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct null
			FoamLagrangian_EXPORT regionModel1D
			(
				const fvMesh& mesh,
				const word& regionType
			);

			//- Construct from mesh, region type and name
			FoamLagrangian_EXPORT regionModel1D
			(
				const fvMesh& mesh,
				const word& regionType,
				const word& modelName,
				bool readFields = true
			);

			//- Construct from mesh, region type and name and dict
			FoamLagrangian_EXPORT regionModel1D
			(
				const fvMesh& mesh,
				const word& regionType,
				const word& modelName,
				const dictionary& dict,
				bool readFields = true
			);



			//- Destructor
			FoamLagrangian_EXPORT virtual ~regionModel1D();


			// Member Functions

				// Access

					// Addressing

						//- Return the global face IDs
			inline const labelListList& boundaryFaceFaces() const;

			//- Return the global cell IDs
			inline const labelListList& boundaryFaceCells() const;

			//- Return the global boundary face IDs oppossite coupled patch
			inline const labelList& boundaryFaceOppositeFace() const;


			// Geometry

				//- Return the face area magnitudes / [m^2]
			inline const surfaceScalarField& nMagSf() const;

			//- Return the number of layers in the region
			inline label nLayers() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <regionModel1DI.hxx>

#endif // !_regionModel1D_Header
