/*
** EPITECH PROJECT, 2024
** Interval.cpp
** File description:
** interval class
*/

#include "Interval.hpp"
#include "macros.hpp"

rtx::Interval::Interval() : min(+infinity), max(-infinity) {}

rtx::Interval::Interval(double _min, double _max) : min(_min), max(_max) {}

const rtx::Interval rtx::Interval::empty = rtx::Interval();
const rtx::Interval rtx::Interval::universe = rtx::Interval(-infinity, +infinity);

double rtx::Interval::clamp(double n) const
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}
