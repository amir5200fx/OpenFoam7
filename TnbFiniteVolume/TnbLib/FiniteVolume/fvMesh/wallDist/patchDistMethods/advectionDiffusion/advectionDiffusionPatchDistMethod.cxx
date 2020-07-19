//#include <advectionDiffusionPatchDistMethod.hxx>
//
//#include <surfaceInterpolate.hxx>
//#include <fvcGrad.hxx>
//#include <fvcDiv.hxx>
//#include <fvmDiv.hxx>
//#include <fvmLaplacian.hxx>
//#include <fvmSup.hxx>
//#include <addToRunTimeSelectionTable.hxx>
//
//#include <fixedValueFvPatchFields.hxx>
//#include <zeroGradientFvPatchFields.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//namespace Foam
//{
//	namespace patchDistMethods
//	{
//		defineTypeNameAndDebug(advectionDiffusion, 0);
//		addToRunTimeSelectionTable(patchDistMethod, advectionDiffusion, dictionary);
//	}
//}
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//Foam::patchDistMethods::advectionDiffusion::advectionDiffusion
//(
//	const dictionary& dict,
//	const fvMesh& mesh,
//	const labelHashSet& patchIDs
//)
//	:
//	patchDistMethod(mesh, patchIDs),
//	coeffs_(dict.optionalSubDict(type() + "Coeffs")),
//	pdmPredictor_
//	(
//		patchDistMethod::New
//		(
//			coeffs_,
//			mesh,
//			patchIDs
//		)
//	),
//	epsilon_(coeffs_.lookupOrDefault<scalar>("epsilon", 0.1)),
//	tolerance_(coeffs_.lookupOrDefault<scalar>("tolerance", 1e-3)),
//	maxIter_(coeffs_.lookupOrDefault<int>("maxIter", 10)),
//	predicted_(false)
//{}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//bool Foam::patchDistMethods::advectionDiffusion::correct(volScalarField& y)
//{
//	return correct(y, const_cast<volVectorField&>(volVectorField::null()));
//}
//
//
//bool Foam::patchDistMethods::advectionDiffusion::correct
//(
//	volScalarField& y,
//	volVectorField& n
//)
//{
//	if (!predicted_)
//	{
//		pdmPredictor_->correct(y);
//		predicted_ = true;
//	}
//
//	volVectorField ny
//	(
//		IOobject
//		(
//			"ny",
//			mesh_.time().timeName(),
//			mesh_,
//			IOobject::NO_READ,
//			IOobject::NO_WRITE,
//			false
//		),
//		mesh_,
//		dimensionedVector(dimless, Zero),
//		patchTypes<vector>(mesh_, patchIDs_)
//	);
//
//	const fvPatchList& patches = mesh_.boundary();
//	volVectorField::Boundary& nybf = ny.boundaryFieldRef();
//
//	forAllConstIter(labelHashSet, patchIDs_, iter)
//	{
//		label patchi = iter.key();
//		nybf[patchi] == -patches[patchi].nf();
//	}
//
//	int iter = 0;
//	scalar initialResidual = 0;
//
//	do
//	{
//		ny = fvc::grad(y);
//		ny /= (mag(ny) + small);
//
//		surfaceVectorField nf(fvc::interpolate(ny));
//		nf /= (mag(nf) + small);
//
//		surfaceScalarField yPhi("yPhi", mesh_.Sf() & nf);
//
//		fvScalarMatrix yEqn
//		(
//			fvm::div(yPhi, y)
//			- fvm::Sp(fvc::div(yPhi), y)
//			- epsilon_ * y*fvm::laplacian(y)
//			==
//			dimensionedScalar(dimless, 1.0)
//		);
//
//		yEqn.relax();
//		initialResidual = yEqn.solve().initialResidual();
//
//	} while (initialResidual > tolerance_ && ++iter < maxIter_);
//
//	// Only calculate n if the field is defined
//	if (notNull(n))
//	{
//		n = -ny;
//	}
//
//	return true;
//}
//
//
//// ************************************************************************* //