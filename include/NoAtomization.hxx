#pragma once
#ifndef _NoAtomization_Header
#define _NoAtomization_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::NoAtomization

Description
	Dummy phase change model for 'none'

\*---------------------------------------------------------------------------*/

#include <AtomizationModel.hxx>

#include <vector.hxx>  // added by amir
#include <Random.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						   Class NoAtomization Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoAtomization
		:
		public AtomizationModel<CloudType>
	{
	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from dictionary
		NoAtomization(const dictionary& dict, CloudType& cloud);

		//- Construct copy
		NoAtomization(const NoAtomization<CloudType>& am);

		//- Construct and return a clone
		virtual autoPtr<AtomizationModel<CloudType>> clone() const
		{
			return autoPtr<AtomizationModel<CloudType>>
				(
					new NoAtomization<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoAtomization();


		// Member Functions

			//- Flag to indicate whether model activates atomization model
		virtual bool active() const;

		//- Initial value of liquidCore
		virtual scalar initLiquidCore() const;

		//- Flag to indicate if chi needs to be calculated
		virtual bool calcChi() const;

		virtual void update
		(
			const scalar dt,
			scalar& d,
			scalar& liquidCore,
			scalar& tc,
			const scalar rho,
			const scalar mu,
			const scalar sigma,
			const scalar volFlowRate,
			const scalar rhoAv,
			const scalar Urel,
			const vector& pos,
			const vector& injectionPos,
			const scalar pAmbient,
			const scalar chi,
			Random& rndGen
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoAtomizationI.hxx>

//#ifdef NoRepository
//#include <NoAtomization.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoAtomization_Header
