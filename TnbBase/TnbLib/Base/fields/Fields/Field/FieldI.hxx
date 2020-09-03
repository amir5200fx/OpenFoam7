#pragma once
#include <FieldM.hxx>
#include <dictionary.hxx>
#include <contiguous.hxx>
#include <mapDistributeBase.hxx>
#include <flipOp.hxx>

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

template<class Type>
const char* const tnbLib::Field<Type>::typeName("Field");


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Field<Type>::Field()
	:
	List<Type>()
{}


template<class Type>
tnbLib::Field<Type>::Field(const label size)
	:
	List<Type>(size)
{}


template<class Type>
tnbLib::Field<Type>::Field(const label size, const Type& t)
	:
	List<Type>(size, t)
{}


template<class Type>
tnbLib::Field<Type>::Field(const label size, const zero)
	:
	List<Type>(size, Zero)
{}


template<class Type>
tnbLib::Field<Type>::Field(const UList<Type>& list)
	:
	List<Type>(list)
{}


template<class Type>
tnbLib::Field<Type>::Field(List<Type>&& f)
	:
	List<Type>(move(f))
{}


template<class Type>
tnbLib::Field<Type>::Field(const UIndirectList<Type>& list)
	:
	List<Type>(list)
{}


template<class Type>
tnbLib::Field<Type>::Field(const Field<Type>& f)
	:
	tmp<Field<Type>>::refCount(),
	List<Type>(f)
{}


template<class Type>
tnbLib::Field<Type>::Field(Field<Type>& f, bool reuse)
	:
	List<Type>(f, reuse)
{}


template<class Type>
tnbLib::Field<Type>::Field(Field<Type>&& f)
	:
	tmp<Field<Type>>::refCount(),
	List<Type>(move(f))
{}


template<class Type>
tnbLib::Field<Type>::Field(const tmp<Field<Type>>& tf)
	:
	List<Type>(const_cast<Field<Type>&>(tf()), tf.isTmp())
{
	tf.clear();
}


template<class Type>
tnbLib::Field<Type>::Field
(
	const UList<Type>& mapF,
	const labelUList& mapAddressing
)
	:
	List<Type>(mapAddressing.size())
{
	map(mapF, mapAddressing);
}


template<class Type>
tnbLib::Field<Type>::Field
(
	const tmp<Field<Type>>& tmapF,
	const labelUList& mapAddressing
)
	:
	List<Type>(mapAddressing.size())
{
	map(tmapF, mapAddressing);
}


template<class Type>
tnbLib::Field<Type>::Field
(
	const UList<Type>& mapF,
	const labelListList& mapAddressing,
	const scalarListList& mapWeights
)
	:
	List<Type>(mapAddressing.size())
{
	map(mapF, mapAddressing, mapWeights);
}


template<class Type>
tnbLib::Field<Type>::Field
(
	const tmp<Field<Type>>& tmapF,
	const labelListList& mapAddressing,
	const scalarListList& mapWeights
)
	:
	List<Type>(mapAddressing.size())
{
	map(tmapF, mapAddressing, mapWeights);
}


template<class Type>
tnbLib::Field<Type>::Field(Istream& is)
	:
	List<Type>(is)
{}


