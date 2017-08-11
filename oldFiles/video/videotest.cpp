#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QWidget>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMediaPlayer *player = new QMediaPlayer;
	QMediaPlaylist *playlist = new QMediaPlaylist(player);
	player->setMedia(QUrl::fromLocalFile("/home/masa/jarvis/src/gui/video/andromeda.mp4"));

	QVideoWidget *videoWidget = new QVideoWidget;
	player->setVideoOutput(videoWidget);

	videoWidget->show();
	playlist->setCurrentIndex(1);
	player->setVolume(10);
	player->play();
}
