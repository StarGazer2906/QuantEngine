#include "qe/daycount/Actual365.hpp"
#include "qe/daycount/Actual360.hpp"
#include "qe/daycount/ActualActual.hpp"
#include "qe/daycount/Thirty360.hpp"
#include <stdexcept>
#include <cassert>

int main()
{

    Date start(1, 1, 2025);
    Date end(1, 7, 2025);

    Actual365 dc;

    assert(dc.yearFraction(start, end) == 181.0 / 365.0);

    Date d1(1, 1, 2024);
    Date d2(1, 1, 2025);

    assert(dc.yearFraction(d1, d2) == 366.0 / 365.0);

    Date start360(1, 1, 2025);
    Date end360(1, 7, 2025);

    Actual360 dc360;

    assert(dc360.yearFraction(start360, end360) == 181.0 / 360.0);

    Date leapStart360(1, 1, 2024);
    Date leapEnd360(1, 1, 2025);

    assert(dc360.yearFraction(leapStart360, leapEnd360) == 366.0 / 360.0);

    Date aaStart1(1, 1, 2025);
    Date aaEnd1(1, 7, 2025);

    ActualActual dcAA;

    assert(dcAA.yearFraction(aaStart1, aaEnd1) == 181.0 / 365.0);


    Date aaStart3(1, 1, 2025);
    Date aaEnd3(1, 7, 2025);

    assert(dcAA.yearFraction(aaStart3, aaEnd3) == 181.0 / 365.0);

    Date aaStart4(1, 1, 2024);
    Date aaEnd4(1, 7, 2024);

    assert(dcAA.yearFraction(aaStart4, aaEnd4) == 182.0 / 366.0);

    Date aaStart5(1, 1, 2024);
    Date aaEnd5(1, 1, 2025);

    assert(dcAA.yearFraction(aaStart5, aaEnd5) == 1.0);

    Date aaStart6(1, 7, 2024);
    Date aaEnd6(1, 7, 2026);

    double expectedAA6 =
        184.0 / 366.0 +
        1.0 +
        181.0 / 365.0;

    assert(dcAA.yearFraction(aaStart6, aaEnd6) == expectedAA6);

    Thirty360 dc30;

    // 30/360 — ordinary dates
    Date tStart1(1, 1, 2025);
    Date tEnd1(1, 7, 2025);

    assert(dc30.yearFraction(tStart1, tEnd1) == 0.5);


    // Start = 30, End = 31
    Date tStart2(30, 1, 2025);
    Date tEnd2(31, 3, 2025);

    assert(dc30.yearFraction(tStart2, tEnd2) == 60.0 / 360.0);


    // Start = 29, End = 31
    // End 31 should remain 31
    Date tStart3(29, 1, 2025);
    Date tEnd3(31, 3, 2025);

    assert(dc30.yearFraction(tStart3, tEnd3) == 62.0 / 360.0);


    // Start = 31, End = 31
    // Start 31 -> 30, therefore End 31 -> 30
    Date tStart4(31, 1, 2025);
    Date tEnd4(31, 3, 2025);

    assert(dc30.yearFraction(tStart4, tEnd4) == 60.0 / 360.0);


    // Non-leap February month-end
    Date tStart5(28, 2, 2025);
    Date tEnd5(31, 3, 2025);

    assert(dc30.yearFraction(tStart5, tEnd5) == 30.0 / 360.0);


    // Leap-year February month-end
    Date tStart6(29, 2, 2024);
    Date tEnd6(31, 3, 2024);

    assert(dc30.yearFraction(tStart6, tEnd6) == 30.0 / 360.0);


    // Both dates are February month-end
    Date tStart7(28, 2, 2025);
    Date tEnd7(28, 2, 2026);

    assert(dc30.yearFraction(tStart7, tEnd7) == 1.0);


    // Leap February → non-leap February
    Date tStart8(29, 2, 2024);
    Date tEnd8(28, 2, 2025);

    assert(dc30.yearFraction(tStart8, tEnd8) == 1.0);

    return 0;
}

