#ifndef GROUPBYTYPES_H
#define GROUPBYTYPES_H
#include "Explorer.h"

class GroupByTypes : public IExplore {
public:
    explicit GroupByTypes() = default;
    virtual ~GroupByTypes() = default;
    void explore(const QString& path) override;
};


#endif // GROUPBYTYPES_H
