#pragma once
#ifndef _porosityModelList_Header
#define _porosityModelList_Header

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
	tnbLib::porosityModelList

Description
	List container for porosity models

SourceFiles
	porosityModelList.C

\*---------------------------------------------------------------------------*/


#include <fvMesh.hxx>
#include <dictionary.hxx>
#include <fvMatricesFwd.hxx>
#include <porosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class porosityModelList;
	FoamFiniteVolume_EXPORT Ostream& operator<<(Ostream& os, const porosityModelList& models);

	/*---------------------------------------------------------------------------*\
						  Class porosityModelList Declaration
	\*---------------------------------------------------------------------------*/

	class porosityModelList
		:
		public PtrList<porosityModel>
	{
	protected:

		// Protected data

			//- Reference to the mesh database
		const fvMesh& mesh_;


	public:

		// Constructors

		FoamFiniteVolume_EXPORT porosityModelList(const fvMesh& mesh, const dictionary& dict);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT porosityModelList(const porosityModelList&) = delete;


		//- Destructor
		FoamFiniteVolume_EXPORT ~porosityModelList();


		// Member Functions

			//- Return active status
		FoamFiniteVolume_EXPORT bool active(const bool active = false) const;

		//- Reset the source list
		FoamFiniteVolume_EXPORT void reset(const dictionary& dict);

		//- Add resistance
		FoamFiniteVolume_EXPORT void addResistance(fvVectorMatrix& UEqn);

		//- Add resistance
		FoamFiniteVolume_EXPORT void addResistance
		(
			fvVectorMatrix& UEqn,
			const volScalarField& rho,
			const volScalarField& mu
		);

		//- Add resistance
		FoamFiniteVolume_EXPORT void addResistance
		(
			const fvVectorMatrix& UEqn,
			volTensorField& AU,
			bool correctAUprocBC = true
		);


		// I-O

			//- Read dictionary
		FoamFiniteVolume_EXPORT bool read(const dictionary& dict);

		//- Write data to Ostream
		FoamFiniteVolume_EXPORT bool writeData(Ostream& os) const;

		//- Ostream operator
		friend FoamFiniteVolume_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const porosityModelList& models
				);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const porosityModelList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_porosityModelList_Header
