
#ifndef AUDIO__AudioQtDevice_H
#define AUDIO__AudioQtDevice_H

#include "AAL_Qt.h"

#include <Data/DataTypes.h>
#include <QtMultimedia/QAudioOutput>
#include <Audio/AudioData.h>

namespace Audio {

class AAL_QT_DLL_EXPORT AudioQtDevice : public QObject {
	Q_OBJECT
	public:
		AudioQtDevice(QObject * parent = 0);

	signals:

		void frameChanged(I8u frame);

	public slots:

		void start();
		void stop();
		void presentData(AudioData * data);
		void config(I8u channels,I8u freq,I8u sampleSize);

	private:
		QAudioOutput * audioOutput;
		QIODevice    * audioDevice;
};

}

#endif 
