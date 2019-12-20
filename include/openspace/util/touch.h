/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2019                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/


#ifndef __OPENSPACE_CORE___TOUCH___H__
#define __OPENSPACE_CORE___TOUCH___H__

#include <cstdint>
#include <deque>

namespace openspace {

struct TouchInput {
    TouchInput(size_t touchDeviceId, size_t fingerId, float x, float y);
    float getScreenX(float resolutionX) const;
    float getScreenY(float resolutionY) const;

    size_t touchDeviceId;
    size_t fingerId;
    float x;
    float y;
    float dx;         // movement in x direction since last touch input
    float dy;         // movement in y direction since last touch input
    double timestamp; // timestamp in seconds from global touch initialization
};

class TouchInputs {
public:
    TouchInputs(TouchInput input);

    void addPoint(const TouchInput &&input);
    void clearInputs();

    const size_t getTouchDeviceId() const;
    const size_t getFingerId() const;

    float getCurrentSpeed() const;
    float getSpeedX() const;
    float getSpeedY() const;
    const TouchInput& getLatestInput() const;
    const std::deque<TouchInput> &getInputs() { return _inputs; }

private:
    static constexpr size_t MAX_INPUTS = 128;
    std::deque<TouchInput> _inputs;
    size_t _touchDeviceId;
    size_t _fingerId;
};

} // namespace openspace

#endif // __OPENSPACE_CORE___TOUCH___H__
