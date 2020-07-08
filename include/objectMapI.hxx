#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	inline objectMap::objectMap()
		:
		index_(-1),
		masterObjects_(0)
	{}


	inline objectMap::objectMap(const label index, const labelList& master)
		:
		index_(index),
		masterObjects_(master)
	{}


	inline objectMap::objectMap(Istream& is)
	{
		// Read beginning of objectMap
		is.readBegin("objectMap");

		is >> index_ >> static_cast<labelList&>(masterObjects_);

		// Read master of objectMap
		is.readEnd("objectMap");

		// Check state of Istream
		is.check("objectMap::objectMap(Istream&)");
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	label& objectMap::index()
	{
		return index_;
	}


	inline label objectMap::index() const
	{
		return index_;
	}


	inline labelList& objectMap::masterObjects()
	{
		return masterObjects_;
	}


	inline const labelList& objectMap::masterObjects() const
	{
		return masterObjects_;
	}


	// * * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * //

	inline bool operator==(const objectMap& a, const objectMap& b)
	{
		return
			(
			(a.index_ == b.index_) && (a.masterObjects_ == b.masterObjects_)
				);
	}


	inline bool operator!=(const objectMap& a, const objectMap& b)
	{
		return (!(a == b));
	}


	// * * * * * * * * * * * * * * * Ostream Operator *  * * * * * * * * * * * * //

	inline Ostream& operator<<(Ostream& os, const objectMap& a)
	{
		os << token::BEGIN_LIST
			<< a.index_ << token::SPACE
			<< a.masterObjects_
			<< token::END_LIST;

		// Check state of Ostream
		os.check("Ostream& operator<<(Ostream&, const objectMap&)");

		return os;
	}


	inline Istream& operator>>(Istream& is, objectMap& a)
	{
		is.readBegin("objectMap");
		is >> a.index_ >> a.masterObjects_;
		is.readEnd("objectMap");

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, objectMap&)");

		return is;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // Master namespace tnbLib

// ************************************************************************* //