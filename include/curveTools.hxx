#pragma once
#ifndef _curveTools_Header
#define _curveTools_Header

#include <scalar.hxx>
#include <vector.hxx>
#include <curve.hxx>
#include <char.hxx>
#include <List.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

#define curveSmall 1.0e-8
#define curveGreat 1.0e8

	typedef List<char> charList;
	typedef List<charList> charListList;


	scalar distance(const vector&, const vector&);


	bool stepForwardsToNextPoint
	(
		const vector&,
		vector&,
		label&,
		label&,
		scalar,
		const curve&
	);


	bool stepBackwardsToNextPoint
	(
		const vector&,
		vector&,
		label&,
		label&,
		scalar,
		const curve&
	);


	bool interpolate
	(
		const vector&,
		const vector&,
		const vector&,
		vector&,
		scalar
	);


	bool XstepForwardsToNextPoint
	(
		const vector&,
		vector&,
		label&,
		label&,
		scalar,
		const curve&
	);


	bool Xinterpolate
	(
		const vector&,
		const vector&,
		const vector&,
		vector&,
		scalar
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


#endif // !_curveTools_Header
