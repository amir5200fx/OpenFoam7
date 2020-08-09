#include <twoPhaseMixture.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::twoPhaseMixture::twoPhaseMixture
(
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	phase1Name_(wordList(dict.lookup("phases"))[0]),
	phase2Name_(wordList(dict.lookup("phases"))[1]),

	alpha1_
	(
		tnbLib::IOobject
		(
			IOobject::groupName("alpha", phase1Name_),
			mesh.time().timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	),

	alpha2_
	(
		tnbLib::IOobject
		(
			IOobject::groupName("alpha", phase2Name_),
			mesh.time().timeName(),
			mesh
		),
		1.0 - alpha1_
	)
{}


// ************************************************************************* //