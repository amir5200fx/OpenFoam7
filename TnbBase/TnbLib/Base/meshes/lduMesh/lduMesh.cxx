#include <lduMesh.hxx>

#include <objectRegistry.hxx>
#include <processorLduInterface.hxx>

#include <lduInterfacePtrsList.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(lduMesh, 0);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::objectRegistry& tnbLib::lduMesh::thisDb() const
{
	NotImplemented;
	const objectRegistry* orPtr_ = nullptr;
	return *orPtr_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<lduMesh>& ip)
{
	const lduMesh& ldum = ip.t_;
	const lduAddressing& addr = ldum.lduAddr();
	const lduInterfacePtrsList interfaces = ldum.interfaces();

	os << "lduMesh :"
		<< " size:" << addr.size()
		<< " l:" << addr.lowerAddr().size()
		<< " u:" << addr.upperAddr().size()
		<< " interfaces:" << interfaces.size()
		<< " comm:" << ldum.comm()
		<< endl;
	label nCouples = 0;
	forAll(interfaces, i)
	{
		if (interfaces.set(i))
		{
			const labelUList& faceCells = addr.patchAddr(i);
			nCouples += faceCells.size();

			if (isA<processorLduInterface>(interfaces[i]))
			{
				const processorLduInterface& pi = refCast
					<
					const processorLduInterface
					>(interfaces[i]);

				os << "    patch:" << i
					<< " type:" << interfaces[i].type()
					<< " size:" << faceCells.size()
					<< " myProcNo:" << pi.myProcNo()
					<< " neighbProcNo:" << pi.neighbProcNo()
					<< " comm:" << pi.comm()
					<< endl;
			}
			else
			{
				os << "    patch:" << i
					<< " type:" << interfaces[i].type()
					<< " size:" << faceCells.size()
					<< endl;
			}
		}
	}
	os << "    Interface faces/cells:" << scalar(nCouples) / addr.size()
		<< endl;


	// Print actual contents
	if (lduMesh::debug)
	{
		const labelList& l = addr.lowerAddr();
		const labelList& u = addr.upperAddr();
		forAll(l, facei)
		{
			os << "        face:" << facei << " l:" << l[facei]
				<< " u:" << u[facei] << endl;
		}
		forAll(interfaces, i)
		{
			if (interfaces.set(i))
			{
				const labelUList& faceCells = addr.patchAddr(i);
				if (faceCells.size())
				{
					os << "    patch:" << i
						<< " type:" << interfaces[i].type() << endl;

					if (isA<processorLduInterface>(interfaces[i]))
					{
						const processorLduInterface& pi = refCast
							<
							const processorLduInterface
							>(interfaces[i]);

						os << "    myProcNo:" << pi.myProcNo()
							<< " neighbProcNo:" << pi.neighbProcNo()
							<< " comm:" << pi.comm()
							<< endl;
					}

					forAll(faceCells, i)
					{
						os << "        " << i << " own:" << faceCells[i]
							<< endl;
					}
				}
			}
		}
	}

	os.check("Ostream& operator<<(Ostream&, const lduMesh&");

	return os;
}


// ************************************************************************* //