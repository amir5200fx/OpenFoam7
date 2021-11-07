#include <edgeVertex.hxx>

#include <meshTools.hxx>
#include <refineCell.hxx>

// * * * * * * * * * * * * * * * Static Functions  * * * * * * * * * * * * * //


// Update stored refine list using map
void tnbLib::edgeVertex::updateLabels
(
    const labelList& map,
    List<refineCell>& refCells
)
{
    label newRefI = 0;

    forAll(refCells, refI)
    {
        const refineCell& refCell = refCells[refI];

        label oldCelli = refCell.cellNo();

        label newCelli = map[oldCelli];

        if (newCelli != -1)
        {
            refCells[newRefI++] = refineCell(newCelli, refCell.direction());
        }
    }
    refCells.setSize(newRefI);
}


// Update stored cell numbers using map.
// Do in two passes to prevent allocation if nothing changed.
void tnbLib::edgeVertex::updateLabels
(
    const labelList& map,
    Map<label>& cellPairs
)
{
    // Iterate over map to see if anything changed
    bool changed = false;

    forAllConstIter(Map<label>, cellPairs, iter)
    {
        label newMaster = map[iter.key()];

        label newSlave = -1;

        if (iter() != -1)
        {
            newSlave = map[iter()];
        }

        if ((newMaster != iter.key()) || (newSlave != iter()))
        {
            changed = true;

            break;
        }
    }

    // Relabel (use second Map to prevent overlapping)
    if (changed)
    {
        Map<label> newCellPairs(2 * cellPairs.size());

        forAllConstIter(Map<label>, cellPairs, iter)
        {
            label newMaster = map[iter.key()];

            label newSlave = -1;

            if (iter() != -1)
            {
                newSlave = map[iter()];
            }

            if (newMaster == -1)
            {
                WarningInFunction
                    << "master cell:" << iter.key()
                    << " has disappeared" << endl;
            }
            else
            {
                newCellPairs.insert(newMaster, newSlave);
            }
        }

        cellPairs = newCellPairs;
    }
}


// Update stored cell numbers using map.
// Do in two passes to prevent allocation if nothing changed.
void tnbLib::edgeVertex::updateLabels
(
    const labelList& map,
    labelHashSet& cells
)
{
    // Iterate over map to see if anything changed
    bool changed = false;

    forAllConstIter(labelHashSet, cells, iter)
    {
        const label newCelli = map[iter.key()];

        if (newCelli != iter.key())
        {
            changed = true;

            break;
        }
    }

    // Relabel (use second Map to prevent overlapping)
    if (changed)
    {
        labelHashSet newCells(2 * cells.size());

        forAllConstIter(labelHashSet, cells, iter)
        {
            const label newCelli = map[iter.key()];

            if (newCelli != -1)
            {
                newCells.insert(newCelli);
            }
        }

        cells = newCells;
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::edgeVertex::coord
(
    const primitiveMesh& mesh,
    const label cut,
    const scalar weight
)
{
    const pointField& pts = mesh.points();

    if (isEdge(mesh, cut))
    {
        const edge& e = mesh.edges()[getEdge(mesh, cut)];

        return weight * pts[e.end()] + (1 - weight) * pts[e.start()];
    }
    else
    {
        return pts[getVertex(mesh, cut)];
    }
}


tnbLib::label tnbLib::edgeVertex::cutPairToEdge
(
    const primitiveMesh& mesh,
    const label cut0,
    const label cut1
)
{
    if (!isEdge(mesh, cut0) && !isEdge(mesh, cut1))
    {
        return meshTools::findEdge
        (
            mesh,
            getVertex(mesh, cut0),
            getVertex(mesh, cut1)
        );
    }
    else
    {
        return -1;
    }
}


tnbLib::Ostream& tnbLib::edgeVertex::writeCut
(
    Ostream& os,
    const label cut,
    const scalar weight
) const
{
    if (isEdge(cut))
    {
        label edgeI = getEdge(cut);

        const edge& e = mesh().edges()[edgeI];

        os << "edge:" << edgeI << e << ' ' << coord(cut, weight);
    }
    else
    {
        label vertI = getVertex(cut);

        os << "vertex:" << vertI << ' ' << coord(cut, weight);
    }
    return os;
}


tnbLib::Ostream& tnbLib::edgeVertex::writeCuts
(
    Ostream& os,
    const labelList& cuts,
    const scalarField& weights
) const
{
    forAll(cuts, cutI)
    {
        if (cutI > 0)
        {
            os << ' ';
        }
        writeCut(os, cuts[cutI], weights[cutI]);
    }
    return os;
}


// ************************************************************************* //
