#include <subBody.hxx>

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::subBody::write(Ostream& os) const
{
	writeEntry(os, "master", masterName_);

	writeEntry(os, "transform", masterXT_);
}


// ************************************************************************* //