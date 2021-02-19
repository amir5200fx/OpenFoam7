#include <solidificationMeltingSource.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::fv::solidificationMeltingSource::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.lookup("Tsol") >> Tsol_;
		coeffs_.readIfPresent("Tliq", Tliq_);
		coeffs_.readIfPresent("alpha1e", alpha1e_);
		coeffs_.lookup("L") >> L_;

		coeffs_.readIfPresent("relax", relax_);

		mode_ = thermoModeTypeNames_.read(coeffs_.lookup("thermoMode"));

		coeffs_.lookup("rhoRef") >> rhoRef_;
		coeffs_.readIfPresent("T", TName_);
		coeffs_.readIfPresent("U", UName_);

		coeffs_.readIfPresent("Cu", Cu_);
		coeffs_.readIfPresent("q", q_);

		coeffs_.readIfPresent("beta", beta_);

		return true;
	}
	else
	{
		return false;
	}

	return false;
}


// ************************************************************************* //