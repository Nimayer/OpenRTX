/***************************************************************************
 *   Copyright (C) 2021 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef M17FRAME_H
#define M17FRAME_H

#ifndef __cplusplus
#error This header is C++ only!
#endif

#include <string>
#include "M17Datatypes.h"

/**
 * This class describes and handles a generic M17 data frame.
 */
class M17Frame
{
public:

    /**
     * Constructor.
     */
    M17Frame()
    {
        clear();
    }

    /**
     * Destructor.
     */
    ~M17Frame(){ }

    /**
     * Clear the frame content, filling it with zeroes.
     */
    void clear()
    {
        auto *ptr = reinterpret_cast< uint8_t *>(&data);
        std::fill(ptr, ptr + sizeof(dataFrame_t), 0x00);
    }

    /**
     * Set frame sequence number.
     *
     * @param seqNum: frame number, between 0 and 0x7FFF.
     */
    void setFrameNumber(const uint16_t seqNum)
    {
        // NOTE: M17 fields are big-endian, we need to swap bytes
        data.frameNum = __builtin_bswap16(seqNum &  0x7fff);
    }

    /**
     * Mark this frame as the last one in the transmission, informing the
     * receiver that transmission ends.
     */
    void lastFrame()
    {
        data.frameNum |= 0x0080;
    }

    /**
     *
     */
//     void setLICH(const lsfChunk_t& lich)
//     {
//         data.LICH = lich;
//     }

    /**
     * Access frame payload.
     *
     * @return a reference to frame's paylod field, allowing for both read and
     * write access.
     */
    payload_t& payload()
    {
        return data.payload;
    }

    /**
     * Get underlying data structure.
     *
     * @return a reference to the underlying dataFrame_t data structure.
     */
    dataFrame_t& getData()
    {
        return data;
    }

private:

    dataFrame_t data;   ///< Underlying frame data.
};

#endif /* M17FRAME_H */