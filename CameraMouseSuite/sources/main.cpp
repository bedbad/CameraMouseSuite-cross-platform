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

#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtMultimedia/QCamera>
#include <QtMultimediaWidgets/QCameraViewfinder>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCamera camera;
    QCameraViewfinder viewfinder;
    viewfinder.show();
    camera.setViewfinder(&viewfinder);
    camera.start();
    return app.exec();
    /*
    QApplication a(argc, argv);
    CMS::MainWindow w;
    w.show();

    return a.exec();*/
}
