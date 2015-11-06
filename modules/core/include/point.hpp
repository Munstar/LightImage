//
// Created by xin on 11/4/15.
//

#ifndef LIGHTIMAGE_POINT_H
#define LIGHTIMAGE_POINT_H


namespace li
{
    template <typename _Tp>
    class Point2_
    {
    public:
        Point2_(_Tp _x, _Tp _y);
        Point2_(const li::Point2_<_Tp>& p);
        Point2_();

        const Point2_ operator + (const Point2_& p);
        const Point2_ operator - (const Point2_& p);
        Point2_& operator = (const Point2_ p);


        _Tp x,y;
    };

    template <typename _Tp>
    class Point3_
    {
    public:
        Point3_(_Tp _x, _Tp _y, _Tp _z);
        Point3_(const li::Point3_<_Tp>& p);
        Point3_();

        const Point3_ operator + (const Point3_& p);
        const Point3_ operator - (const Point3_& p);
        Point3_& operator = (const Point3_& p);

        _Tp x,y,z;
    };

    template <typename _Tp>
    Point2_<_Tp>::Point2_(_Tp _x, _Tp _y) : x(_x), y(_y) { }

    template <typename _Tp>
    Point2_<_Tp>::Point2_(const li::Point2_<_Tp>& p)
    {
        x = p.x;
        y = p.y;
    }

    template <typename _Tp>
    Point2_<_Tp>::Point2_() : x(0), y(0) { }

    template <typename _Tp>
    const Point2_<_Tp> Point2_<_Tp>::operator + (const li::Point2_<_Tp>& p)
    {
        return Point2_<_Tp>(x + p.x, y + p.y);
    }

    template <typename _Tp>
    const Point2_<_Tp> Point2_<_Tp>::operator - (const li::Point2_<_Tp>& p)
    {
        return Point2_<_Tp>(x + p.x, y + p.y);
    }


    template <typename _Tp>
    Point2_<_Tp>& Point2_<_Tp>::operator = (const li::Point2_<_Tp> p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    template <typename _Tp>
    Point3_<_Tp>::Point3_() : x(0), y(0), z(0) { }

    template <typename _Tp>
    Point3_<_Tp>::Point3_(_Tp _x, _Tp _y, _Tp _z) : x(_x), y(_y), z(_z){ }

    template <typename _Tp>
    Point3_<_Tp>::Point3_(const li::Point3_<_Tp> &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    template <typename _Tp>
    const Point3_<_Tp> Point3_<_Tp>::operator+(const li::Point3_<_Tp> &p)
    {
        return Point3_<_Tp>(x + p.x, y + p.y, z + p.z);
    }

    template <typename _Tp>
    const Point3_<_Tp> Point3_<_Tp>::operator-(const li::Point3_<_Tp> &p)
    {
        return Point3_<_Tp>(x - p.x, y - p.y, z + p.z);
    }

    template <typename _Tp>
    Point3_<_Tp>& Point3_<_Tp>::operator=(const li::Point3_<_Tp> &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
}


#endif //LIGHTIMAGE_POINT_H
