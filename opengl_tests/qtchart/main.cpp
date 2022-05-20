#include <QtWidgets>
#include <rabbit/chart/qtchart.h>

int main(int argc, char ** argv) 
{
	QApplication app(argc, argv);

	rabbit::qtchart chart;
	chart.show();

	app.exec();
}