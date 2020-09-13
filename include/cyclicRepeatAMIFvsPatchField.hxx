#pragma once
#ifndef _cyclicRepeatAMIFvsPatchField_Header
#define _cyclicRepeatAMIFvsPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::cyclicRepeatAMIFvsPatchField

Description
	tnbLib::cyclicRepeatAMIFvsPatchField

SourceFiles
	cyclicRepeatAMIFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMIFvsPatchField.hxx>
#include <cyclicRepeatAMIFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicRepeatAMIFvsPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicRepeatAMIFvsPatchField
		:
		public cyclicAMIFvsPatchField<Type>
	{
	public:

		//- Runtime type information
		TypeName(cyclicRepeatAMIFvPatch::typeName_());


		// Constructors

			//- Inherit parent constructors
		using cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField;

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new cyclicRepeatAMIFvsPatchField<Type>(*this)
					);
		}

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvsPatchField<Type>> clone
		(
			const DimensionedField<Type, surfaceMesh>& iF
		) const
		{
			return tmp<fvsPatchField<Type>>
				(
					new cyclicRepeatAMIFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicRepeatAMIFvsPatchField_Header