#include <coalCloudList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coalCloudList::coalCloudList
(
	const volScalarField& rho,
	const volVectorField& U,
	const dimensionedVector& g,
	const SLGThermo& slgThermo
)
	:
	PtrList<coalCloud>(),
	mesh_(rho.mesh())
{
	IOdictionary props
	(
		IOobject
		(
			"coalCloudList",
			mesh_.time().constant(),
			mesh_,
			IOobject::MUST_READ
		)
	);

	const wordHashSet cloudNames(wordList(props.lookup("clouds")));

	setSize(cloudNames.size());

	label i = 0;
	forAllConstIter(wordHashSet, cloudNames, iter)
	{
		const word& name = iter.key();

		Info << "creating cloud: " << name << endl;

		set
		(
			i++,
			new coalCloud
			(
				name,
				rho,
				U,
				g,
				slgThermo
			)
		);

		Info << endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::coalCloudList::evolve()
{
	forAll(*this, i)
	{
		operator[](i).evolve();
	}
}


// ************************************************************************* //