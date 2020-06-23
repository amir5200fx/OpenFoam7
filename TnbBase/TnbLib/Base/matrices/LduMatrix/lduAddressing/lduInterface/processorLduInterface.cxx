#include <processorLduInterface.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorLduInterface, 0);
}


// * * * * * * * * * * * * * Private Member Functions *  * * * * * * * * * * //

void tnbLib::processorLduInterface::resizeBuf
(
	List<char>& buf,
	const label size
) const
{
	if (buf.size() < size)
	{
		buf.setSize(size);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorLduInterface::processorLduInterface()
	:
	sendBuf_(0),
	receiveBuf_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorLduInterface::~processorLduInterface()
{}


// ************************************************************************* //