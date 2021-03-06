/*!
 * \file two_bit_packed_file_signal_source.h
 * \brief Interface of a class that reads signals samples from a file. Each
 * sample is two bits, which are packed into bytes or shorts.
 *
 * \author Cillian O'Driscoll, 2015 cillian.odriscoll (at) gmail.com
 *
 * This class represents a file signal source.
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_TWO_BIT_PACKED_FILE_SIGNAL_SOURCE_H_
#define GNSS_SDR_TWO_BIT_PACKED_FILE_SIGNAL_SOURCE_H_

#include <string>
#include <gnuradio/blocks/file_source.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/blocks/throttle.h>
#include <gnuradio/hier_block2.h>
#include <gnuradio/msg_queue.h>
#include <gnuradio/blocks/interleaved_char_to_complex.h>
#include "gnss_block_interface.h"
#include "unpack_2bit_samples.h"



class ConfigurationInterface;

/*!
 * \brief Class that reads signals samples from a file
 * and adapts it to a SignalSourceInterface
 */
class TwoBitPackedFileSignalSource: public GNSSBlockInterface
{
public:
    TwoBitPackedFileSignalSource(ConfigurationInterface* configuration, std::string role,
            unsigned int in_streams, unsigned int out_streams,
            boost::shared_ptr<gr::msg_queue> queue);

    virtual ~TwoBitPackedFileSignalSource();
    std::string role()
    {
        return role_;
    }

    /*!
     * \brief Returns "Two_Bit_Packed_File_Signal_Source".
     */
    std::string implementation()
    {
        return "Two_Bit_Packed_File_Signal_Source";
    }
    size_t item_size()
    {
        return item_size_;
    }
    void connect(gr::top_block_sptr top_block);
    void disconnect(gr::top_block_sptr top_block);
    gr::basic_block_sptr get_left_block();
    gr::basic_block_sptr get_right_block();
    std::string filename()
    {
        return filename_;
    }
    std::string item_type()
    {
        return item_type_;
    }
    bool repeat()
    {
        return repeat_;
    }
    long sampling_frequency()
    {
        return sampling_frequency_;
    }
    long samples()
    {
        return samples_;
    }
    bool big_endian_items()
    {
        return big_endian_items_;
    }
    bool big_endian_bytes()
    {
        return big_endian_bytes_;
    }
    bool is_complex()
    {
        return is_complex_;
    }
    bool reverse_interleaving()
    {
        return reverse_interleaving_;
    }

private:
    unsigned long long samples_;
    long sampling_frequency_;
    std::string filename_;
    std::string item_type_;
    bool repeat_;
    bool dump_;
    std::string dump_filename_;
    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    gr::blocks::file_source::sptr file_source_;
    unpack_2bit_samples_sptr unpack_samples_;
    gr::basic_block_sptr char_to_float_;
    boost::shared_ptr<gr::block> valve_;
    gr::blocks::file_sink::sptr sink_;
    gr::blocks::throttle::sptr  throttle_;
    boost::shared_ptr<gr::msg_queue> queue_;
    size_t item_size_;
    bool big_endian_items_;
    bool big_endian_bytes_;
    bool is_complex_;
    bool reverse_interleaving_;
    std::string sample_type_;
    // Throttle control
    bool enable_throttle_control_;
};

#endif /*GNSS_SDR_TWO_BIT_CPX_FILE_SIGNAL_SOURCE_H_*/

