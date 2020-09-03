#pragma once
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

\*---------------------------------------------------------------------------*/

#include <GeometricScalarField.hxx>

//#define TEMPLATE \
//    template<class Type, template<class> class PatchField, class GeoMesh>
//#include <GeometricFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void component
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf,
		const direction d
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	void T
	(
		GeometricField<Type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	);

	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		void pow
		(
			GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh>& gf,
			const GeometricField<Type, PatchField, GeoMesh>& gf1
		);

	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		tmp
		<
		GeometricField
		<typename powProduct<Type, r>::type, PatchField, GeoMesh>
		>
		pow
		(
			const GeometricField<Type, PatchField, GeoMesh>& gf,
			typename powProduct<Type, r>::type
		);

	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		tmp
		<
		GeometricField
		<typename powProduct<Type, r>::type, PatchField, GeoMesh>
		>
		pow
		(
			const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf,
			typename powProduct<Type, r>::type
		);

	template<class Type, template<class> class PatchField, class GeoMesh>
	void sqr
	(
		GeometricField
		<typename outerProduct<Type, Type>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const GeometricField<Type, PatchField, GeoMesh>& gf);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf);

	template<class Type, template<class> class PatchField, class GeoMesh>
	void magSqr
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> magSqr
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> magSqr
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	void mag
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> mag
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> mag
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptAv
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const GeometricField<Type, PatchField, GeoMesh>& gf);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf);


//#define UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY(returnType, func, gFunc)        \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf                        \
//);                                                                             \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//);

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const GeometricField<Type, PatchField, GeoMesh>& gf);
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const GeometricField<Type, PatchField, GeoMesh>& gf);
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);

//#undef UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY


//#define UNARY_REDUCTION_FUNCTION(returnType, func, gFunc)                      \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf                        \
//);                                                                             \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//);

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const GeometricField<Type, PatchField, GeoMesh>& gf);
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const GeometricField<Type, PatchField, GeoMesh>& gf);
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const GeometricField<Type, PatchField, GeoMesh>& gf);
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);

//#undef UNARY_REDUCTION_FUNCTION


		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	                                                            tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const Type& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2,
	                                                   const Type& t2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                   const Type& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                   const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2,
	                                                   const Type& t2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                            const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                            const Type& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                            const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2,
	                                                            const Type& t2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const Type& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const dimensioned<Type>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2,
	                                                          const Type& t2);


		// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const GeometricField<Type, PatchField, GeoMesh>& df1);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1);

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                          tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                          tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                          tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                          tdf2);

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& df2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf2);
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const dimensioned<scalar>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const scalar& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const dimensioned<scalar>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const scalar& t2);

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const dimensioned<scalar>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& df1,
	                                                          const scalar& t2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const dimensioned<scalar>& dt2);
	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tdf1,
	                                                          const scalar& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Type1, Type2>::type, PatchField, GeoMesh>& gf,           \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//        <typename product<Type1, Type2>::type, PatchField, GeoMesh>            \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Type1, Type2>::type, PatchField, GeoMesh>                \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2                \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Type1, Type2>::type, PatchField, GeoMesh>                \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,               \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Type1, Type2>::type, PatchField, GeoMesh>                \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,               \
//    const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2                \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Type, Form>::type, PatchField, GeoMesh>& gf,             \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const dimensioned<Form>& dvs                                               \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Type, Form>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const dimensioned<Form>& dvs                                               \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Type, Form>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,                \
//    const dimensioned<Form>& dvs                                               \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,                \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>& gf,             \
//    const dimensioned<Form>& dvs,                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp                                                                            \
//<                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>                  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//);

		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf, const dimensioned<Form>& dvs,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	              const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	              const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
	              const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf,
	              const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);

		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	           const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	           const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	           const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	           const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	         const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	            const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	            const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2);
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	            const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	            const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1);
	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1);

//#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GeometricFieldFunctionsI.hxx>

//#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //
