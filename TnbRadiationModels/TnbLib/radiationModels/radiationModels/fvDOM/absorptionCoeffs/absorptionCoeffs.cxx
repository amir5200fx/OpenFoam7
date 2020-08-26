#include <absorptionCoeffs.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionCoeffs::~absorptionCoeffs()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::radiationModels::absorptionCoeffs::checkT(const scalar T) const
{
	if (T < Tlow_ || T > Thigh_)
	{
		WarningInFunction
			<< "using absorptionCoeffs out of temperature range:" << nl
			<< "    " << Tlow_ << " -> " << Thigh_ << ";  T = " << T
			<< nl << endl;
	}
}


const tnbLib::radiationModels::absorptionCoeffs::coeffArray&
tnbLib::radiationModels::absorptionCoeffs::coeffs
(
	const scalar T
) const
{
	checkT(T);

	if (T < Tcommon_)
	{
		return lowACoeffs_;
	}
	else
	{
		return highACoeffs_;
	}
}


void tnbLib::radiationModels::absorptionCoeffs::initialise(const dictionary& dict)
{
	dict.lookup("Tcommon") >> Tcommon_;
	dict.lookup("Tlow") >> Tlow_;
	dict.lookup("Thigh") >> Thigh_;
	dict.lookup("invTemp") >> invTemp_;
	dict.lookup("loTcoeffs") >> lowACoeffs_;
	dict.lookup("hiTcoeffs") >> highACoeffs_;
}


// ************************************************************************* //