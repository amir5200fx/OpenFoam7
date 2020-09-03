#pragma once
#include <FieldM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<class Type>
	void transform
	(
		Field<Type>& rtf,
		const tensorField& trf,
		const Field<Type>& tf
	)
	{
		if (trf.size() == 1)
		{
			return transform(rtf, trf[0], tf);
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F_F
			(
				Type, rtf, =, transform, tensor, trf, Type, tf
			)
		}
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tensorField& trf,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type>> tranf(new Field<Type>(tf.size()));
		transform(tranf.ref(), trf, tf);
		return tranf;
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tensorField& trf,
		const tmp<Field<Type>>& ttf
	)
	{
		tmp<Field<Type>> tranf = New(ttf);
		transform(tranf.ref(), trf, ttf());
		ttf.clear();
		return tranf;
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tmp<tensorField>& ttrf,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type>> tranf(new Field<Type>(tf.size()));
		transform(tranf.ref(), ttrf(), tf);
		ttrf.clear();
		return tranf;
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tmp<tensorField>& ttrf,
		const tmp<Field<Type>>& ttf
	)
	{
		tmp<Field<Type>> tranf = New(ttf);
		transform(tranf.ref(), ttrf(), ttf());
		ttf.clear();
		ttrf.clear();
		return tranf;
	}


	template<class Type>
	void transform
	(
		Field<Type>& rtf,
		const tensor& t,
		const Field<Type>& tf
	)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, rtf, =, transform, tensor, t, Type, tf)
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tensor& t,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type>> tranf(new Field<Type>(tf.size()));
		transform(tranf.ref(), t, tf);
		return tranf;
	}


	template<class Type>
	tmp<Field<Type>> transform
	(
		const tensor& t,
		const tmp<Field<Type>>& ttf
	)
	{
		tmp<Field<Type>> tranf = New(ttf);
		transform(tranf.ref(), t, ttf());
		ttf.clear();
		return tranf;
	}


	template<class Type1, class Type2>
	tmp<Field<Type1>> transformFieldMask(const Field<Type2>& f)
	{
		return f;
	}

	template<class Type1, class Type2>
	tmp<Field<Type1>> transformFieldMask(const tmp<Field<Type2>>& tf)
	{
		return tmp<Field<Type1>>(tf.ptr());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //