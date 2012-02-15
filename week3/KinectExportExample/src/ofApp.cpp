#include "ofApp.h"

#include <string>
#include <sstream>

//gives you an image in the rgb+alpha format in png

bool recordingOn = false;
int frameNumber = 0;
ostringstream fileNameToSave;

void ofApp::setup() {
    kinect.init();
	kinect.setRegistration(true);
	kinect.open();
    
//    ofImage_::ofImage(const ofPixels_< PixelType > &pix)
//    img.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);

    
}

void ofApp::update() {
	
    kinect.update();
    if(ofGetKeyPressed(' ')) {
        recordingOn =! recordingOn;
    }

    
	if(kinect.isFrameNew()) { 
        if (recordingOn == true && frameNumber <= 60) {
			ofPixels& depthPixels = kinect.getDepthPixelsRef();
			ofPixels& colorPixels = kinect.getPixelsRef();
			for(int y = 0; y < 480; y++) {
				for(int x = 0; x < 640; x++) {
					ofColor color = colorPixels.getColor(x, y);
					ofColor depth = depthPixels.getColor(x, y);
					img.setColor(x, y, ofColor(color, depth.getBrightness()));

				}
			}
            frameNumber = frameNumber + 1;
            ostringstream fileNameToSave;
            fileNameToSave << frameNumber << ".png";
            string result = fileNameToSave.str();
			img.saveImage(result);
		}
    }
}

void ofApp::draw() {
    
	ofBackground(0);
	ofSetColor(255, 255, 255);
	kinect.drawDepth(0, 0, 640, 480);
	kinect.draw(0, 480, 640, 480);
    

}

void ofApp::exit() {
	kinect.close();
}

