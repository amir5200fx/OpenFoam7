#pragma once
#include <iostream>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::token::clear()
{
	if (type_ == WORD)
	{
		delete wordTokenPtr_;
	}
	else if (type_ == STRING || type_ == VARIABLE || type_ == VERBATIMSTRING)
	{
		delete stringTokenPtr_;
	}
	else if (type_ == LONG_DOUBLE_SCALAR)
	{
		delete longDoubleScalarTokenPtr_;
	}
	else if (type_ == COMPOUND)
	{
		if (compoundTokenPtr_->unique())
		{
			delete compoundTokenPtr_;
		}
		else
		{
			compoundTokenPtr_->refCount::operator--();
		}
	}

	type_ = UNDEFINED;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::token::token()
	:
	type_(UNDEFINED),
	lineNumber_(0)
{}


inline tnbLib::token::token(const token& t)
	:
	type_(t.type_),
	lineNumber_(t.lineNumber_)
{
	switch (type_)
	{
	case token::UNDEFINED:
		break;

	case PUNCTUATION:
		punctuationToken_ = t.punctuationToken_;
		break;

	case WORD:
		wordTokenPtr_ = new word(*t.wordTokenPtr_);
		break;

	case STRING:
	case VARIABLE:
	case VERBATIMSTRING:
		stringTokenPtr_ = new string(*t.stringTokenPtr_);
		break;

	case LABEL:
		labelToken_ = t.labelToken_;
		break;

	case FLOAT_SCALAR:
		floatScalarToken_ = t.floatScalarToken_;
		break;

	case DOUBLE_SCALAR:
		doubleScalarToken_ = t.doubleScalarToken_;
		break;

	case LONG_DOUBLE_SCALAR:
		longDoubleScalarTokenPtr_ =
			new longDoubleScalar(*t.longDoubleScalarTokenPtr_);
		break;

	case COMPOUND:
		compoundTokenPtr_ = t.compoundTokenPtr_;
		compoundTokenPtr_->refCount::operator++();
		break;

	case token::ERROR:
		break;
	}
}


inline tnbLib::token::token(punctuationToken p, label lineNumber)
	:
	type_(PUNCTUATION),
	punctuationToken_(p),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const word& w, label lineNumber)
	:
	type_(WORD),
	wordTokenPtr_(new word(w)),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const string& s, label lineNumber)
	:
	type_(STRING),
	stringTokenPtr_(new string(s)),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const label l, label lineNumber)
	:
	type_(LABEL),
	labelToken_(l),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const floatScalar s, label lineNumber)
	:
	type_(FLOAT_SCALAR),
	floatScalarToken_(s),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const doubleScalar s, label lineNumber)
	:
	type_(DOUBLE_SCALAR),
	doubleScalarToken_(s),
	lineNumber_(lineNumber)
{}


inline tnbLib::token::token(const longDoubleScalar s, label lineNumber)
	:
	type_(LONG_DOUBLE_SCALAR),
	longDoubleScalarTokenPtr_(new longDoubleScalar(s)),
	lineNumber_(lineNumber)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

