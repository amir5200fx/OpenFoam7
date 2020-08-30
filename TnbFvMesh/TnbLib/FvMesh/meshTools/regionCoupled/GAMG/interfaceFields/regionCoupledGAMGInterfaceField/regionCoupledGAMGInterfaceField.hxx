#pragma once
#ifndef _regionCoupledGAMGInterfaceField_Header
#define _regionCoupledGAMGInterfaceField_Header

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
	tnbLib::regionCoupledGAMGInterfaceField

Description
	GAMG agglomerated region coupled interface field.

SourceFiles
	regionCoupledGAMGInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <GAMGInterfaceField.hxx>
#include <regionCoupledGAMGInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class regionCoupledGAMGInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledGAMGInterfaceField
		:
		public GAMGInterfaceField
	{
		// Private Data

			//- Local reference cast into the cyclic interface
		const regionCoupledGAMGInterface& regionCoupledGAMGInterface_;


	public:

		//- Runtime type information
		TypeName("regionCoupled");


		// Constructors

			//- Construct from GAMG interface and fine level interface field
		regionCoupledGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField& fineInterfaceField
		);

		//- Construct from GAMG interface and fine level interface field
		regionCoupledGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		);

		//- Disallow default bitwise copy construction
		regionCoupledGAMGInterfaceField
		(
			const regionCoupledGAMGInterfaceField&
		);


		//- Destructor
		virtual ~regionCoupledGAMGInterfaceField();


		// Member Functions

			// Access

				//- Return size
		label size() const
		{
			return regionCoupledGAMGInterface_.size();
		}


		//- Interface matrix update
		virtual void updateInterfaceMatrix
		(
			scalarField&,
			const scalarField&,
			const scalarField&,
			const direction,
			const Pstream::commsTypes commsType
		) const
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const regionCoupledGAMGInterfaceField&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledGAMGInterfaceField_Header