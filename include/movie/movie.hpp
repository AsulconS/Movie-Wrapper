#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <string>

#include "core/common.hpp"

struct MovieData
{
    uint32 id;

    std::string type;
    std::string primaryTitle;
    std::string originalTitle;

    bool isAdult;

    uint16 startYear;
    uint16 endYear;

    uint8 runtimeMinutes;

    std::vector<std::string> genders;
};

enum Criteria
{
    DEFAULT,
    BY_ID = offsetof(MovieData, id),
    BY_TYPE = offsetof(MovieData, type),
    BY_PRIMARY_TITLE = offsetof(MovieData, primaryTitle),
    BY_ORIGINAL_TITLE = offsetof(MovieData, originalTitle),
    BY_START_YEAR = offsetof(MovieData, startYear),
    BY_END_YEAR = offsetof(MovieData, endYear),
    BY_RUNTIME_MINUTES = offsetof(MovieData, runtimeMinutes)
};

using CriteriaOffset = uint8;

class Movie
{
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
    typedef bool (Movie::*CriteriaFnType)(const Movie& m1, const Movie& m2) const;
private:
    CriteriaOffset criteriaOffset;
    CriteriaFnType criteriaEFn;
    CriteriaFnType criteriaIFn;

    MovieData* data;

    template <typename T>
    inline bool criteriaE(const Movie& m1, const Movie& m2) const
    {
        if(m1.criteriaOffset != m2.criteriaOffset) return false;
        uint8* ptr1 = reinterpret_cast<uint8*>(m1.data);
        uint8* ptr2 = reinterpret_cast<uint8*>(m2.data);
        return *((T*)(ptr1 + m1.criteriaOffset)) == *((T*)(ptr2 + m2.criteriaOffset));
    }
    template <typename T>
    inline bool criteriaI(const Movie& m1, const Movie& m2) const
    {
        if(m1.criteriaOffset != m2.criteriaOffset) return false;
        uint8* ptr1 = reinterpret_cast<uint8*>(m1.data);
        uint8* ptr2 = reinterpret_cast<uint8*>(m2.data);
        return *((T*)(ptr1 + m1.criteriaOffset)) > *((T*)(ptr2 + m2.criteriaOffset));
    }

public:
    inline bool operator==(const Movie& o) const { return  (this->*criteriaEFn)(*this, o); }
    inline bool operator> (const Movie& o) const { return  (this->*criteriaIFn)(*this, o); }
    inline bool operator< (const Movie& o) const { return !(this->*criteriaIFn)(*this, o); }
    inline bool operator>=(const Movie& o) const { return  (this->*criteriaIFn)(*this, o) || (this->*criteriaEFn)(*this, o); }
    inline bool operator<=(const Movie& o) const { return !(this->*criteriaIFn)(*this, o) || (this->*criteriaEFn)(*this, o); }

    template <typename T>
    inline void setCriteria(const CriteriaOffset _criteriaOffset)
    {
        criteriaOffset = _criteriaOffset;
        criteriaEFn = &Movie::criteriaE<T>;
        criteriaIFn = &Movie::criteriaI<T>;
    }

    inline void setData(MovieData* _data) { delete data; data = _data; }

    Movie() { data = new MovieData; }
    Movie(MovieData* _data) : data(_data) {}
    virtual ~Movie() { delete data; }
};

#endif // MOVIE_H
