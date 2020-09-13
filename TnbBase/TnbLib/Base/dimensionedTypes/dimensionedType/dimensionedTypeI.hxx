#pragma once
#include <pTraits.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::dimensioned<Type>::initialize(Istream& is)
{
	token nextToken(is);
	is.putBack(nextToken);

	// Check if the original format is used in which the name is provided
	// and reset the name to that read
	if (nextToken.isWord())
	{
		is >> name_;
		is >> nextToken;
		is.putBack(nextToken);
	}

	// If the dimensions are provided compare with the argument
	scalar multiplier = 1.0;

	if (nextToken == token::BEGIN_SQR)
	{
		dimensionSet dims(dimless);
		dims.read(is, multiplier);

		if (dims != dimensions_)
		{
			FatalIOErrorInFunction
			(
				is
			) << "The dimensions " << dims
				<< " provided do not match the required dimensions "
				<< dimensions_
				<< abort(FatalIOError);
		}
	}

	is >> value_;
	value_ *= multiplier;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const word& name,
	const dimensionSet& dimSet,
	const Type& t
)
	:
	name_(name),
	dimensions_(dimSet),
	value_(t)
{}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const dimensionSet& dimSet,
	const Type& t
)
	:
	name_(::tnbLib::name(t)),
	dimensions_(dimSet),
	value_(t)
{}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned(const Type& t)
	:
	name_(::tnbLib::name(t)),
	dimensions_(dimless),
	value_(t)
{}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const word& name,
	const dimensioned<Type>& dt
)
	:
	name_(name),
	dimensions_(dt.dimensions_),
	value_(dt.value_)
{}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	Istream& is
)
	:
	dimensions_(dimless)
{
	read(is);
}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const word& name,
	Istream& is
)
	:
	name_(name),
	dimensions_(dimless)
{
	scalar multiplier;
	dimensions_.read(is, multiplier);
	is >> value_;
	value_ *= multiplier;
}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const word& name,
	const dimensionSet& dimSet,
	Istream& is
)
	:
	name_(name),
	dimensions_(dimSet),
	value_(Zero)
{
	initialize(is);
}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
(
	const word& name,
	const dimensionSet& dimSet,
	const dictionary& dict
)
	:
	name_(name),
	dimensions_(dimSet),
	value_(Zero)
{
	initialize(dict.lookup(name));
}


template<class Type>
tnbLib::dimensioned<Type>::dimensioned
()
	:
	name_("undefined"),
	dimensions_(dimless),
	value_(Zero)
{}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

