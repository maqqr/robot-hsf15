# Install recordscreen.py utility first

http://www.davidrevoy.com/article65/recordscreen-py-video-and-audio-capture-from-terminal-for-ubuntu-12-04

sudo apt-get install wget libav-tools ffmpeg libavc1394-0 libavformat-extra-53 libavfilter2 libavutil-extra-51 mencoder libavahi-common-data

wget http://www.davidrevoy.com/data/documents/recordscreen_12-04.zip -P ~/bin/
unzip ~/bin/recordscreen_12-04.zip
rm ~/bin/recordscreen_12-04.zip
chmod +x ~/bin/recordscreen.py

(and make sure ~/bin is in path..)
