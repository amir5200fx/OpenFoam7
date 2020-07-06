#include <GAMGSolver.hxx>

#include <GAMGInterface.hxx>

#include <IOstreams.hxx>  // added by amir
#include <IStringStream.hxx> // added by amir
#include <OStringStream.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGSolver, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<GAMGSolver>
		addGAMGSolverMatrixConstructorToTable_;

	lduMatrix::solver::addasymMatrixConstructorToTable<GAMGSolver>
		addGAMGAsymSolverMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GAMGSolver::GAMGSolver
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& solverControls
)
	:
	lduMatrix::solver
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces,
		solverControls
	),

	// Default values for all controls
	// which may be overridden by those in controlDict
	cacheAgglomeration_(true),
	nPreSweeps_(0),
	preSweepsLevelMultiplier_(1),
	maxPreSweeps_(4),
	nPostSweeps_(2),
	postSweepsLevelMultiplier_(1),
	maxPostSweeps_(4),
	nFinestSweeps_(2),
	interpolateCorrection_(false),
	scaleCorrection_(matrix.symmetric()),
	directSolveCoarsest_(false),
	agglomeration_(GAMGAgglomeration::New(matrix_, controlDict_)),

	matrixLevels_(agglomeration_.size()),
	primitiveInterfaceLevels_(agglomeration_.size()),
	interfaceLevels_(agglomeration_.size()),
	interfaceLevelsBouCoeffs_(agglomeration_.size()),
	interfaceLevelsIntCoeffs_(agglomeration_.size())
{
	readControls();

	if (agglomeration_.processorAgglomerate())
	{
		forAll(agglomeration_, fineLevelIndex)
		{
			if (agglomeration_.hasMeshLevel(fineLevelIndex))
			{
				if
					(
					(fineLevelIndex + 1) < agglomeration_.size()
						&& agglomeration_.hasProcMesh(fineLevelIndex + 1)
						)
				{
					// Construct matrix without referencing the coarse mesh so
					// construct a dummy mesh instead. This will get overwritten
					// by the call to procAgglomerateMatrix so is only to get
					// it through agglomerateMatrix


					const lduInterfacePtrsList& fineMeshInterfaces =
						agglomeration_.interfaceLevel(fineLevelIndex);

					PtrList<GAMGInterface> dummyPrimMeshInterfaces
					(
						fineMeshInterfaces.size()
					);
					lduInterfacePtrsList dummyMeshInterfaces
					(
						dummyPrimMeshInterfaces.size()
					);
					forAll(fineMeshInterfaces, intI)
					{
						if (fineMeshInterfaces.set(intI))
						{
							OStringStream os;
							refCast<const GAMGInterface>
								(
									fineMeshInterfaces[intI]
									).write(os);
							IStringStream is(os.str());

							dummyPrimMeshInterfaces.set
							(
								intI,
								GAMGInterface::New
								(
									fineMeshInterfaces[intI].type(),
									intI,
									dummyMeshInterfaces,
									is
								)
							);
						}
					}

					forAll(dummyPrimMeshInterfaces, intI)
					{
						if (dummyPrimMeshInterfaces.set(intI))
						{
							dummyMeshInterfaces.set
							(
								intI,
								&dummyPrimMeshInterfaces[intI]
							);
						}
					}

					// So:
					// - pass in incorrect mesh (= fine mesh instead of coarse)
					// - pass in dummy interfaces
					agglomerateMatrix
					(
						fineLevelIndex,
						agglomeration_.meshLevel(fineLevelIndex),
						dummyMeshInterfaces
					);


					const labelList& procAgglomMap =
						agglomeration_.procAgglomMap(fineLevelIndex + 1);
					const List<label>& procIDs =
						agglomeration_.agglomProcIDs(fineLevelIndex + 1);

					procAgglomerateMatrix
					(
						procAgglomMap,
						procIDs,
						fineLevelIndex
					);
				}
				else
				{
					agglomerateMatrix
					(
						fineLevelIndex,
						agglomeration_.meshLevel(fineLevelIndex + 1),
						agglomeration_.interfaceLevel(fineLevelIndex + 1)
					);
				}
			}
			else
			{
				// No mesh. Not involved in calculation anymore
			}
		}
	}
	else
	{
		forAll(agglomeration_, fineLevelIndex)
		{
			// Agglomerate on to coarse level mesh
			agglomerateMatrix
			(
				fineLevelIndex,
				agglomeration_.meshLevel(fineLevelIndex + 1),
				agglomeration_.interfaceLevel(fineLevelIndex + 1)
			);
		}
	}


	if (debug)
	{
		for
			(
				label fineLevelIndex = 0;
				fineLevelIndex <= matrixLevels_.size();
				fineLevelIndex++
				)
		{
			if (fineLevelIndex == 0 || matrixLevels_.set(fineLevelIndex - 1))
			{
				const lduMatrix& matrix = matrixLevel(fineLevelIndex);
				const lduInterfaceFieldPtrsList& interfaces =
					interfaceLevel(fineLevelIndex);

				Pout << "level:" << fineLevelIndex << nl
					<< "    nCells:" << matrix.diag().size() << nl
					<< "    nFaces:" << matrix.lower().size() << nl
					<< "    nInterfaces:" << interfaces.size()
					<< endl;

				forAll(interfaces, i)
				{
					if (interfaces.set(i))
					{
						Pout << "        " << i
							<< "\ttype:" << interfaces[i].type()
							<< endl;
					}
				}
			}
			else
			{
				Pout << "level:" << fineLevelIndex << " : no matrix" << endl;
			}
		}
		Pout << endl;
	}


	if (matrixLevels_.size())
	{
		if (directSolveCoarsest_)
		{
			const label coarsestLevel = matrixLevels_.size() - 1;

			if (matrixLevels_.set(coarsestLevel))
			{
				coarsestLUMatrixPtr_.set
				(
					new LUscalarMatrix
					(
						matrixLevels_[coarsestLevel],
						interfaceLevelsBouCoeffs_[coarsestLevel],
						interfaceLevels_[coarsestLevel]
					)
				);
			}
		}
	}
	else
	{
		FatalErrorInFunction
			<< "No coarse levels created, either matrix too small for GAMG"
			" or nCellsInCoarsestLevel too large.\n"
			"    Either choose another solver of reduce "
			"nCellsInCoarsestLevel."
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::GAMGSolver::~GAMGSolver()
{
	if (!cacheAgglomeration_)
	{
		delete &agglomeration_;
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGSolver::readControls()
{
	lduMatrix::solver::readControls();

	controlDict_.readIfPresent("cacheAgglomeration", cacheAgglomeration_);
	controlDict_.readIfPresent("nPreSweeps", nPreSweeps_);
	controlDict_.readIfPresent
	(
		"preSweepsLevelMultiplier",
		preSweepsLevelMultiplier_
	);
	controlDict_.readIfPresent("maxPreSweeps", maxPreSweeps_);
	controlDict_.readIfPresent("nPostSweeps", nPostSweeps_);
	controlDict_.readIfPresent
	(
		"postSweepsLevelMultiplier",
		postSweepsLevelMultiplier_
	);
	controlDict_.readIfPresent("maxPostSweeps", maxPostSweeps_);
	controlDict_.readIfPresent("nFinestSweeps", nFinestSweeps_);
	controlDict_.readIfPresent("interpolateCorrection", interpolateCorrection_);
	controlDict_.readIfPresent("scaleCorrection", scaleCorrection_);
	controlDict_.readIfPresent("directSolveCoarsest", directSolveCoarsest_);

	if (debug)
	{
		Pout << "GAMGSolver settings :"
			<< " cacheAgglomeration:" << cacheAgglomeration_
			<< " nPreSweeps:" << nPreSweeps_
			<< " preSweepsLevelMultiplier:" << preSweepsLevelMultiplier_
			<< " maxPreSweeps:" << maxPreSweeps_
			<< " nPostSweeps:" << nPostSweeps_
			<< " postSweepsLevelMultiplier:" << postSweepsLevelMultiplier_
			<< " maxPostSweeps:" << maxPostSweeps_
			<< " nFinestSweeps:" << nFinestSweeps_
			<< " interpolateCorrection:" << interpolateCorrection_
			<< " scaleCorrection:" << scaleCorrection_
			<< " directSolveCoarsest:" << directSolveCoarsest_
			<< endl;
	}
}


const tnbLib::lduMatrix& tnbLib::GAMGSolver::matrixLevel(const label i) const
{
	if (i == 0)
	{
		return matrix_;
	}
	else
	{
		return matrixLevels_[i - 1];
	}
}


const tnbLib::lduInterfaceFieldPtrsList& tnbLib::GAMGSolver::interfaceLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return interfaces_;
	}
	else
	{
		return interfaceLevels_[i - 1];
	}
}


const tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>&
tnbLib::GAMGSolver::interfaceBouCoeffsLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return interfaceBouCoeffs_;
	}
	else
	{
		return interfaceLevelsBouCoeffs_[i - 1];
	}
}


const tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>&
tnbLib::GAMGSolver::interfaceIntCoeffsLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return interfaceIntCoeffs_;
	}
	else
	{
		return interfaceLevelsIntCoeffs_[i - 1];
	}
}


// ************************************************************************* //