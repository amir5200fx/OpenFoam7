#pragma once
// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const Polynomial<PolySize>& poly
	)
{
	os << static_cast
		<VectorSpace<Polynomial<PolySize>, scalar, PolySize>>(poly);

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<(Ostream&, const Polynomial<PolySize>&)"
	);

	return os;
}


// ************************************************************************* //