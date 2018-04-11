#pragma once

#include <Processing.NDI.Lib.h>
#include <unordered_map>

namespace KlakNDI
{
    // NDI receiver class
    class Receiver
    {
    public:

        Receiver(const NDIlib_source_t& source)
        {
            instance_ = NDIlib_recv_create_v2(&NDIlib_recv_create_t(source, NDIlib_recv_color_format_fastest));
            id_ = generateID();
            getInstanceMap()[id_] = this;
        }

        ~Receiver()
        {
            NDIlib_recv_destroy(instance_);
            getInstanceMap().erase(id_);
        }

        uint32_t getID() const
        {
            return id_;
        }

        bool receiveFrame()
        {
            return NDIlib_recv_capture_v2(instance_, &frame_, nullptr, nullptr, 0) == NDIlib_frame_type_video;
        }

        void freeFrame()
        {
            NDIlib_recv_free_video_v2(instance_, &frame_);
        }

        int getFrameWidth() const
        {
            return frame_.xres;
        }

        int getFrameHeight() const
        {
            return frame_.yres;
        }

        NDIlib_FourCC_type_e getFrameFourCC() const
        {
            return frame_.FourCC;
        }

        const void* getFrameData() const
        {
            return frame_.p_data;
        }

        static Receiver* getInstanceFromID(uint32_t id)
        {
            return getInstanceMap()[id];
        }

    private:

        NDIlib_recv_instance_t instance_;
        NDIlib_video_frame_v2_t frame_;
        uint32_t id_;

        static uint32_t generateID()
        {
            static uint32_t counter;
            return counter++;
        }

        static std::unordered_map<uint32_t, Receiver*>& getInstanceMap()
        {
            static std::unordered_map<uint32_t, Receiver*> map;
            return map;
        }
    };
}
