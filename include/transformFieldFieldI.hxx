#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	void transform
	(
		FieldField<Field, Type>& rtf,
		const FieldField<Field, tensor>& trf,
		const FieldField<Field, Type>& tf
	)
	{
		forAll(rtf, i)
		{
			transform(rtf[i], trf[i], tf[i]);
		}
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const FieldField<Field, tensor>& trf,
		const FieldField<Field, Type>& tf
	)
	{
		tmp<FieldField<Field, Type>> tranf
		(
			FieldField<Field, Type>::NewCalculatedType(tf)
		);
		transform(tranf(), trf, tf);
		return tranf;
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const FieldField<Field, tensor>& trf,
		const tmp<FieldField<Field, Type>>& ttf
	)
	{
		tmp<FieldField<Field, Type>> tranf(ttf.ptr());
		transform(tranf(), trf, tranf());
		return tranf;
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tmp<FieldField<Field, tensor>>& ttrf,
		const FieldField<Field, Type>& tf
	)
	{
		tmp<FieldField<Field, Type>> tranf
		(
			FieldField<Field, Type>::NewCalculatedType(tf)
		);
		transform(tranf(), ttrf(), tf);
		ttrf.clear();
		return tranf;
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tmp<FieldField<Field, tensor>>& ttrf,
		const tmp<FieldField<Field, Type>>& ttf
	)
	{
		tmp<FieldField<Field, Type>> tranf(ttf.ptr());
		transform(tranf(), ttrf(), tranf());
		ttrf.clear();
		return tranf;
	}


	template<template<class> class Field, class Type>
	void transform
	(
		FieldField<Field, Type>& rtf,
		const tensor& t,
		const FieldField<Field, Type>& tf
	)
	{
		forAll(rtf, i)
		{
			transform(rtf[i], t, tf[i]);
		}
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tensor& t,
		const FieldField<Field, Type>& tf
	)
	{
		tmp<FieldField<Field, Type>> tranf
		(
			FieldField<Field, Type>::NewCalculatedType(tf)
		);
		transform(tranf(), t, tf);
		return tranf;
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tensor& t,
		const tmp<FieldField<Field, Type>>& ttf
	)
	{
		tmp<FieldField<Field, Type>> tranf(ttf.ptr());
		transform(tranf(), t, tranf());
		return tranf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //