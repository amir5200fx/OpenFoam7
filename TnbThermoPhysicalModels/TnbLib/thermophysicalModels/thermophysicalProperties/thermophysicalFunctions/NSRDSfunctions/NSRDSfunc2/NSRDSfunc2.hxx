#pragma once
#ifndef _NSRDSfunc2_Header
#define _NSRDSfunc2_Header

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
	tnbLib::NSRDSfunc2

Description
	NSRDS function number 102

	Source:
	\verbatim
					  NSRDS - AICHE
				 Data Compilation Tables
					of Properties of
					 Pure Compounds

		Design Institute for Physical Property Data
		  American Institute of Chemical Engineers
				  345 East 47th Street
				New York, New York 10017

		 National Standard Reference Data System
		 American Institute of Chemical Engineers

		  T.E. Daubert       -       R.P. Danner

			Department of Chemical Engineering
			The Pennsylvania State University
				University Park, PA 16802
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <thermophysicalFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class NSRDSfunc2 Declaration
	\*---------------------------------------------------------------------------*/

	class NSRDSfunc2
		:
		public thermophysicalFunction
	{
		// Private Data

			// NSRDS function 102 coefficients
		scalar a_, b_, c_, d_;


	public:

		//- Runtime type information
		//TypeName("NSRDSfunc2");
		static const char* typeName_() { return "NSRDSfunc2"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamThermophysicalModels_EXPORT NSRDSfunc2
		(
			const scalar a,
			const scalar b,
			const scalar c,
			const scalar d
		);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT NSRDSfunc2(const dictionary& dict);


		// Member Functions

			//- Evaluate the function and return the result
		scalar f(scalar, scalar T) const
		{
			return a_ * pow(T, b_) / (1.0 + c_ / T + d_ / sqr(T));
		}

		//- Write the function coefficients
		void writeData(Ostream& os) const
		{
			os << a_ << token::SPACE
				<< b_ << token::SPACE
				<< c_ << token::SPACE
				<< d_;
		}


		// Ostream Operator

		friend Ostream& operator<<(Ostream& os, const NSRDSfunc2& f)
		{
			f.writeData(os);
			return os;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NSRDSfunc2_Header
