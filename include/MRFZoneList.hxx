#pragma once
#ifndef _MRFZoneList_Header
#define _MRFZoneList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::MRFZoneList

Description
	List container for MRF zomes

SourceFiles
	MRFZoneList.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>
#include <dictionary.hxx>
#include <fvMatricesFwd.hxx>
#include <MRFZone.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class MRFZoneList;
	FoamFiniteVolume_EXPORT Ostream& operator<<(Ostream& os, const MRFZoneList& models);

	/*---------------------------------------------------------------------------*\
							 Class MRFZoneList Declaration
	\*---------------------------------------------------------------------------*/

	class MRFZoneList
		:
		public PtrList<MRFZone>
	{
	protected:

		// Protected data

			//- Reference to the mesh database
		const fvMesh& mesh_;


	public:

		// Constructors

		FoamFiniteVolume_EXPORT MRFZoneList(const fvMesh& mesh, const dictionary& dict);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT MRFZoneList(const MRFZoneList&) = delete;


		//- Destructor
		FoamFiniteVolume_EXPORT ~MRFZoneList();


		// Member Functions

			//- Return active status
		FoamFiniteVolume_EXPORT bool active(const bool warn = false) const;

		//- Reset the source list
		FoamFiniteVolume_EXPORT void reset(const dictionary& dict);

		//- Add the frame acceleration
		FoamFiniteVolume_EXPORT void addAcceleration
		(
			const volVectorField& U,
			volVectorField& ddtU
		) const;

		//- Add the frame acceleration contribution to the momentum equation
		FoamFiniteVolume_EXPORT void addAcceleration(fvVectorMatrix& UEqn) const;

		//- Add the frame acceleration contribution to the momentum equation
		FoamFiniteVolume_EXPORT void addAcceleration
		(
			const volScalarField& rho,
			fvVectorMatrix& UEqn
		) const;

		//- Return the frame acceleration
		FoamFiniteVolume_EXPORT tmp<volVectorField> DDt
		(
			const volVectorField& U
		) const;

		//- Return the frame acceleration
		FoamFiniteVolume_EXPORT tmp<volVectorField> DDt
		(
			const volScalarField& rho,
			const volVectorField& U
		) const;

		//- Make the given absolute velocity relative within the MRF region
		FoamFiniteVolume_EXPORT void makeRelative(volVectorField& U) const;

		//- Make the given absolute flux relative within the MRF region
		FoamFiniteVolume_EXPORT void makeRelative(surfaceScalarField& phi) const;

		//- Return the given absolute flux relative within the MRF region
		FoamFiniteVolume_EXPORT tmp<surfaceScalarField> relative
		(
			const tmp<surfaceScalarField>& phi
		) const;

		//- Return the given absolute boundary flux relative within
		//  the MRF region
		FoamFiniteVolume_EXPORT tmp<FieldField<fvsPatchField, scalar>> relative
		(
			const tmp<FieldField<fvsPatchField, scalar>>& tphi
		) const;

		//- Return the given absolute patch flux relative within
		//  the MRF region
		FoamFiniteVolume_EXPORT tmp<Field<scalar>> relative
		(
			const tmp<Field<scalar>>& tphi,
			const label patchi
		) const;

		//- Make the given absolute mass-flux relative within the MRF region
		FoamFiniteVolume_EXPORT void makeRelative
		(
			const surfaceScalarField& rho,
			surfaceScalarField& phi
		) const;

		//- Make the given relative velocity absolute within the MRF region
		FoamFiniteVolume_EXPORT void makeAbsolute(volVectorField& U) const;

		//- Make the given relative flux absolute within the MRF region
		FoamFiniteVolume_EXPORT void makeAbsolute(surfaceScalarField& phi) const;

		//- Return the given relative flux absolute within the MRF region
		FoamFiniteVolume_EXPORT tmp<surfaceScalarField> absolute
		(
			const tmp<surfaceScalarField>& phi
		) const;

		//- Make the given relative mass-flux absolute within the MRF region
		FoamFiniteVolume_EXPORT void makeAbsolute
		(
			const surfaceScalarField& rho,
			surfaceScalarField& phi
		) const;

		//- Correct the boundary velocity for the rotation of the MRF region
		FoamFiniteVolume_EXPORT void correctBoundaryVelocity(volVectorField& U) const;

		//- Correct the boundary flux for the rotation of the MRF region
		FoamFiniteVolume_EXPORT void correctBoundaryFlux
		(
			const volVectorField& U,
			surfaceScalarField& phi
		) const;

		//- Filter-out the MRF region contribution from the given field
		// setting the corresponding values to zero
		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> zeroFilter
		(
			const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tphi
		) const;

		//- Update MRFZone faces if the mesh topology changes
		FoamFiniteVolume_EXPORT void update();


		// I-O

		//- Read dictionary
		FoamFiniteVolume_EXPORT bool read(const dictionary& dict);

		//- Write data to Ostream
		FoamFiniteVolume_EXPORT bool writeData(Ostream& os) const;

		//- Ostream operator
		friend FoamFiniteVolume_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const MRFZoneList& models
				);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const MRFZoneList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <MRFZoneListI.hxx>

//#ifdef NoRepository
//#include <MRFZoneListTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MRFZoneList_Header
