#include <janafThermo.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::janafThermo<EquationOfState>::checkInputData() const
{
	if (Tlow_ >= Thigh_)
	{
		FatalErrorInFunction
			<< "Tlow(" << Tlow_ << ") >= Thigh(" << Thigh_ << ')'
			<< exit(FatalError);
	}

	if (Tcommon_ <= Tlow_)
	{
		FatalErrorInFunction
			<< "Tcommon(" << Tcommon_ << ") <= Tlow(" << Tlow_ << ')'
			<< exit(FatalError);
	}

	if (Tcommon_ > Thigh_)
	{
		FatalErrorInFunction
			<< "Tcommon(" << Tcommon_ << ") > Thigh(" << Thigh_ << ')'
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::janafThermo<EquationOfState>::janafThermo(const dictionary& dict)
	:
	EquationOfState(dict),
	Tlow_(readScalar(dict.subDict("thermodynamics").lookup("Tlow"))),
	Thigh_(readScalar(dict.subDict("thermodynamics").lookup("Thigh"))),
	Tcommon_(readScalar(dict.subDict("thermodynamics").lookup("Tcommon"))),
	highCpCoeffs_(dict.subDict("thermodynamics").lookup("highCpCoeffs")),
	lowCpCoeffs_(dict.subDict("thermodynamics").lookup("lowCpCoeffs"))
{
	// Convert coefficients to mass-basis
	for (label coefLabel = 0; coefLabel < nCoeffs_; coefLabel++)
	{
		highCpCoeffs_[coefLabel] *= this->R();
		lowCpCoeffs_[coefLabel] *= this->R();
	}

	checkInputData();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::janafThermo<EquationOfState>::write(Ostream& os) const
{
	EquationOfState::write(os);

	// Convert coefficients back to dimensionless form
	coeffArray highCpCoeffs;
	coeffArray lowCpCoeffs;
	for (label coefLabel = 0; coefLabel < nCoeffs_; coefLabel++)
	{
		highCpCoeffs[coefLabel] = highCpCoeffs_[coefLabel] / this->R();
		lowCpCoeffs[coefLabel] = lowCpCoeffs_[coefLabel] / this->R();
	}

	dictionary dict("thermodynamics");
	dict.add("Tlow", Tlow_);
	dict.add("Thigh", Thigh_);
	dict.add("Tcommon", Tcommon_);
	dict.add("highCpCoeffs", highCpCoeffs);
	dict.add("lowCpCoeffs", lowCpCoeffs);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const janafThermo<EquationOfState>& jt
	)
{
	jt.write(os);
	return os;
}


// ************************************************************************* //