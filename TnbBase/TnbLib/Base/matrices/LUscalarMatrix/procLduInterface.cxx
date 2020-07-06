#include <procLduInterface.hxx>

#include <lduInterfaceField.hxx>
#include <cyclicLduInterface.hxx>
#include <processorLduInterface.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::procLduInterface::procLduInterface
(
	const lduInterfaceField& interface,
	const scalarField& coeffs
)
	:
	faceCells_(interface.interface().faceCells()),
	coeffs_(coeffs),
	myProcNo_(-1),
	neighbProcNo_(-1),
	tag_(-1),
	comm_(-1)
{
	if (isA<processorLduInterface>(interface.interface()))
	{
		const processorLduInterface& pldui =
			refCast<const processorLduInterface>(interface.interface());

		myProcNo_ = pldui.myProcNo();
		neighbProcNo_ = pldui.neighbProcNo();
		tag_ = pldui.tag();
		comm_ = pldui.comm();
	}
	else if (isA<cyclicLduInterface>(interface.interface()))
	{
	}
	else
	{
		FatalErrorInFunction
			<< "Unknown lduInterface type "
			<< interface.interface().type()
			<< exit(FatalError);
	}
}


tnbLib::procLduInterface::procLduInterface(Istream& is)
	:
	faceCells_(is),
	coeffs_(is),
	myProcNo_(readLabel(is)),
	neighbProcNo_(readLabel(is)),
	tag_(readLabel(is)),
	comm_(readLabel(is))
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const procLduInterface& cldui)
{
	os << cldui.faceCells_
		<< cldui.coeffs_
		<< cldui.myProcNo_
		<< cldui.neighbProcNo_
		<< cldui.tag_
		<< cldui.comm_;

	return os;
}


// ************************************************************************* //