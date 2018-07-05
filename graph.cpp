#include "graph.h"

Graph::Graph()
{

}

void Graph::addNode(const QPoint &src, const QPoint &dst)
{
    pointGraph.insert(src, dst);
}

void Graph::clearAll()
{
    pointGraph.clear();
}

QVector<QPoint> Graph::findPath(const QPoint &start, const QPoint &end, QVector<QPoint> path)
{
    QVector<QPoint> empty;  // Define an empty QVector if no path found
    path.append(start);

    if (start == end)
        return path;

    if (!pointGraph.contains(start))
        return empty;

    for (auto &node : pointGraph.values(start))
    {
        if (!path.contains(node))
        {
            QVector<QPoint> newPath;
            newPath = findPath(node, end, path);
            if (!newPath.isEmpty())
                return newPath;
        }
    }
    return empty;
}