template<class Type>
tnbLib::dimensioned<Type> tnbLib::dimensioned<Type>::lookupOrDefault
(
	const word& name,
	const dictionary& dict,
	const dimensionSet& dims,
	const Type& defaultValue
)
{
	if (dict.found(name))
	{
		return dimensioned<Type>(name, dims, dict.lookup(name));
	}
	else
	{
		return dimensioned<Type>(name, dims, defaultValue);
	}
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::dimensioned<Type>::lookupOrDefault
(
	const word& name,
	const dictionary& dict,
	const Type& defaultValue
)
{
	return lookupOrDefault(name, dict, dimless, defaultValue);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::dimensioned<Type>::lookupOrAddToDict
(
	const word& name,
	dictionary& dict,
	const dimensionSet& dims,
	const Type& defaultValue
)
{
	Type value = dict.lookupOrAddDefault<Type>(name, defaultValue);
	return dimensioned<Type>(name, dims, value);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::dimensioned<Type>::lookupOrAddToDict
(
	const word& name,
	dictionary& dict,
	const Type& defaultValue
)
{
	return lookupOrAddToDict(name, dict, dimless, defaultValue);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word& tnbLib::dimensioned<Type>::name() const
{
	return name_;
}

template<class Type>
tnbLib::word& tnbLib::dimensioned<Type>::name()
{
	return name_;
}


template<class Type>
const tnbLib::dimensionSet& tnbLib::dimensioned<Type>::dimensions() const
{
	return dimensions_;
}

template<class Type>
tnbLib::dimensionSet& tnbLib::dimensioned<Type>::dimensions()
{
	return dimensions_;
}


template<class Type>
const Type& tnbLib::dimensioned<Type>::value() const
{
	return value_;
}

template<class Type>
Type& tnbLib::dimensioned<Type>::value()
{
	return value_;
}


template<class Type>
tnbLib::dimensioned<typename tnbLib::dimensioned<Type>::cmptType>
tnbLib::dimensioned<Type>::component
(
	const direction d
) const
{
	return dimensioned<cmptType>
		(
			name_ + ".component(" + tnbLib::name(d) + ')',
			dimensions_,
			value_.component(d)
			);
}


template<class Type>
void tnbLib::dimensioned<Type>::replace
(
	const direction d,
	const dimensioned<typename dimensioned<Type>::cmptType>& dc
)
{
	dimensions_ = dc.dimensions();
	value_.replace(d, dc.value());
}


template<class Type>
void tnbLib::dimensioned<Type>::read(const dictionary& dict)
{
	dict.lookup(name_) >> value_;
}


template<class Type>
bool tnbLib::dimensioned<Type>::readIfPresent(const dictionary& dict)
{
	return dict.readIfPresent(name_, value_);
}


template<class Type>
tnbLib::Istream&
tnbLib::dimensioned<Type>::read(Istream& is, const dictionary& readSet)
{
	// Read name
	is >> name_;

	// Read dimensionSet + multiplier
	scalar mult;
	dimensions_.read(is, mult, readSet);

	// Read value
	is >> value_;
	value_ *= mult;

	// Check state of Istream
	is.check
	(
		"Istream& dimensioned<Type>::read(Istream& is, const dictionary&)"
	);

	return is;
}


template<class Type>
tnbLib::Istream& tnbLib::dimensioned<Type>::read
(
	Istream& is,
	const HashTable<dimensionedScalar>& readSet
)
{
	// Read name
	is >> name_;

	// Read dimensionSet + multiplier
	scalar mult;
	dimensions_.read(is, mult, readSet);

	// Read value
	is >> value_;
	value_ *= mult;

	// Check state of Istream
	is.check
	(
		"Istream& dimensioned<Type>::read"
		"(Istream& is, const HashTable<dimensionedScalar>&)"
	);

	return is;
}


template<class Type>
tnbLib::Istream& tnbLib::dimensioned<Type>::read(Istream& is)
{
	// Read name
	is >> name_;

	// Read dimensionSet + multiplier
	scalar mult;
	dimensions_.read(is, mult);

	// Read value
	is >> value_;
	value_ *= mult;

	// Check state of Istream
	is.check
	(
		"Istream& dimensioned<Type>::read(Istream& is)"
	);

	return is;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
tnbLib::dimensioned<typename tnbLib::dimensioned<Type>::cmptType>
tnbLib::dimensioned<Type>::operator[]
(
	const direction d
	) const
{
	return component(d);
}


template<class Type>
void tnbLib::dimensioned<Type>::operator+=
(
	const dimensioned<Type>& dt
	)
{
	dimensions_ += dt.dimensions_;
	value_ += dt.value_;
}


template<class Type>
void tnbLib::dimensioned<Type>::operator-=
(
	const dimensioned<Type>& dt
	)
{
	dimensions_ -= dt.dimensions_;
	value_ -= dt.value_;
}


template<class Type>
void tnbLib::dimensioned<Type>::operator*=
(
	const scalar s
	)
{
	value_ *= s;
}


template<class Type>
void tnbLib::dimensioned<Type>::operator/=
(
	const scalar s
	)
{
	value_ /= s;
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

template<class Type, tnbLib::direction r>
tnbLib::dimensioned<typename tnbLib::powProduct<Type, r>::type>
tnbLib::pow(const dimensioned<Type>& dt, typename powProduct<Type, r>::type)
{
	return dimensioned<typename powProduct<Type, r>::type>
		(
			"pow(" + dt.name() + ',' + name(r) + ')',
			pow(dt.dimensions(), r),
			pow(dt.value(), 2)
			);
}


template<class Type>
tnbLib::dimensioned<typename tnbLib::outerProduct<Type, Type>::type>
tnbLib::sqr(const dimensioned<Type>& dt)
{
	return dimensioned<typename outerProduct<Type, Type>::type>
		(
			"sqr(" + dt.name() + ')',
			sqr(dt.dimensions()),
			sqr(dt.value())
			);
}

template<class Type>
tnbLib::dimensioned<tnbLib::scalar> tnbLib::magSqr(const dimensioned<Type>& dt)
{
	return dimensioned<scalar>
		(
			"magSqr(" + dt.name() + ')',
			magSqr(dt.dimensions()),
			magSqr(dt.value())
			);
}

template<class Type>
tnbLib::dimensioned<tnbLib::scalar> tnbLib::mag(const dimensioned<Type>& dt)
{
	return dimensioned<scalar>
		(
			"mag(" + dt.name() + ')',
			dt.dimensions(),
			mag(dt.value())
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::cmptMultiply
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
)
{
	return dimensioned<Type>
		(
			"cmptMultiply(" + dt1.name() + ',' + dt2.name() + ')',
			cmptMultiply(dt1.dimensions(), dt2.dimensions()),
			cmptMultiply(dt1.value(), dt2.value())
			);
}

template<class Type>
tnbLib::dimensioned<Type> tnbLib::cmptDivide
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
)
{
	return dimensioned<Type>
		(
			"cmptDivide(" + dt1.name() + ',' + dt2.name() + ')',
			cmptDivide(dt1.dimensions(), dt2.dimensions()),
			cmptDivide(dt1.value(), dt2.value())
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::max
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
)
{
	if (dt1.dimensions() != dt2.dimensions())
	{
		FatalErrorInFunction
			<< "dimensions of arguments are not equal"
			<< abort(FatalError);
	}

	return dimensioned<Type>
		(
			"max(" + dt1.name() + ',' + dt2.name() + ')',
			dt1.dimensions(),
			max(dt1.value(), dt2.value())
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::min
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
)
{
	if (dt1.dimensions() != dt2.dimensions())
	{
		FatalErrorInFunction
			<< "dimensions of arguments are not equal"
			<< abort(FatalError);
	}

	return dimensioned<Type>
		(
			"min(" + dt1.name() + ',' + dt2.name() + ')',
			dt1.dimensions(),
			min(dt1.value(), dt2.value())
			);
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class Type>
void tnbLib::writeEntry(Ostream& os, const dimensioned<Type>& dt)
{
	os << dt;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Istream& tnbLib::operator>>(Istream& is, dimensioned<Type>& dt)
{
	token nextToken(is);
	is.putBack(nextToken);

	// Check if the original format is used in which the name is provided
	// and reset the name to that read
	if (nextToken.isWord())
	{
		is >> dt.name_;
		is >> nextToken;
		is.putBack(nextToken);
	}

	// If the dimensions are provided reset the dimensions to those read
	scalar multiplier = 1.0;
	if (nextToken == token::BEGIN_SQR)
	{
		dt.dimensions_.read(is, multiplier);
	}

	// Read the value
	is >> dt.value_;
	dt.value_ *= multiplier;

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, dimensioned<Type>&)");

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const dimensioned<Type>& dt)
{
	// Write the name
	os << dt.name() << token::SPACE;

	// Write the dimensions
	scalar mult;
	dt.dimensions().write(os, mult);

	os << token::SPACE;

	// Write the value
	os << dt.value() / mult;

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const dimensioned<Type>&)");

	return os;
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::operator>
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
	)
{
	return dt1.value() > dt2.value();
}


template<class Type>
bool tnbLib::operator<
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
	)
{
	return dt1.value() < dt2.value();
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::operator+
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
	)
{
	return dimensioned<Type>
		(
			'(' + dt1.name() + '+' + dt2.name() + ')',
			dt1.dimensions() + dt2.dimensions(),
			dt1.value() + dt2.value()
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::operator-(const dimensioned<Type>& dt)
{
	return dimensioned<Type>
		(
			'-' + dt.name(),
			dt.dimensions(),
			-dt.value()
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::operator-
(
	const dimensioned<Type>& dt1,
	const dimensioned<Type>& dt2
	)
{
	return dimensioned<Type>
		(
			'(' + dt1.name() + '-' + dt2.name() + ')',
			dt1.dimensions() - dt2.dimensions(),
			dt1.value() - dt2.value()
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::operator*
(
	const dimensioned<scalar>& ds,
	const dimensioned<Type>& dt
	)
{
	return dimensioned<Type>
		(
			'(' + ds.name() + '*' + dt.name() + ')',
			ds.dimensions() * dt.dimensions(),
			ds.value() * dt.value()
			);
}


template<class Type>
tnbLib::dimensioned<Type> tnbLib::operator/
(
	const dimensioned<Type>& dt,
	const dimensioned<scalar>& ds
	)
{
	return dimensioned<Type>
		(
			'(' + dt.name() + '|' + ds.name() + ')',
			dt.dimensions() / ds.dimensions(),
			dt.value() / ds.value()
			);
}


//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tnbLib::dimensioned<typename tnbLib::product<Type1, Type2>::type>                  \
//tnbLib::operator op                                                              \
//(                                                                              \
//    const dimensioned<Type1>& dt1,                                             \
//    const dimensioned<Type2>& dt2                                              \
//)                                                                              \
//{                                                                              \
//    return dimensioned<typename product<Type1, Type2>::type>                   \
//    (                                                                          \
//        '(' + dt1.name() + #op + dt2.name() + ')',                             \
//        dt1.dimensions() op dt2.dimensions(),                                  \
//        dt1.value() op dt2.value()                                             \
//    );                                                                         \
//}                                                                              \
//                                                                               \
//template<class Type, class Form, class Cmpt, tnbLib::direction nCmpt>            \
//tnbLib::dimensioned<typename tnbLib::product<Type, Form>::type>                    \
//tnbLib::operator op                                                              \
//(                                                                              \
//    const dimensioned<Type>& dt1,                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& t2                                     \
//)                                                                              \
//{                                                                              \
//    return dimensioned<typename product<Type, Form>::type>                     \
//    (                                                                          \
//        '(' + dt1.name() + #op + name(t2) + ')',                               \
//        dt1.dimensions(),                                                      \
//        dt1.value() op static_cast<const Form&>(t2)                            \
//    );                                                                         \
//}                                                                              \
//                                                                               \
//template<class Type, class Form, class Cmpt, tnbLib::direction nCmpt>            \
//tnbLib::dimensioned<typename tnbLib::product<Form, Type>::type>                    \
//tnbLib::operator op                                                              \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& t1,                                    \
//    const dimensioned<Type>& dt2                                               \
//)                                                                              \
//{                                                                              \
//    return dimensioned<typename product<Form, Type>::type>                     \
//    (                                                                          \
//        '(' + name(t1) + #op + dt2.name() + ')',                               \
//        dt2.dimensions(),                                                      \
//        static_cast<const Form&>(t1) op dt2.value()                            \
//    );                                                                         \
//}


template <class Type1, class Type2>
tnbLib::dimensioned<typename tnbLib::outerProduct<Type1, Type2>::type> tnbLib::operator
*(const dimensioned<Type1>& dt1, const dimensioned<Type2>& dt2)
{
	return dimensioned<typename outerProduct<Type1, Type2>::type>('(' + dt1.name() + "*" + dt2.name() + ')',
		dt1.dimensions() * dt2.dimensions(),
		dt1.value() * dt2.value());
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::outerProduct<Type, Form>::type> tnbLib::operator
*(const dimensioned<Type>& dt1, const VectorSpace<Form, Cmpt, nCmpt>& t2)
{
	return dimensioned<typename outerProduct<Type, Form>::type>('(' + dt1.name() + "*" + name(t2) + ')', dt1.dimensions(),
		dt1.value() * static_cast<const Form&>(t2));
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::outerProduct<Form, Type>::type> tnbLib::operator
*(const VectorSpace<Form, Cmpt, nCmpt>& t1, const dimensioned<Type>& dt2)
{
	return dimensioned<typename outerProduct<Form, Type>::type>('(' + name(t1) + "*" + dt2.name() + ')', dt2.dimensions(),
		static_cast<const Form&>(t1) * dt2.value());
}

template <class Type1, class Type2>
tnbLib::dimensioned<typename tnbLib::crossProduct<Type1, Type2>::type> tnbLib::operator
^(const dimensioned<Type1>& dt1, const dimensioned<Type2>& dt2)
{
	return dimensioned<typename crossProduct<Type1, Type2>::type>('(' + dt1.name() + "^" + dt2.name() + ')',
		dt1.dimensions() ^ dt2.dimensions(),
		dt1.value() ^ dt2.value());
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::crossProduct<Type, Form>::type> tnbLib::operator
^(const dimensioned<Type>& dt1, const VectorSpace<Form, Cmpt, nCmpt>& t2)
{
	return dimensioned<typename crossProduct<Type, Form>::type>('(' + dt1.name() + "^" + name(t2) + ')', dt1.dimensions(),
		dt1.value() ^ static_cast<const Form&>(t2));
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::crossProduct<Form, Type>::type> tnbLib::operator
^(const VectorSpace<Form, Cmpt, nCmpt>& t1, const dimensioned<Type>& dt2)
{
	return dimensioned<typename crossProduct<Form, Type>::type>('(' + name(t1) + "^" + dt2.name() + ')', dt2.dimensions(),
		static_cast<const Form&>(t1) ^ dt2.value());
}

template <class Type1, class Type2>
tnbLib::dimensioned<typename tnbLib::innerProduct<Type1, Type2>::type> tnbLib::operator
&(const dimensioned<Type1>& dt1, const dimensioned<Type2>& dt2)
{
	return dimensioned<typename innerProduct<Type1, Type2>::type>('(' + dt1.name() + "&" + dt2.name() + ')',
		dt1.dimensions() & dt2.dimensions(),
		dt1.value() & dt2.value());
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::innerProduct<Type, Form>::type> tnbLib::operator
&(const dimensioned<Type>& dt1, const VectorSpace<Form, Cmpt, nCmpt>& t2)
{
	return dimensioned<typename innerProduct<Type, Form>::type>('(' + dt1.name() + "&" + name(t2) + ')', dt1.dimensions(),
		dt1.value() & static_cast<const Form&>(t2));
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::innerProduct<Form, Type>::type> tnbLib::operator
&(const VectorSpace<Form, Cmpt, nCmpt>& t1, const dimensioned<Type>& dt2)
{
	return dimensioned<typename innerProduct<Form, Type>::type>('(' + name(t1) + "&" + dt2.name() + ')', dt2.dimensions(),
		static_cast<const Form&>(t1) & dt2.value());
}

template <class Type1, class Type2>
tnbLib::dimensioned<typename tnbLib::scalarProduct<Type1, Type2>::type> tnbLib::operator
&&(const dimensioned<Type1>& dt1, const dimensioned<Type2>& dt2)
{
	return dimensioned<typename scalarProduct<Type1, Type2>::type>('(' + dt1.name() + "&&" + dt2.name() + ')',
		dt1.dimensions() && dt2.dimensions(),
		dt1.value() && dt2.value());
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::scalarProduct<Type, Form>::type> tnbLib::operator
&&(const dimensioned<Type>& dt1, const VectorSpace<Form, Cmpt, nCmpt>& t2)
{
	return dimensioned<typename scalarProduct<Type, Form>::type>('(' + dt1.name() + "&&" + name(t2) + ')',
		dt1.dimensions(),
		dt1.value() && static_cast<const Form&>(t2));
}

template <class Type, class Form, class Cmpt, tnbLib::direction nCmpt>
tnbLib::dimensioned<typename tnbLib::scalarProduct<Form, Type>::type> tnbLib::operator
&&(const VectorSpace<Form, Cmpt, nCmpt>& t1, const dimensioned<Type>& dt2)
{
	return dimensioned<typename scalarProduct<Form, Type>::type>('(' + name(t1) + "&&" + dt2.name() + ')',
		dt2.dimensions(),
		static_cast<const Form&>(t1) && dt2.value());
}

//#undef PRODUCT_OPERATOR


// ************************************************************************* //