inline tnbLib::token::~token()
{
	clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::token::tokenType  tnbLib::token::type() const
{
	return type_;
}

inline tnbLib::token::tokenType&  tnbLib::token::type()
{
	return type_;
}

inline bool tnbLib::token::good() const
{
	return (type_ != ERROR && type_ != UNDEFINED);
}

inline bool tnbLib::token::undefined() const
{
	return (type_ == UNDEFINED);
}

inline bool tnbLib::token::error() const
{
	return (type_ == ERROR);
}

inline bool tnbLib::token::isPunctuation() const
{
	return (type_ == PUNCTUATION);
}

inline tnbLib::token::punctuationToken  tnbLib::token::pToken() const
{
	if (type_ == PUNCTUATION)
	{
		return punctuationToken_;
	}
	else
	{
		parseError("punctuation character");
		return NULL_TOKEN;
	}
}

inline bool tnbLib::token::isWord() const
{
	return (type_ == WORD);
}

inline const tnbLib::word& tnbLib::token::wordToken() const
{
	if (type_ == WORD)
	{
		return *wordTokenPtr_;
	}
	else
	{
		parseError(word::typeName);
		return word::null;
	}
}

inline bool tnbLib::token::isVariable() const
{
	return (type_ == VARIABLE);
}

inline bool tnbLib::token::isString() const
{
	return (type_ == STRING || type_ == VARIABLE || type_ == VERBATIMSTRING);
}

inline const tnbLib::string& tnbLib::token::stringToken() const
{
	if (type_ == STRING || type_ == VARIABLE || type_ == VERBATIMSTRING)
	{
		return *stringTokenPtr_;
	}
	else
	{
		parseError(string::typeName);
		return string::null;
	}
}

inline bool tnbLib::token::isLabel() const
{
	return (type_ == LABEL);
}

inline tnbLib::label tnbLib::token::labelToken() const
{
	if (type_ == LABEL)
	{
		return labelToken_;
	}
	else
	{
		parseError(pTraits<label>::typeName);
		return 0;
	}
}

inline bool tnbLib::token::isFloatScalar() const
{
	return (type_ == FLOAT_SCALAR);
}

inline tnbLib::floatScalar tnbLib::token::floatScalarToken() const
{
	if (type_ == FLOAT_SCALAR)
	{
		return floatScalarToken_;
	}
	else
	{
		parseError("floatScalar");
		return 0.0;
	}
}


inline bool tnbLib::token::isDoubleScalar() const
{
	return (type_ == DOUBLE_SCALAR);
}

inline tnbLib::doubleScalar tnbLib::token::doubleScalarToken() const
{
	if (type_ == DOUBLE_SCALAR)
	{
		return doubleScalarToken_;
	}
	else
	{
		parseError("doubleScalar");
		return 0.0;
	}
}


inline bool tnbLib::token::isLongDoubleScalar() const
{
	return (type_ == LONG_DOUBLE_SCALAR);
}

inline tnbLib::longDoubleScalar tnbLib::token::longDoubleScalarToken() const
{
	if (type_ == LONG_DOUBLE_SCALAR)
	{
		return *longDoubleScalarTokenPtr_;
	}
	else
	{
		parseError("longDoubleScalar");
		return 0.0;
	}
}


inline bool tnbLib::token::isScalar() const
{
	return
		(
			type_ == FLOAT_SCALAR
			|| type_ == DOUBLE_SCALAR
			|| type_ == LONG_DOUBLE_SCALAR
			);
}

inline tnbLib::scalar tnbLib::token::scalarToken() const
{
	if (type_ == FLOAT_SCALAR)
	{
		return floatScalarToken_;
	}
	else if (type_ == DOUBLE_SCALAR)
	{
		return doubleScalarToken_;
	}
	else if (type_ == LONG_DOUBLE_SCALAR)
	{
		return *longDoubleScalarTokenPtr_;
	}
	else
	{
		parseError(pTraits<scalar>::typeName);
		return 0.0;
	}
}

inline bool tnbLib::token::isNumber() const
{
	return (type_ == LABEL || isScalar());
}

inline tnbLib::scalar tnbLib::token::number() const
{
	if (type_ == LABEL)
	{
		return labelToken_;
	}
	else if (isScalar())
	{
		return scalarToken();
	}
	else
	{
		parseError("number (label or scalar)");
		return 0.0;
	}
}

inline bool tnbLib::token::isCompound() const
{
	return (type_ == COMPOUND);
}

inline const tnbLib::token::compound& tnbLib::token::compoundToken() const
{
	if (type_ == COMPOUND)
	{
		return *compoundTokenPtr_;
	}
	else
	{
		parseError("compound");
		return *compoundTokenPtr_;
	}
}


inline tnbLib::label tnbLib::token::lineNumber() const
{
	return lineNumber_;
}

inline tnbLib::label& tnbLib::token::lineNumber()
{
	return lineNumber_;
}


inline void tnbLib::token::setBad()
{
	clear();
	type_ = ERROR;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::token::operator=(const token& t)
{
	clear();
	type_ = t.type_;

	switch (type_)
	{
	case token::UNDEFINED:
		break;

	case PUNCTUATION:
		punctuationToken_ = t.punctuationToken_;
		break;

	case WORD:
		wordTokenPtr_ = new word(*t.wordTokenPtr_);
		break;

	case STRING:
	case VARIABLE:
	case VERBATIMSTRING:
		stringTokenPtr_ = new string(*t.stringTokenPtr_);
		break;

	case LABEL:
		labelToken_ = t.labelToken_;
		break;

	case FLOAT_SCALAR:
		floatScalarToken_ = t.floatScalarToken_;
		break;

	case DOUBLE_SCALAR:
		doubleScalarToken_ = t.doubleScalarToken_;
		break;

	case LONG_DOUBLE_SCALAR:
		longDoubleScalarTokenPtr_ =
			new longDoubleScalar(*t.longDoubleScalarTokenPtr_);
		break;

	case COMPOUND:
		compoundTokenPtr_ = t.compoundTokenPtr_;
		compoundTokenPtr_->refCount::operator++();
		break;

	case token::ERROR:
		break;
	}

	lineNumber_ = t.lineNumber_;
}

inline void tnbLib::token::operator=(const punctuationToken p)
{
	clear();
	type_ = PUNCTUATION;
	punctuationToken_ = p;
}

inline void tnbLib::token::operator=(word* wPtr)
{
	clear();
	type_ = WORD;
	wordTokenPtr_ = wPtr;
}

inline void tnbLib::token::operator=(const word& w)
{
	operator=(new word(w));
}

inline void tnbLib::token::operator=(string* sPtr)
{
	clear();
	type_ = STRING;
	stringTokenPtr_ = sPtr;
}

inline void tnbLib::token::operator=(const string& s)
{
	operator=(new string(s));
}

inline void tnbLib::token::operator=(const label l)
{
	clear();
	type_ = LABEL;
	labelToken_ = l;
}

inline void tnbLib::token::operator=(const floatScalar s)
{
	clear();
	type_ = FLOAT_SCALAR;
	floatScalarToken_ = s;
}

inline void tnbLib::token::operator=(const doubleScalar s)
{
	clear();
	type_ = DOUBLE_SCALAR;
	doubleScalarToken_ = s;
}

inline void tnbLib::token::operator=(const longDoubleScalar s)
{
	clear();
	type_ = LONG_DOUBLE_SCALAR;
	longDoubleScalarTokenPtr_ = new longDoubleScalar(s);
}

inline void tnbLib::token::operator=(tnbLib::token::compound* cPtr)
{
	clear();
	type_ = COMPOUND;
	compoundTokenPtr_ = cPtr;
}


inline bool tnbLib::token::operator==(const token& t) const
{
	if (type_ != t.type_)
	{
		return false;
	}

	switch (type_)
	{
	case token::UNDEFINED:
		return true;

	case PUNCTUATION:
		return punctuationToken_ == t.punctuationToken_;

	case WORD:
		return *wordTokenPtr_ == *t.wordTokenPtr_;

	case STRING:
	case VARIABLE:
	case VERBATIMSTRING:
		return *stringTokenPtr_ == *t.stringTokenPtr_;

	case LABEL:
		return labelToken_ == t.labelToken_;

	case FLOAT_SCALAR:
		return equal(floatScalarToken_, t.floatScalarToken_);

	case DOUBLE_SCALAR:
		return equal(doubleScalarToken_, t.doubleScalarToken_);

	case LONG_DOUBLE_SCALAR:
		return equal
		(
			*longDoubleScalarTokenPtr_,
			*t.longDoubleScalarTokenPtr_
		);

	case COMPOUND:
		return compoundTokenPtr_ == t.compoundTokenPtr_;

	case token::ERROR:
		return true;
	}

	return false;
}

inline bool tnbLib::token::operator==(const punctuationToken p) const
{
	return (type_ == PUNCTUATION && punctuationToken_ == p);
}

inline bool tnbLib::token::operator==(const word& w) const
{
	return (type_ == WORD && wordToken() == w);
}

inline bool tnbLib::token::operator==(const string& s) const
{
	return
		(
		(type_ == STRING || type_ == VARIABLE || type_ == VERBATIMSTRING)
			&& stringToken() == s
			);
}

inline bool tnbLib::token::operator==(const label l) const
{
	return (type_ == LABEL && labelToken_ == l);
}

inline bool tnbLib::token::operator==(const floatScalar s) const
{
	return (type_ == FLOAT_SCALAR && equal(floatScalarToken_, s));
}

inline bool tnbLib::token::operator==(const doubleScalar s) const
{
	return (type_ == DOUBLE_SCALAR && equal(doubleScalarToken_, s));
}

inline bool tnbLib::token::operator==(const longDoubleScalar s) const
{
	return
		(
			type_ == LONG_DOUBLE_SCALAR && equal(*longDoubleScalarTokenPtr_, s)
			);
}

inline bool tnbLib::token::operator!=(const token& t) const
{
	return !operator==(t);
}

inline bool tnbLib::token::operator!=(const punctuationToken p) const
{
	return !operator==(p);
}

inline bool tnbLib::token::operator!=(const word& w) const
{
	return !operator==(w);
}

inline bool tnbLib::token::operator!=(const string& s) const
{
	return !operator==(s);
}

inline bool tnbLib::token::operator!=(const floatScalar s) const
{
	return !operator==(s);
}

inline bool tnbLib::token::operator!=(const doubleScalar s) const
{
	return !operator==(s);
}

inline bool tnbLib::token::operator!=(const longDoubleScalar s) const
{
	return !operator==(s);
}

inline bool tnbLib::token::operator!=(const label l) const
{
	return !operator==(l);
}


// ************************************************************************* //