template<class Type>
tnbLib::Field<Type>::Field
(
	const word& keyword,
	const dictionary& dict,
	const label s
)
{
	if (s)
	{
		ITstream& is = dict.lookup(keyword);

		// Read first token
		token firstToken(is);

		if (firstToken.isWord())
		{
			if (firstToken.wordToken() == "uniform")
			{
				this->setSize(s);
				operator=(pTraits<Type>(is));
			}
			else if (firstToken.wordToken() == "nonuniform")
			{
				is >> static_cast<List<Type>&>(*this);
				if (this->size() != s)
				{
					FatalIOErrorInFunction
					(
						dict
					) << "size " << this->size()
						<< " is not equal to the given value of " << s
						<< exit(FatalIOError);
				}
			}
			else
			{
				FatalIOErrorInFunction
				(
					dict
				) << "expected keyword 'uniform' or 'nonuniform', found "
					<< firstToken.wordToken()
					<< exit(FatalIOError);
			}
		}
		else
		{
			if (is.version() == 2.0)
			{
				IOWarningInFunction
				(
					dict
				) << "expected keyword 'uniform' or 'nonuniform', "
					"assuming deprecated Field format from "
					"tnbLib version 2.0." << endl;

				this->setSize(s);

				is.putBack(firstToken);
				operator=(pTraits<Type>(is));
			}
			else
			{
				FatalIOErrorInFunction
				(
					dict
				) << "expected keyword 'uniform' or 'nonuniform', found "
					<< firstToken.info()
					<< exit(FatalIOError);
			}
		}
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Field<Type>::clone() const
{
	return tmp<Field<Type>>(new Field<Type>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::UList<Type>& tnbLib::Field<Type>::copySelf
(
	const UList<Type>& mapF,
	tmp<Field<Type>>& tmapF
) const
{
	if (static_cast<const UList<Type>*>(this) == &mapF)
	{
		tmapF = clone();
	}
	return tmapF.valid() ? tmapF() : mapF;
}


template<class Type>
void tnbLib::Field<Type>::map
(
	const UList<Type>& mapF0,
	const labelUList& mapAddressing
)
{
	Field<Type>& f = *this;

	tmp<Field<Type>> tmapF;
	const UList<Type>& mapF = copySelf(mapF0, tmapF);

	if (f.size() != mapAddressing.size())
	{
		f.setSize(mapAddressing.size());
	}

	if (mapF.size() > 0)
	{
		forAll(f, i)
		{
			const label mapi = mapAddressing[i];

			if (mapi >= 0)
			{
				f[i] = mapF[mapi];
			}
		}
	}
}


template<class Type>
void tnbLib::Field<Type>::map
(
	const tmp<Field<Type>>& tmapF,
	const labelUList& mapAddressing
)
{
	map(tmapF(), mapAddressing);
	tmapF.clear();
}


template<class Type>
void tnbLib::Field<Type>::map
(
	const UList<Type>& mapF0,
	const labelListList& mapAddressing,
	const scalarListList& mapWeights
)
{
	if (mapWeights.size() != mapAddressing.size())
	{
		FatalErrorInFunction
			<< mapWeights.size() << " map size: " << mapAddressing.size()
			<< abort(FatalError);
	}

	Field<Type>& f = *this;

	tmp<Field<Type>> tmapF;
	const UList<Type>& mapF = copySelf(mapF0, tmapF);

	if (this->size() != mapAddressing.size())
	{
		this->setSize(mapAddressing.size());
	}

	forAll(f, i)
	{
		const labelList& localAddrs = mapAddressing[i];
		const scalarList& localWeights = mapWeights[i];

		f[i] = Zero;

		forAll(localAddrs, j)
		{
			f[i] += localWeights[j] * mapF[localAddrs[j]];
		}
	}
}


template<class Type>
void tnbLib::Field<Type>::map
(
	const tmp<Field<Type>>& tmapF,
	const labelListList& mapAddressing,
	const scalarListList& mapWeights
)
{
	map(tmapF(), mapAddressing, mapWeights);
	tmapF.clear();
}


template<class Type>
void tnbLib::Field<Type>::rmap
(
	const UList<Type>& mapF0,
	const labelUList& mapAddressing
)
{
	Field<Type>& f = *this;

	tmp<Field<Type>> tmapF;
	const UList<Type>& mapF = copySelf(mapF0, tmapF);

	forAll(mapF, i)
	{
		const label mapi = mapAddressing[i];

		if (mapi >= 0)
		{
			f[mapi] = mapF[i];
		}
	}
}


template<class Type>
void tnbLib::Field<Type>::rmap
(
	const tmp<Field<Type>>& tmapF,
	const labelUList& mapAddressing
)
{
	rmap(tmapF(), mapAddressing);
	tmapF.clear();
}


template<class Type>
void tnbLib::Field<Type>::rmap
(
	const UList<Type>& mapF0,
	const labelUList& mapAddressing,
	const UList<scalar>& mapWeights
)
{
	Field<Type>& f = *this;

	tmp<Field<Type>> tmapF;
	const UList<Type>& mapF = copySelf(mapF0, tmapF);

	f = Zero;

	forAll(mapF, i)
	{
		f[mapAddressing[i]] += mapF[i] * mapWeights[i];
	}
}


template<class Type>
void tnbLib::Field<Type>::rmap
(
	const tmp<Field<Type>>& tmapF,
	const labelUList& mapAddressing,
	const UList<scalar>& mapWeights
)
{
	rmap(tmapF(), mapAddressing, mapWeights);
	tmapF.clear();
}


template<class Type>
void tnbLib::Field<Type>::negate()
{
	TFOR_ALL_F_OP_OP_F(Type, *this, =, -, Type, *this)
}


template<class Type>
tnbLib::tmp<tnbLib::Field<typename tnbLib::Field<Type>::cmptType>>
tnbLib::Field<Type>::component
(
	const direction d
) const
{
	tmp<Field<cmptType>> Component(new Field<cmptType>(this->size()));
	::tnbLib::component(Component.ref(), *this, d);
	return Component;
}


template<class Type>
void tnbLib::Field<Type>::replace
(
	const direction d,
	const UList<cmptType>& sf
)
{
	TFOR_ALL_F_OP_FUNC_S_F(Type, *this, ., replace, const direction, d,
		cmptType, sf)
}


template<class Type>
void tnbLib::Field<Type>::replace
(
	const direction d,
	const tmp<Field<cmptType>>& tsf
)
{
	replace(d, tsf());
	tsf.clear();
}


template<class Type>
void tnbLib::Field<Type>::replace
(
	const direction d,
	const cmptType& c
)
{
	TFOR_ALL_F_OP_FUNC_S_S(Type, *this, ., replace, const direction, d,
		cmptType, c)
}


template<class Type>
template<class VSForm>
VSForm tnbLib::Field<Type>::block(const label start) const
{
	VSForm vs;
	for (direction i = 0; i < VSForm::nComponents; i++)
	{
		vs[i] = this->operator[](start + i);
	}
	return vs;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Field<Type>::T() const
{
	tmp<Field<Type>> transpose(new Field<Type>(this->size()));
	::tnbLib::T(transpose.ref(), *this);
	return transpose;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Field<Type>::operator=(const Field<Type>& rhs)
{
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	List<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::Field<Type>::operator=(Field<Type>&& rhs)
{
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	List<Type>::operator=(move(rhs));
}


template<class Type>
void tnbLib::Field<Type>::operator=(const SubField<Type>& rhs)
{
	List<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::Field<Type>::operator=(const UList<Type>& rhs)
{
	List<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::Field<Type>::operator=(List<Type>&& rhs)
{
	List<Type>::operator=(move(rhs));
}


template<class Type>
void tnbLib::Field<Type>::operator=(const tmp<Field>& rhs)
{
	if (this == &(rhs()))
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	List<Type>::operator=(rhs());
}


template<class Type>
void tnbLib::Field<Type>::operator=(const Type& t)
{
	List<Type>::operator=(t);
}


template<class Type>
void tnbLib::Field<Type>::operator=(const zero)
{
	List<Type>::operator=(Zero);
}


template<class Type>
template<class Form, class Cmpt, tnbLib::direction nCmpt>
void tnbLib::Field<Type>::operator=(const VectorSpace<Form, Cmpt, nCmpt>& vs)
{
	TFOR_ALL_F_OP_S(Type, *this, =, VSType, vs)
}


//#define COMPUTED_ASSIGNMENT(TYPE, op)                                          \
//                                                                               \
//template<class Type>                                                           \
//void tnbLib::Field<Type>::operator op(const UList<TYPE>& f)                      \
//{                                                                              \
//    TFOR_ALL_F_OP_F(Type, *this, op, TYPE, f)                                  \
//}                                                                              \
//                                                                               \
//template<class Type>                                                           \
//void tnbLib::Field<Type>::operator op(const tmp<Field<TYPE>>& tf)                \
//{                                                                              \
//    operator op(tf());                                                         \
//    tf.clear();                                                                \
//}                                                                              \
//                                                                               \
//template<class Type>                                                           \
//void tnbLib::Field<Type>::operator op(const TYPE& t)                             \
//{                                                                              \
//    TFOR_ALL_F_OP_S(Type, *this, op, TYPE, t)                                  \
//}

template <class Type>
void tnbLib::Field<Type>::operator +=(const UList<Type>& f)
{
	TFOR_ALL_F_OP_F(Type, *this, +=, Type, f)
}

template <class Type>
void tnbLib::Field<Type>::operator +=(const tmp<Field<Type>>& tf)
{
	operator +=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::Field<Type>::operator +=(const Type& t)
{
	TFOR_ALL_F_OP_S(Type, *this, +=, Type, t)
}

template <class Type>
void tnbLib::Field<Type>::operator -=(const UList<Type>& f)
{
	TFOR_ALL_F_OP_F(Type, *this, -=, Type, f)
}

template <class Type>
void tnbLib::Field<Type>::operator -=(const tmp<Field<Type>>& tf)
{
	operator -=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::Field<Type>::operator -=(const Type& t)
{
	TFOR_ALL_F_OP_S(Type, *this, -=, Type, t)
}

template <class Type>
void tnbLib::Field<Type>::operator *=(const UList<scalar>& f)
{
	TFOR_ALL_F_OP_F(Type, *this, *=, scalar, f)
}

template <class Type>
void tnbLib::Field<Type>::operator *=(const tmp<Field<scalar>>& tf)
{
	operator *=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::Field<Type>::operator *=(const scalar& t)
{
	TFOR_ALL_F_OP_S(Type, *this, *=, scalar, t)
}

template <class Type>
void tnbLib::Field<Type>::operator /=(const UList<scalar>& f)
{
	TFOR_ALL_F_OP_F(Type, *this, /=, scalar, f)
}

template <class Type>
void tnbLib::Field<Type>::operator /=(const tmp<Field<scalar>>& tf)
{
	operator /=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::Field<Type>::operator /=(const scalar& t)
{
	TFOR_ALL_F_OP_S(Type, *this, /=, scalar, t)
}

//#undef COMPUTED_ASSIGNMENT


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class Type>
void tnbLib::writeEntry(Ostream& os, const Field<Type>& f)
{
	bool uniform = false;

	if (f.size() && contiguous<Type>())
	{
		uniform = true;

		forAll(f, i)
		{
			if (f[i] != f[0])
			{
				uniform = false;
				break;
			}
		}
	}

	if (uniform)
	{
		os << "uniform " << f[0];
	}
	else
	{
		os << "nonuniform ";
		writeEntry(os, static_cast<const List<Type>&>(f));
	}
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Field<Type>& f)
{
	os << static_cast<const List<Type>&>(f);
	return os;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const tmp<Field<Type>>& tf)
{
	os << tf();
	tf.clear();
	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //