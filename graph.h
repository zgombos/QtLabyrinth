#ifndef GRAPH_H
#define GRAPH_H

#include <QMultiMap>
#include <QVector>
#include <QPoint>

class Graph
{
public:
    Graph();

    void addNode(const QPoint &src, const QPoint &dst);
    void clearAll();
    QVector<QPoint> findPath(const QPoint &start, const QPoint &end, QVector<QPoint> path={});

private:
    QMultiMap<QPoint, QPoint> pointGraph;
};

inline bool operator< (const QPoint &first, const QPoint &second)
{
    return first.x() <second.x() || ( first.x() == second.x() && first.y() < second.y() );
}

#endif // GRAPH_H
