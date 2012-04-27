# AAL_Qt - Audio Library integration with Qt

## Contents

### QueueQtTarget, AudioQtDevice
The target of a media pipe that plays audio using Audio::AudioQtDevice

## Example Usage
 ----------------
auto audioQtDevice = new Audio::AudioQtDevice();  
auto audioQtTarget = new Audio::Queue::QtTarget(audioQtDevice);  
auto audioReaderAgent = new Thread::Queue::ReaderAgent(*audioPipe);  
audioReaderAgent->registerTarget(audioQtTarget);  
 ----------------

## Example Program
See ./exe/MediaPlayer  

## Dependencies

./lib/AAL  
