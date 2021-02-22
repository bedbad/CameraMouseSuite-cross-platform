/*                         Camera Mouse Suite
 *  Copyright (C) 2015, Andrew Kurauchi
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtCore/QObject>
#if defined(Q_OS_LINUX) || defined(Q_OS_WIN32)
#include <opencv2/imgproc.hpp>
#endif

#include "ImageProcessing.h"

namespace CMS {

void ImageProcessing::drawGreenRectangle(cv::Mat &image, cv::Rect &rectangle)
{
    cv::rectangle(image, rectangle, cv::Scalar(50, 205, 50), 2);
}

} // namespace CMS