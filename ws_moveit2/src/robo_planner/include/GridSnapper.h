#ifndef GRIDSNAPPER_HPP
#define GRIDSNAPPER_HPP

namespace WzlPlanner
{
    class GridSnappper
    {

        public:
            GridSnappper(const float offsetX, const float offsetY, const float gapSizeX, const float gapSizeY) 
            { 
                offsetX_ = offsetX; 
                offsetY_ = offsetY;
                gapSizeX_ = gapSizeX; 
                gapSizeY_ = gapSizeY;
            }

            void SnapToGrid(const float posX, const float posY, int& indexX, int& indexY) const
            {
                indexX = (posX - offsetX_ + gapSizeX_ * 0.5f) / gapSizeX_;
                indexY = (posY - offsetY_ + gapSizeY_ * 0.5f) / gapSizeY_;
            }

            float GetSnappedPosX(const int indexX)
            {
                return offsetX_ + indexX * gapSizeX_;
            }

            float GetSnappedPosY(const int indexY)
            {
                return offsetY_ + indexY * gapSizeY_;
            }

        private:
            // offset between the world origin and the first drill hole [m]
            float offsetX_, offsetY_;

            // gap between 2 drill holes [m]
            float gapSizeX_, gapSizeY_;
    };
} // namespace WzlPlanner

#endif // GRIDSNAPPER_HPP