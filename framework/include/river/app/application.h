#ifndef RIVER_APPLICATION_H
#define RIVER_APPLICATION_H

namespace ri
{
    /**
     * \brief represents an application with its window class. Make sure to create its subclass
     * 
     */
    struct Application
    {
        /**
         * \brief
         */
        explicit Application(unsigned width, unsigned height, const char* title);
        virtual ~Application() = default;
        auto run() -> int;

        auto getScreenWidth() const -> unsigned;
        auto getScreenHeight() const -> unsigned;
        auto getTitle() const -> const char*;
        auto getVerticalSync() const -> float;
    protected:
        auto setVerticalSync(bool vsync) -> void;
        virtual void init() {}
        virtual void update(float delta) {}
        virtual void render() {}
    private:
        bool m_vsync;
        unsigned m_width;
        unsigned m_height;
        const char* m_title;
        void* m_window;
    };
}

#endif