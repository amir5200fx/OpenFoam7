#include <thermodynamicConstants.hxx>

#include <physicoChemicalConstants.hxx>
#include <fundamentalConstants.hxx> // added by amir


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{
		namespace thermodynamic
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

				// Note: the 1e3 converts from /mol to /kmol for consistency with the
				// SI choice of kg rather than g for mass.
				// This is not appropriate for USCS and will be changed to an entry in
				// the DimensionedConstants dictionary in etc/controlDict
			const scalar RR = 1e3*physicoChemical::R.value();

			const scalar Pstd = standard::Pstd.value();
			const scalar Tstd = standard::Tstd.value();

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermodynamic
	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //