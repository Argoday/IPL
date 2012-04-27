# AVL_Qt - Video Library integration with Qt

## Contents

### QueueQtTarget, Widget, WidgetSurface
The target of a media pipe that renders video onto Video::Widget

## Example Usage
 ----------------
auto videoWidget = new Video::Widget();  
auto surface = videoWidget->videoSurface();  
  
player = new Media::FFMPEGqtPlayer(dataManager,surface);  
 ----------------

## Example Program
See ./exe/MediaPlayer  

## Dependencies

./lib/AIL  
