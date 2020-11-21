#pragma once
#ifndef _nonEquilibrium_Header
#define _nonEquilibrium_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::TimeScaleModels::nonEquilibrium

Description
	Non-Equlibrium model for the time scale over which properties of a
	dispersed phase tend towards the mean value.

	Reference:
	\verbatim
		"An improved collision damping time for MP-PIC calculations of dense
		particle flows with applications to polydisperse sedimenting beds and
		colliding particle jets"
		P O'Rourke and D Snider
		Chemical Engineering Science
		Volume 65, Issue 22, Pages 6014-6028, November 2010
	\endverbatim

SourceFiles
	nonEquilibrium.C

\*---------------------------------------------------------------------------*/

#include <TimeScaleModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace TimeScaleModels
	{

		/*---------------------------------------------------------------------------*\
								Class nonEquilibrium Declaration
		\*---------------------------------------------------------------------------*/

		class nonEquilibrium
			:
			public TimeScaleModel
		{
		public:

			//- Runtime type information
			//TypeName("nonEquilibrium");
			static const char* typeName_() { return "nonEquilibrium"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			//- Constructors

				//- Construct from components
			FoamLagrangian_EXPORT nonEquilibrium(const dictionary& dict);

			//- Construct a copy
			FoamLagrangian_EXPORT nonEquilibrium(const nonEquilibrium& hc);

			//- Construct and return a clone
			virtual autoPtr<TimeScaleModel> clone() const
			{
				return autoPtr<TimeScaleModel>
					(
						new nonEquilibrium(*this)
						);
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~nonEquilibrium();


			//- Member Functions

				//- Time scale
			FoamLagrangian_EXPORT tmp<FieldField<Field, scalar>> oneByTau
			(
				const FieldField<Field, scalar>& alpha,
				const FieldField<Field, scalar>& r32,
				const FieldField<Field, scalar>& uSqr,
				const FieldField<Field, scalar>& f
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace TimeScaleModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nonEquilibrium_Header
