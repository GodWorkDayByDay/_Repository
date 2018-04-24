#ifndef MILC_H
#define MILC_H

#include <mil.h>
#include <math.h>
#include <Windows.h>

// Image rotation values.
#define ROTATED_FIND_ROTATION_DELTA_ANGLE  180
// Angle range to search.
#define ROTATED_FIND_ANGLE_DELTA_POS           ROTATED_FIND_ROTATION_DELTA_ANGLE
#define ROTATED_FIND_ANGLE_DELTA_NEG           ROTATED_FIND_ROTATION_DELTA_ANGLE
// Minimum accuracy for the search angle.
#define ROTATED_FIND_MIN_ANGLE_ACCURACY        0.25

class MILC
{
public:
    MILC();
    ~MILC();
    bool MilSearch(double &find_x, double &find_y);

public:
    MIL_ID MilApplication;
    MIL_ID MilSystem;
    MIL_ID MilDisplay;

    MIL_ID ImageModel;
    MIL_ID ImageSource;
    MIL_ID Result;
    MIL_ID Model;

    MIL_DOUBLE Time;
    MIL_DOUBLE x, y, angle;
    MIL_DOUBLE Score;
    MIL_DOUBLE XOrg, YOrg;

    BYTE *b_model;
    BYTE *b_source;

    double unit;
    int modelID;
};

#endif // MILC_H
