#include <referredWallFace.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::referredWallFace::referredWallFace()
	:
	face(),
	pts_(),
	patchi_()
{}


tnbLib::referredWallFace::referredWallFace
(
	const face& f,
	const pointField& pts,
	label patchi
)
	:
	face(f),
	pts_(pts),
	patchi_(patchi)
{
	if (this->size() != pts_.size())
	{
		FatalErrorInFunction
			<< "Face and pointField are not the same size. " << nl << (*this)
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::referredWallFace::~referredWallFace()
{}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

bool tnbLib::referredWallFace::operator==(const referredWallFace& rhs) const
{
	return
		(
			static_cast<const face&>(rhs) == static_cast<face>(*this)
			&& rhs.pts_ == pts_
			&& rhs.patchi_ == patchi_
			);
}


bool tnbLib::referredWallFace::operator!=(const referredWallFace& rhs) const
{
	return !(*this == rhs);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, referredWallFace& rWF)
{
	is >> static_cast<face&>(rWF) >> rWF.pts_ >> rWF.patchi_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& "
		"tnbLib::operator>>(tnbLib::Istream&, tnbLib::referredWallFace&)"
	);

	return is;
}


FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const referredWallFace& rWF)
{
	os << static_cast<const face&>(rWF) << token::SPACE
		<< rWF.pts_ << token::SPACE
		<< rWF.patchi_;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::referredWallFace&)"
	);

	return os;
}


// ************************************************************************* //