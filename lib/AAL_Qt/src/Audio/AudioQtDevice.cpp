
#include "AudioQtDevice.h"

namespace Audio {

AAL_QT_DLL_EXPORT AudioQtDevice::AudioQtDevice(QObject * parent)
	:QObject(parent)
{
	QAudioFormat format; //Guess
	format.setFrequency(44100);
	format.setChannels(2);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	audioOutput = new QAudioOutput(format);
	start();
}
void AAL_QT_DLL_EXPORT AudioQtDevice::start(){
	audioDevice=audioOutput->start();
}
void AAL_QT_DLL_EXPORT AudioQtDevice::stop(){
	audioOutput->stop();
}
void AAL_QT_DLL_EXPORT AudioQtDevice::presentData(AudioData * data){
	audioDevice->write(reinterpret_cast<const char*>(data->getData()),data->getNumBytes());
	delete data;
}
void AAL_QT_DLL_EXPORT AudioQtDevice::config(I8u channels,I8u freq,I8u sampleSize){
	QAudioFormat format;
	format.setFrequency(freq);
	format.setChannels(channels);
	format.setSampleSize(sampleSize*8);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	audioOutput = new QAudioOutput(format);
	start();
}


}